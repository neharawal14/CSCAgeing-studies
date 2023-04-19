// it take each chamber variation of charge with pressure and inst lumi, and then take ratio with the corresponding chamnber of charge with pressure and instlumi for ME13HV3. 
// After taking ratio, we obtain another set of normalized distributions which we can see varying with pressure and instlumi values. 
// We fit this distributions with a straight line and obtain slopes for each chamber into an output root file
#include <iostream>
void intlumi_only_goodchannels(TString chamber){
//void intlumi_only_goodchannels(){
  TString input_file_chamber; 
  //TString input_file_chamber[32]; 
  TFile *file;	
  TFile *file_ref;	
  
	 bool debug = true;

	 TH1D *hist_slope_integratelumi;
   TH1D* integratelumi; 
   TH1D *integratelumi_ME13HV3;
   TH1D *new_integratelumi = new TH1D("new_integratlumi", " Normalized trimmed mean charge wrt ME13HV3 ref",45,0,45);
 
 	 TGraphErrors *graph_slope_integratelumi_chamber;


	TString input_file_path = "/cmsuf/data/store/user/t2/users/neha.rawal/CSCAgeing_2022/analysis_2022/2022_output_files/";
	TString result_path = "/cmsuf/data/store/user/t2/users/neha.rawal/CSCAgeing_2022/analysis_2022/analysis_gas_gain/systematic_study/result_systematic_intlumi/"; 
 	TFile *output_file = new TFile(result_path+"/output_file_"+chamber+".root","RECREATE");
   
  TString input_file_ref = input_file_path+ "outf_dataset25to36fbonly_ME13HV3_output.root";
	file_ref = TFile::Open(input_file_ref);
	TDirectory *dir_intlumi_ref = (TDirectory*) file_ref->Get("_integratelumi"); if(debug) std::cout<<"after opening root file"<<std::endl;
  if(debug) std::cout<<"goijng to start the loop"<<std::endl;
  TDirectory * dir_intlumi;
 	float new_hist_value = 0;
 	float new_hist_value_error = 0;

    	input_file_chamber = input_file_path + "outf_dataset25to36fbonly_"+chamber+"_output.root";
      std::cout<<"filename "<<input_file_chamber<<std::endl;	
    	
    	file = TFile::Open(input_file_chamber);
      std::cout<<"issue after opening file"<<std::endl;
     	dir_intlumi = (TDirectory*) file->Get("_integratelumi");
     	dir_intlumi->cd();
    	std::cout<<"input file "<<file<<std::endl;
     
          TString hist_org_name = "_dataset25to36fbonlytrimmean_allgoodchannelsvs_integratelumi";
          TString hist_ref_name = TString::Format("_dataset25to36fbonlytrimmean_allgoodchannelsvs_integratelumi");
          integratelumi_ME13HV3 = (TH1D*) dir_intlumi_ref->Get(hist_ref_name);

      	  std::cout<<" histogram name org "<<hist_org_name<<std::endl;
      	  std::cout<<" histogram name ref "<<hist_ref_name<<std::endl;
				  
          integratelumi = (TH1D*) dir_intlumi->Get(hist_org_name);

					// Plot the luminosity in a different range between 0.9 and 1.1
			TCanvas *c  = new TCanvas("c","int lumi");
			c->cd();
			integratelumi->GetYaxis()->SetRangeUser(0.9,1.1);
			integratelumi->Draw();
			c->SaveAs(result_path+"integratelumi_before_correction"+chamber+".pdf");
    
			TLegend *legend = new TLegend(0.7,0.7,0.9,0.9);
      legend->AddEntry(integratelumi,chamber,"l");
	    legend->AddEntry(integratelumi_ME13HV3,"ME13HV3","l");

      TCanvas *c1  = new TCanvas("c1","int lumi");
			c1->cd();
			integratelumi_ME13HV3->GetYaxis()->SetRangeUser(0.9,1.1);
			integratelumi_ME13HV3->Draw();
			integratelumi_ME13HV3->SetLineColor(kRed);
			integratelumi_ME13HV3->SetMarkerColor(kRed);
			integratelumi_ME13HV3->SetTitle("Normalized charge "+chamber+" : ME13HV3");
			integratelumi->Draw("same");
			integratelumi->SetStats(0);
			integratelumi_ME13HV3->SetStats(0);
			integratelumi->SetLineColor(kBlue);
			integratelumi->SetMarkerColor(kBlue);

		  legend->Draw();
			c1->SaveAs(result_path+"integratelumi_before_correction"+chamber+".pdf");
	//std::cout<<" taking rations  "<<hist_slope_integratelumi[i]->GetNbinsX()<<std::endl;
	//std::cout<<" taking rations ME13HV3 "<<hist_slope_integratelumi_13HV3[i]->GetNbinsX()<<std::endl;
	    std::cout<<"total bins  "<<integratelumi->GetNbinsX()<<std::endl;
      

   	for(int j=1; j<= integratelumi->GetNbinsX()+1 ; j++){

	    std::cout<<"loop value "<<j<<std::endl;
  		std::cout<<"checking loop thigs here"<<std::endl;	

	    if (integratelumi->GetBinContent(j) == 0 || integratelumi_ME13HV3->GetBinContent(j) ==0) continue;
      new_hist_value = integratelumi->GetBinContent(j)/integratelumi_ME13HV3->GetBinContent(j);
	    new_hist_value_error =  new_hist_value * sqrt(pow(integratelumi->GetBinError(j)/integratelumi->GetBinContent(j),2) +pow(integratelumi_ME13HV3->GetBinError(j)/integratelumi_ME13HV3->GetBinContent(j),2) ) ;
 // new_hist_value = j;
//			file_ME13HV3<<"bin "<<j<<" ME13HV3 int lumi "<<integratelumi_ME13HV3->GetBinContent(j)<<"chamber value "<<integratelumi.at(i)->GetBinContent(j)<<" ratio "<<new_hist_value<<" error "<<new_hist_value_error<<std::endl;
	    std::cout<<integratelumi->GetBinContent(j)<<std::endl;	
	    std::cout<<integratelumi_ME13HV3->GetBinContent(j)<<std::endl;	
	    std::cout<<" in loop evaluting  rations  "<<new_hist_value<<std::endl;
	    std::cout<<" in loop evaluting  ration error  "<<new_hist_value_error<<std::endl;
      new_integratelumi->SetBinContent(j,new_hist_value);
	  	new_integratelumi->SetBinError(j,new_hist_value_error);
	 }
  
	std::cout<<" reached canvas here "<<std::endl;
TCanvas *c_intlumi = new TCanvas();
  gStyle->SetOptFit(0111);
//	for(int i=0; i<3; i++){
//		if(channels_total
   c_intlumi->cd();
/*   new_integratelumi.at(i)->GetXaxis()->SetTitle("integrated luminoisty (fb^{-1})");
   new_integratelumi.at(i)->GetYaxis()->SetTitle("Trim mean charge/ME13HV3 ref");
	 new_integratelumi.at(i)->SetMarkerStyle(kFullCircle);
   new_integratelumi.at(i)->Draw("PE"); */
   //c_intlumi->SaveAs(result_path+chamber+"/slope_intlumi_"+channel_nb+".pdf");
			new_integratelumi->SetTitle("Normalized charge "+chamber+" : ME13HV3");
   new_integratelumi->GetXaxis()->SetTitle("integrated luminoisty (fb^{-1})");
   new_integratelumi->GetYaxis()->SetTitle("Trim mean charge/ME13HV3 ref");
   new_integratelumi->GetYaxis()->SetRangeUser(0.9,1.1);
   new_integratelumi->SetMarkerStyle(kFullCircle);
   new_integratelumi->SetMarkerSize(0.6);
//   new_integratelumi.at(i).Fit(f1,"R");
   new_integratelumi->Draw("PE");
  
 TString string_saving ="all_good_channels_"+chamber+".pdf";
	// TString string_saving = TString::Format("/slope_intlumi_%d.pdf",channel);
   c_intlumi->SaveAs(result_path+string_saving);
	 c_intlumi->Clear();
//   c_intlumi->Close();


 //file_ME13HV3.close();
 std::cout<<"************************************"<<std::endl;
  
//	if(debug) std::cout<<" bin number and the setted mean value for pressure "<<i<<" mean "<<mean_slope_pressure[i]<<" chamber[i] "<<chamber[i]<<std::endl;
  
output_file->cd();
new_integratelumi->SetName("intlumi_only_goodchannels");
   new_integratelumi->Write();
	 output_file->Close();
 // file->Close();
  //hist_slope_pressure[i]->Write();	
	//hist_slope_instlumi[i]->Write();
	}
