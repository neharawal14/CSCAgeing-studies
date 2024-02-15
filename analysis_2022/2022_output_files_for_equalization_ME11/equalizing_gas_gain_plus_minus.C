#define equalizing_gas_gain_plus_minus_cxx
#include "equalizing_gas_gain_plus_minus.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void equalizing_gas_gain_plus_minus :: Loop(){
   // we are passing name of the input file when calling the macro 
   TFile * inputf = TFile::Open("/cmsuf/data/store/user/t2/users/neha.rawal/CSCAgeing_2022/analysis_2022/2022_output_files_for_equalization_ME11/output_after_pressure_depenedence_removal_ME11_plus.root");
   TTree * tree =(TTree*) inputf->Get("tree_new");
   Init(tree);
   TH2D * hcharge = new TH2D("hcharge","charge (ADC counts) for each channel",3000,0,3000, 770,1,771);
	 // output root file after processing 
//   TFile * outf  = new TFile(output_path+"outf"+detregionstr+"_"+chamber_string_name+"_output.root","recreate");  
	   for(int i = 0; i < tree->GetEntries(); i++){
     // std::cout<<"entered into integratedlumi loop correction "<<i<<std::endl; 
		 //if(_integratelumi==0) continue;
     // std::cout<<"case for which integratedlumi correction exists "<<i<<std::endl; 
     //if(i%100 !=0 &&istest) continue;
     LoadTree(i);tree->GetEntry(i);
     if(i%1000000 ==0)cout << i<<endl;
     //if(badrun(_runNb) ) continue;
     //if(check7to9e33only  &&_instlumi<8000 ) continue;
     //if(check7to9e33only  &&_instlumi>14000 ) continue;
     // what is significance of this ?
		 //if(check7to9e33only) _integratelumi -= 17000;
     int rhidreduced = ((int)floor(new_rhid/10))%1000;
     if(new_rhid> 2000000) rhidreduced +=400;
     //int idforcorr = (iszmumu )? 0: rhidreduced ;
     hcharge->Fill(new_rhsumQ_RAW,rhidreduced);
   }
	 
	// plot the charge for each reduced rhid, and find trimmed mean for each distribution 
  // This vector stores the gas gain for each channel. Gas gain for each channel is the trimmed mean for the channel 
	vector<float> params_mean;
	for(int i=0; i<771; i++){
		int init =0; 
		params_mean.push_back(init);
	}
	//Look at the charge distributions and its variation over year in individual channel 
  params_mean = trimmed_mean(hcharge); 

	ofstream gas_gain_file; 
	gas_gain_file.open(output_plots_folder+"gas_gain_individual_channel.txt");
	TH1D *h_gas_gain_plus = new TH1D("h_gas_gain_plus", " Gas gain : +endcap : chamber ME11",100,0,1000); 
	TH1D *h_gas_gain_minus = new TH1D("h_gas_gain_minus", " Gas gain : -endcap : chamber ME11",100,0,1000); 
	TH1D *equalized_gas_gain_plus = new TH1D("equalized_gas_gain_plus", " Gas gain : +endcap : chamber : after equalizing ME11",200,0,1000); 
	TH1D *equalized_gas_gain_minus = new TH1D("equalized_gas_gain_minus", " Gas gain : -endcap : chamber: after equalizing ME11",200,0,1000); 

  gas_gain_file<<" Gas gain for individual channel "<<std::endl;
	std::cout<<" trimmed mean for all the channels "<<std::endl;
	for(int h = 1; h < 771 ; h++){
		if(h!=0 && h%10>=7)continue;
    if( (1<= h && h<= 6) || (401<= h && h<=406))continue;
	  // h >7 implies that the one which are extra layers after reduced rechit Id = 366 for chamber36, endcap1, layer6 :
	  // and reducedrechitId = 411 for chamber 1 , endcap 2, layer 1  , we dont want to count them 
    if(h!=0 && h%10==0)continue;
    if(h>370&& h<=400)continue;
	  TString endcap = (h<=400)? "_Endcap1":"_Endcap2";
    int chambernb = (h<=400)?  (int)floor(h/10)  : (int)floor( (h-400) /10) ;
  	// this condition will remove if there are extra chambers between 400 and 410 
    TString rhidshort ="chamber"+ (TString) Form("%d", chambernb)  +"_layer"+ (TString)Form("%d",h%10) + endcap;
    std::cout<<" channel : "<<h<<" rhid : "<<rhidshort<<" charge : "<<params_mean[h]<<std::endl;
    gas_gain_file<<" channel : "<<h<<" rhid : "<<rhidshort<<" charge : "<<params_mean[h]<<std::endl;

		// exclude channel 
		if(rhidshort=="chamber1_layer5_Endcap1" ||rhidshort=="chamber1_layer6_Endcap1" || rhidshort=="chamber19_layer6_Endcap1") continue;
		if(rhidshort=="chamber15_layer2_Endcap2" ||rhidshort=="chamber28_layer3_Endcap2" || rhidshort=="chamber9_layer2_Endcap2") continue;
		// just for testing one channel
		if(params_mean[h] ==0) continue;
	  // Collect this trimmed mean and plot it on a histogram , it should be a gaussian distribution 
		if(endcap=="_Endcap1") h_gas_gain_plus->Fill(params_mean[h]);
		if(endcap=="_Endcap2") h_gas_gain_minus->Fill(params_mean[h]);
	 }

		//Plot the gas gain 
 if(analyzing_plus==true){
	TCanvas * c = new TCanvas("c","gas gain");
	 c->cd();
   h_gas_gain_plus->Draw();
	 gStyle->SetOptStat(000001111);
   c->SaveAs(output_plots_folder+"Gas_gain/Gas_gain_before_eqalizing_plus_endcap.pdf");
   c->Close();
	 h_gas_gain_plus->Write();
 }
 if(analyzing_minus==true){
	 TCanvas * c_1 = new TCanvas("c_1","gas gain");
	 c_1->cd();
   h_gas_gain_minus->Draw();
	 gStyle->SetOptStat(000001111);
   c_1->SaveAs(output_plots_folder+"Gas_gain/Gas_gain_before_eqalizing_minus_endcap.pdf");
   c_1->Close();
	 h_gas_gain_minus->Write();
 }
	 // write the histgoram in a root file

	 float mean_gas_gain_plus = 0, mean_gas_gain_minus = 0;
	 float sigma_gas_gain_plus = 0, sigma_gas_gain_minus = 0;
	  // find average gas gain by fitting it with a gaussian distribution
	  // defining a gaussian distribution
	  TF1 *f1 = new TF1("f1", "gaus",200,500);
		f1->SetParLimits(1,200,450);
		f1->SetParLimits(2,0,100);
		f1->SetParLimits(0,1,30);

	  TF1 *f2 = new TF1("f2", "gaus",160,550);
		f2->SetParLimits(1,200,450);
		f2->SetParLimits(2,0,100);
		f2->SetParLimits(0,1,30);

 if(analyzing_plus==true){
	  TCanvas * c1 = new TCanvas("c1","gas gain with fit");
	  c1->cd();
		h_gas_gain_plus->Fit(f1,"R+");
	  gStyle->SetOptFit();
    h_gas_gain_plus->Draw();
		mean_gas_gain_plus = f1->GetParameter(1);
		sigma_gas_gain_plus = f1->GetParameter(2);
		std::cout<<" mean and sigma from the gaussian fit : mean : +endcap :  "<<mean_gas_gain_plus<<" sigma : "<<sigma_gas_gain_plus<<" normalization "<<f1->GetParameter(0)<<std::endl;
    c1->SaveAs(output_plots_folder+"Gas_gain/Gas_gain_before_eqalizing_plus_endcap_fit.pdf");
    c1->Close();
  }


 if(analyzing_minus==true){
		TCanvas * c2 = new TCanvas("c2","gas gain with fit");
	  c2->cd();
		h_gas_gain_minus->Fit(f2,"R+");
	  gStyle->SetOptFit();
    h_gas_gain_minus->Draw();
		mean_gas_gain_minus = f2->GetParameter(1);
		sigma_gas_gain_minus = f2->GetParameter(2);
		std::cout<<" mean and sigma from the gaussian fit : mean : "<<mean_gas_gain_minus<<" sigma : "<<sigma_gas_gain_minus<<" normalization "<<f2->GetParameter(0)<<std::endl;
    c2->SaveAs(output_plots_folder+"Gas_gain/Gas_gain_before_eqalizing_minus_endcap_fit.pdf");
    c2->Close();
  }

		// Lets test for one channel first

	  // find gas gain in each channel, make a gaussian distribution
    // mean gaus = equalized gas gain : G0
		// G = G0 exp(B(HV-HV0))
		// G = G0 exp(-B*deltaHV0) ; deltaHV0 = HV0-HV
		// G = gas gain for that channel given by params_mean[h], HV0 -> the HV voltage to equalize gas gain 
		float B = 0.00626;
		// HV0 = HV - (1/B) * ln(Q/Qraw)
    // finding HV0 for each individual channel 
	  std::vector<int> HV0;
		for(int i=1; i<771;i++){
      HV0.push_back(0);
		}
		ofstream out_text;
		TString file_name = output_plots_folder+"HV_equalized.txt";
		out_text.open(file_name);

		float eq_gas_gain_plus =0; 
		float eq_gas_gain_minus =0; 

			 //out_text<<std::setw(20)<<"chamber"<<"\t"<<std::setw(10)<<"#Delta HV"<<"\t"<<std::setw(10)<<"HV"<<"\t"<<std::setw(10)<<"chamber"<<"\t"<<std::setw(10)<<"layer"<<"\t"<<std::endl;
			 out_text<<std::setw(22)<<"chamber"<<std::setw(10)<<"#Delta HV"<<std::setw(10)<<"HV"<<std::setw(10)<<"chamber"<<std::setw(10)<<"layer"<<std::setw(10)<<"Endcap"<<std::endl;
		float delta_HV0_value = 0;
			TString t; 
			int sign;
	 	 for(int h = 1; h < 771 ; h++){
    	if(h!=0 && h%10>=7)continue;
      if( (1<= h && h<= 6) || (401<= h && h<=406))continue;
	 	  // h >7 implies that the one which are extra layers after reduced rechit Id = 366 for chamber36, endcap1, layer6 :
		  // and reducedrechitId = 411 for chamber 1 , endcap 2, layer 1  , we dont want to count them 
      if(h!=0 && h%10==0)continue;
      if(h>370&& h<=400)continue;
		  TString endcap = (h<=400)? "_Endcap1":"_Endcap2";
			if(endcap=="_Endcap1")  t="+endcap";
			if(endcap=="_Endcap2")  t="-endcap";
      int chambernb = (h<=400)?  (int)floor(h/10)  : (int)floor( (h-400) /10) ;
  		// this condition will remove if there are extra chambers between 400 and 410 
      TString rhidshort ="chamber"+ (TString) Form("%d", chambernb)  +"_layer"+ (TString)Form("%d",h%10) + endcap;

       if(endcap=="_Endcap1") delta_HV0_value = - (1./B) * TMath::Log(params_mean[h]/mean_gas_gain_plus);
       if(endcap=="_Endcap2") delta_HV0_value = - (1./B) * TMath::Log(params_mean[h]/mean_gas_gain_minus);
       HV0[h] = 2900 +delta_HV0_value;
			 		// exclude channel 
		if(rhidshort=="chamber1_layer5_Endcap1" ||rhidshort=="chamber1_layer6_Endcap1" || rhidshort=="chamber19_layer6_Endcap1") continue;
		if(rhidshort=="chamber15_layer2_Endcap2" ||rhidshort=="chamber28_layer3_Endcap2" || rhidshort=="chamber9_layer2_Endcap2") continue;
	
			 if(endcap=="_Endcap1") { 
				 eq_gas_gain_plus = mean_gas_gain_plus * exp(-B *delta_HV0_value) ;
				 //sign = TMath::Sign(1,delta_HV0_value);
         gas_gain_file<<" channel : "<<h<<" rhid : "<<rhidshort<<" charge : "<<params_mean[h]<<std::endl;
				 equalized_gas_gain_plus->Fill(eq_gas_gain_plus);
				 }
		   if(endcap=="_Endcap2") {
				 eq_gas_gain_minus = mean_gas_gain_minus * exp(-B *delta_HV0_value);
         gas_gain_file<<" channel : "<<h<<" rhid : "<<rhidshort<<" charge : "<<params_mean[h]<<std::endl;
				 equalized_gas_gain_minus->Fill(eq_gas_gain_minus); 
				// sign = TMath::Sign(1,delta_HV0_value);
				 }

			 std::cout<<"channel :"<<h<<" rhid : "<<rhidshort<<"  #Delta HV = "<<delta_HV0_value<<" HV : "<<HV0[h]<<std::endl;
			 TString chamber_string = "CSC_ME_P11_C"+(TString)Form("%d",chambernb); 
			 out_text<<std::setw(22)<<rhidshort<<std::setw(10)<<round(delta_HV0_value)<<std::setw(10)<<HV0[h]<<std::setw(20)<<chamber_string<<std::setw(10)<<(TString)Form("%d",h%10)<<std::setw(10)<<t<<std::endl;


		 }

		 // Plot gas gain after equalization
		 //

 if(analyzing_plus==true){
  	  TCanvas * c3 = new TCanvas("c3","gas gain with fit");
	  c3->cd();
		equalized_gas_gain_plus->Draw();
	  gStyle->SetOptStat();
    c3->SaveAs(output_plots_folder+"Gas_gain/Gas_gain_after_eqalizing_plus_endcap.pdf");
    c3->Close();
 }

 if(analyzing_minus==true){
		TCanvas * c4 = new TCanvas("c4","gas gain with fit");
	  c4->cd();
	  equalized_gas_gain_minus->Draw();
	  gStyle->SetOptStat();
    c4->SaveAs(output_plots_folder+"Gas_gain/Gas_gain_after_eqalizing_minus_endcap.pdf");
    c4->Close();
 }

/*		 TH1D *hcharge_special_chamber9_layer2_endcap2_first = new TH1D("hcharge_special_chamber9_layer2_endcap2_first","",200,0,1000);
		 TH1D *hcharge_special_chamber9_layer2_endcap2_second = new TH1D("hcharge_special_chamber9_layer2_endcap2_second","",200,0,1000);
		// Making plots for chamber9 layer2 Endcap2 bins with less gas gain
	   for(int i = 0; i < tree->GetEntries(); i++){
     // std::cout<<"entered into integratedlumi loop correction "<<i<<std::endl; 
		 //if(_integratelumi==0) continue;
     // std::cout<<"case for which integratedlumi correction exists "<<i<<std::endl; 
     //if(i%100 !=0 &&istest) continue;
     LoadTree(i);tree->GetEntry(i);
     if(i%1000000 ==0)cout << i<<endl;
     //if(badrun(_runNb) ) continue;
     //if(check7to9e33only  &&_instlumi<8000 ) continue;
     //if(check7to9e33only  &&_instlumi>14000 ) continue;
     // what is significance of this ?
		 //if(check7to9e33only) _integratelumi -= 17000;
     int rhidreduced = ((int)floor(_rhid/10))%1000;
     if(_rhid> 2000000) rhidreduced +=400;
     //int idforcorr = (iszmumu )? 0: rhidreduced ;

		 if(6<= _integratelumi && _integratelumi<7){
		 hcharge_special_chamber9_layer2_endcap2_first->Fill(_rhsumQ_RAW);
		 }
		 if(22<= _integratelumi && _integratelumi<23){
		 hcharge_special_chamber9_layer2_endcap2_second->Fill(_rhsumQ_RAW);
     }
   }
		 float parameter_special_first;
		 float parameter_special_second;
		 // find the bins for which integratelumi lies in some range and fill those in a plot and find trim mean for those special bins
		 parameter_special_first = trimmed_mean_special(hcharge_special_chamber9_layer2_endcap2_first,9,2,2);
		 parameter_special_first = trimmed_mean_special(hcharge_special_chamber9_layer2_endcap2_second,9,2,2);

		 std::cout<<"special parameter gas gain chamber9, layer 2 endcap2"<<parameter_special_first<<" : "<<parameter_special_second<<std::endl;
*/	
}
std::vector<float> equalizing_gas_gain_plus_minus :: trimmed_mean(TH2D *myh){
    
		 std::vector <float> result ; //Assume that fitted function has two parameters
     for(int i = 0; i<771;i++){
      float initpair = 0; 
      result.push_back(initpair);}
     ofstream charge_file;
		 charge_file.open(output_plots_folder+"charge_before_after_trim.txt"); 
  
	 	 for(int h = 1; h < 771 ; h++){
      //Skipping empty entries
      if( (1<= h && h<= 6) || (401<= h && h<=406))continue;
      if(h!=0 && h%10>=7)continue;
	 	  // h >7 implies that the one which are extra layers after reduced rechit Id = 366 for chamber36, endcap1, layer6 :
		  // and reducedrechitId = 411 for chamber 1 , endcap 2, layer 1  , we dont want to count them 
      if(h!=0 && h%10==0)continue;
      if(h>370&& h<=400)continue;
      //N.B.: h=0 takes all rechits together 
    
  		TString endcap = (h<=400)? "_Endcap1":"_Endcap2";
      int chambernb = (h<=400)?  (int)floor(h/10)  : (int)floor( (h-400) /10) ;
  		// this condition will remove if there are extra chambers between 400 and 410 
      TString rhidshort ="chamber"+ (TString) Form("%d", chambernb)  +"_layer"+ (TString)Form("%d",h%10) + endcap;
      //Declare histo to store trimmed mean for different values of the variable of interest (pressure, inst L,...)
      TH1D* proj_charge = myh->ProjectionX("_px", h, h) ;  
      proj_charge->SetName("charge_before_equalizing_"+rhidshort );
 
		 // plot initial charge for few bins
		 if(rhidshort=="chamber10_layer2_Endcap1" ||rhidshort=="chamber12_layer1_Endcap2"){ 
      TCanvas *c = new TCanvas("c", "Charge in chamber ");
			c->cd();
			proj_charge->Draw();
			gStyle->SetOptStat(001111111);
			c->SaveAs(gas_gain_plots+"charge_initial_total_"+rhidshort+".pdf");
			c->Close();
		 }	 
     TH1D * h_trim = (TH1D*) proj_charge->Clone();
  	 h_trim->Reset();
  	 h_trim->ResetStats();
		 // the trim histogram should have new stats
		 float normal = proj_charge->Integral();
		 float integral =0;
		 int last_bin = 0;
     for(int it = 1; it<=   proj_charge->GetNbinsX() ;it++) {
		    if(integral < trimmean * normal){
		 	   integral+=proj_charge->GetBinContent(it);	
		 		 last_bin =it;
		 	 }
      }
		 double new_integral =0; 
		 int entries_last_bin;
		 for(int it=1; it<last_bin; it++){
  			h_trim->SetBinContent(it,proj_charge->GetBinContent(it));
				h_trim->SetBinError(it,proj_charge->GetBinError(it));
		 	  new_integral += proj_charge->GetBinContent(it); 
		 }
		 entries_last_bin = (int) (trimmean*normal - new_integral); 
		  std::cout<<"entries in last bin : rhid"<<rhidshort<<" bin number"<<" before : "<<proj_charge->GetBinContent(last_bin)<<" after :"<<entries_last_bin<<std::endl;
			h_trim->SetBinContent(last_bin, entries_last_bin);
		  h_trim->SetBinError(last_bin, proj_charge->GetBinError(last_bin));
		  for(int it=last_bin+1; it<=proj_charge->GetNbinsX() ; it++) {
				h_trim->SetBinContent(it,0);
				h_trim->SetBinError(it,0);
			}
			gStyle->SetStatW(0.2); // Set the width of the statistics box (0.2 corresponds to 20% of the canvas width)
			gStyle->SetStatH(0.1); // Set the height of the statistics box (0.1 corresponds to 10% of the canvas height)
		  // Adjust the position of the statistics box
		  gStyle->SetStatX(0.9); // Set the x-position of the statistics box (0.7 corresponds to 70% of the canvas width)
			gStyle->SetStatY(0.9);


/*		 if(rhidshort=="chamber10_layer2_Endcap1" ||rhidshort=="chamber12_layer1_Endcap2"){ 
      TCanvas *c1 = new TCanvas("c1", "Charge in chamber after trimming ");
			c1->cd();
			h_trim->Draw();
			c1->Update();
			gStyle->SetOptStat(111111111);
			c1->SaveAs(gas_gain_plots+"charge_initial_total_"+rhidshort+"_after_trimming.pdf");
		 }	 
			
		 if(h_trim->GetMean() <200 || h_trim->GetMean() > 450){ 
      gStyle->SetStatW(0.2); // Set the width of the statistics box (0.2 corresponds to 20% of the canvas width)
			gStyle->SetStatH(0.1); // Set the height of the statistics box (0.1 corresponds to 10% of the canvas height)
		  // Adjust the position of the statistics box
		  gStyle->SetStatX(0.9); // Set the x-position of the statistics box (0.7 corresponds to 70% of the canvas width)
			gStyle->SetStatY(0.9);


      TCanvas *c2 = new TCanvas("c2", "Charge in chamber after trimming ");
			c2->cd();
			h_trim->Draw();
			c2->Update();
			gStyle->SetOptStat(111111111);
			c2->SaveAs(gas_gain_plots+"outliers_charge_initial_total_"+rhidshort+"_after_trimming.pdf");
  
			gStyle->SetStatW(0.2); // Set the width of the statistics box (0.2 corresponds to 20% of the canvas width)
			gStyle->SetStatH(0.1); // Set the height of the statistics box (0.1 corresponds to 10% of the canvas height)
		  // Adjust the position of the statistics box
		  gStyle->SetStatX(0.9); // Set the x-position of the statistics box (0.7 corresponds to 70% of the canvas width)
			gStyle->SetStatY(0.9);

    
			TCanvas *c3 = new TCanvas("c3", "Charge in chamber after trimming ");
			c3->cd();
		  proj_charge->Draw();
			c3->Update();
			gStyle->SetOptStat(111111111);
			c3->SaveAs(gas_gain_plots+"outliers_charge_initial_total_"+rhidshort+"_before_trimming.pdf");

		 }
			gStyle->SetStatW(0.2); // Set the width of the statistics box (0.2 corresponds to 20% of the canvas width)
			gStyle->SetStatH(0.1); // Set the height of the statistics box (0.1 corresponds to 10% of the canvas height)
		  // Adjust the position of the statistics box
		  gStyle->SetStatX(0.9); // Set the x-position of the statistics box (0.7 corresponds to 70% of the canvas width)
			gStyle->SetStatY(0.9);

  
		 // storing all values
      TCanvas *c_1 = new TCanvas("c_1", "Charge in chamber after trimming ");
			c_1->cd();
			h_trim->Draw();
			c_1->Update();
			gStyle->SetOptStat(111111111);
			c_1->SaveAs(gas_gain_plots_all+"charge_initial_total_"+rhidshort+"_after_trimming.pdf");
  
			gStyle->SetStatW(0.2); // Set the width of the statistics box (0.2 corresponds to 20% of the canvas width)
			gStyle->SetStatH(0.1); // Set the height of the statistics box (0.1 corresponds to 10% of the canvas height)
		  // Adjust the position of the statistics box
		  gStyle->SetStatX(0.9); // Set the x-position of the statistics box (0.7 corresponds to 70% of the canvas width)
			gStyle->SetStatY(0.9);

      
			TCanvas *c_2 = new TCanvas("c_2", "Charge in chamber after trimming ");
			c_2->cd();
		  proj_charge->Draw();
			c_2->Update();
			gStyle->SetOptStat(111111111);
			c_2->SaveAs(gas_gain_plots_all+"charge_initial_total_"+rhidshort+"_before_trimming.pdf");
*/
     std::cout<<" Charge before trimming in "<<rhidshort<<" : charge : "<<proj_charge->GetMean()<<" after trimming : "<<h_trim->GetMean()<<std::endl;		 
     charge_file<<" Charge before trimming in "<<rhidshort<<" : charge : "<<proj_charge->GetMean()<<" after trimming : "<<h_trim->GetMean()<<std::endl;		 
		 float final_integral = new_integral+entries_last_bin;
		 result[h] = h_trim->GetMean();
		} 
	  return result; 
	} 
/*
float equalizing_gas_gain_plus_minus :: trimmed_mean_special(TH1D *myh,int chambernb,int endcap,int layer){
    
		 float result =0 ; //Assume that fitted function has two parameters
      //Skipping empty entries
      
      TString rhidshort ="chamber"+ (TString) Form("%d", chambernb)  +"_layer"+ (TString)Form("%d",layer) + (TString) Form("%d",endcap);
      //Declare histo to store trimmed mean for different values of the variable of interest (pressure, inst L,...)
      TH1D* proj_charge = (TH1D*) myh->Clone() ;  
      proj_charge->SetName("charge_before_equalizing_"+rhidshort );
 
     TH1D * h_trim = (TH1D*) proj_charge->Clone();
  	 h_trim->Reset();
  	 h_trim->ResetStats();
		 // the trim histogram should have new stats
		 float normal = proj_charge->Integral();
		 float integral =0;
		 int last_bin = 0;
     for(int it = 1; it<=   proj_charge->GetNbinsX() ;it++) {
		    if(integral < trimmean * normal){
		 	   integral+=proj_charge->GetBinContent(it);	
		 		 last_bin =it;
		 	 }
      }
		 double new_integral =0; 
		 int entries_last_bin;
		 for(int it=1; it<last_bin; it++){
  			h_trim->SetBinContent(it,proj_charge->GetBinContent(it));
				h_trim->SetBinError(it,proj_charge->GetBinError(it));
		 	  new_integral += proj_charge->GetBinContent(it); 
		 }
		 entries_last_bin = (int) (trimmean*normal - new_integral); 
		  std::cout<<"entries in last bin : rhid"<<rhidshort<<" bin number"<<" before : "<<proj_charge->GetBinContent(last_bin)<<" after :"<<entries_last_bin<<std::endl;
			h_trim->SetBinContent(last_bin, entries_last_bin);
		  h_trim->SetBinError(last_bin, proj_charge->GetBinError(last_bin));
		  for(int it=last_bin+1; it<=proj_charge->GetNbinsX() ; it++) {
				h_trim->SetBinContent(it,0);
				h_trim->SetBinError(it,0);
			}
			gStyle->SetStatW(0.2); // Set the width of the statistics box (0.2 corresponds to 20% of the canvas width)
			gStyle->SetStatH(0.1); // Set the height of the statistics box (0.1 corresponds to 10% of the canvas height)
		  // Adjust the position of the statistics box
		  gStyle->SetStatX(0.9); // Set the x-position of the statistics box (0.7 corresponds to 70% of the canvas width)
			gStyle->SetStatY(0.9);

			gStyle->SetOptStat(111111111);
      TCanvas *c2 = new TCanvas("c2", "Charge in chamber before trimming ");
			c2->cd();
			proj_charge->Draw();
			c2->Update();
			gStyle->SetOptStat(111111111);
			c2->SaveAs(gas_gain_plots+"special_charge_initial_total_"+rhidshort+"_before_trimming.pdf");

			gStyle->SetOptStat(111111111);
      TCanvas *c1 = new TCanvas("c1", "Charge in chamber after trimming ");
			c1->cd();
			h_trim->Draw();
			c1->Update();
			gStyle->SetOptStat(111111111);
			c1->SaveAs(gas_gain_plots+"special_charge_initial_total_"+rhidshort+"_after_trimming.pdf");
		  result = h_trim->GetMean();
	  return result; 
	} */ 

