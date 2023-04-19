// it take each chamber variation of charge with pressure and inst lumi, and then take ratio with the corresponding chamnber of charge with pressure and instlumi for ME13HV3. 
// After taking ratio, we obtain another set of normalized distributions which we can see varying with pressure and instlumi values. 
// We fit this distributions with a straight line and obtain slopes for each chamber into an output root file

void systematic_evaluation(TString chamber, int channels_total, float channel_nb){

  TString input_file_chamber; 
  //TString input_file_chamber[32]; 
  TFile *file;	
  TFile *file_ref;	
	//TFile *file[2];
  //TString chamber[2] = {"ME11a", "ME11b", "ME12HV1", "ME12HV2", "ME12HV3", "ME13HV1", "ME13HV2", "ME13HV3", "ME21HV1", "ME21HV2", "ME21HV3", "ME22HV1", "ME22HV2", "ME22HV3", "ME22HV4", "ME22HV5", "ME31HV1", "ME31HV2", "ME31HV3", "ME2HV1", "ME2HV2", "ME2HV3", "ME2HV4", "ME2HV5", "ME41HV1", "ME41HV2" ,"ME41HV3", "ME42HV1", "ME42HV2", "ME42HV3", "ME42HV4", "ME42HV5"}; 
//  TString chamber[2] = {"ME12HV1"}; 
 //TString chamber[32] = {"ME11a", "ME11b", "ME12HV1", "ME12HV2","ME12HV3", "ME13HV1","ME13HV2","ME13HV3","ME21HV1","ME21HV2", "ME21HV3", "ME22HV1", "ME22HV2", "ME22HV3", "ME22HV4","ME22HV5","ME31HV1","ME31HV2", "ME31HV3", "ME32HV1", "ME32HV2", "ME32HV3", "ME32HV4","ME32HV5","ME41HV1","ME41HV2", "ME41HV3", "ME42HV1", "ME42HV2", "ME42HV3", "ME42HV4","ME42HV5" }; 
// TString chamber[2] = {"ME11a", "ME11b" }; 
   
	 bool debug = true;

	 TH1D *hist_slope_integratelumi;
	 TH1D *hist_slope_integratelumi_ME13HV3;
   std::vector<TH1D*> integratelumi; 
   std::vector<TH1D*> integratelumi_ME13HV3;
   std::vector<TH1D> new_integratelumi;
   TH1D hist_new_integratelumi("hist_new_integratlumi", " Normalized trimmed mean charge wrt ME13HV3 ref",45,0,45);
   for(int i=0; i<channels_total; i++){
//		 TString new_integratelumi_string = TString::Format("hist_new_integratelumi[%d]",i);
//     hist_new_integratelumi[i] = new TH1D(new_integratlumi_string, " Normalized trimmed mean charge wrt ME13HV3 ref",45,0,45);
//    integratelumi.push_back(hist_integratelumi); 
//    integratelumi_ME13HV3.push_back(hist_integratelumi_ME13HV3); 
    new_integratelumi.push_back(hist_new_integratelumi); 
   }	
/*		TH1D *hist_slope_integratelumi[32];
  TH1D *hist_new_integratelumi[32];

	TH1D *hist_slope_integratelumi[432];
	TH1D *hist_slope_integratelumi_13HV3[2];
  TH1D *hist_new_integratelumi[2];
 TString hist_new_integratelumi_string;
	for(int i=0; i<2; i++){
		hist_new_integratelumi_string = TString::Format("hist_new_integartelumi[%d]",i);
    hist_new_integratelumi[i] = new TH1D(hist_new_integratelumi_string, " Normalized trimmed mean charge wrt ME13HV3 ref",45,0,45);
	}
*/
 // TGraphErrors *graph_slope_integratelumi_chamber_initial;
	TGraphErrors *graph_slope_integratelumi_chamber;


	TString input_file_path = "/cmsuf/data/store/user/t2/users/neha.rawal/CSC_2017_data_RAW_RECO/nTuple_output/2017/output_ntuples/output_root_files/";
	TString result_path = "/cmsuf/data/store/user/t2/users/neha.rawal/CSC_2017_data_RAW_RECO/nTuple_output/2017/analyzing_gas_gain/systematic_study/results/"; 
 	TFile *output_file = new TFile(result_path+chamber+"/output_file.root","RECREATE");
   
  TTree *tree_intlumi = new TTree("tree_intlumi",""); 
  Float_t slope, slope_error,chi2;
  Int_t  ndf;
  tree_intlumi->Branch("slope",&slope, "slope/F");
  tree_intlumi->Branch("slope_error",&slope_error, "slope_error/F");
  tree_intlumi->Branch("chi2",&chi2, "chi2/F");
  tree_intlumi->Branch("ndf",&ndf, "ndf/I");
	
	TString input_file_ref = input_file_path+ "outfDUMMYFILENAME_2017_new_all_ME13HV3_tree14to26fbonly_7e33to9e33.root";
	file_ref = TFile::Open(input_file_ref);
	TDirectory *dir_intlumi_ref = (TDirectory*) file_ref->Get("_integratelumi"); if(debug) std::cout<<"after opening root file"<<std::endl;
  if(debug) std::cout<<"goijng to start the loop"<<std::endl;
  TDirectory * dir_intlumi;
 	float new_hist_value = 0;
 	float new_hist_value_error = 0;

    	input_file_chamber = input_file_path + "outfDUMMYFILENAME_2017_new_all_"+chamber+"_tree14to26fbonly_7e33to9e33.root";
      std::cout<<"filename "<<input_file_chamber<<std::endl;	
    	
    	file = TFile::Open(input_file_chamber);
      std::cout<<"issue after opening file"<<std::endl;
     	dir_intlumi = (TDirectory*) file->Get("_integratelumi");
     	dir_intlumi->cd();
    	std::cout<<"input file "<<file<<std::endl;
     
    	std::cout<<"example file name : DUMMYFILENAME_2017_new_all_ME13HV1_tree14to26fbonly_7e33to9e33trimmean_chamber34_layer4_Endcap2vs_integratelumi"<<std::endl;
 int layer_nb = 6;
int endcap_nb =2;  
  for(int channel=1; channel<=channel_nb;channel++){
			 for(int endcap=1; endcap<=endcap_nb; endcap++){ 
        for(int layer=1; layer<=layer_nb;layer++){
          TString hist_org_name = TString::Format("DUMMYFILENAME_2017_new_all_"+chamber+"_tree14to26fbonly_7e33to9e33trimmean_chamber%d_layer%d_Endcap%dvs_integratelumi",channel,layer,endcap);
          TString hist_ref_name = TString::Format("DUMMYFILENAME_2017_new_all_ME13HV3_tree14to26fbonly_7e33to9e33trimmean_chamber%d_layer%d_Endcap%dvs_integratelumi",channel,layer,endcap);

      	  std::cout<<" histogram name org "<<hist_org_name<<std::endl;
      	  std::cout<<" histogram name ref "<<hist_ref_name<<std::endl;
				  
          integratelumi.push_back( (TH1D*) dir_intlumi->Get(hist_org_name));
          integratelumi_ME13HV3.push_back((TH1D*) dir_intlumi_ref->Get(hist_ref_name));
			 }
     }
 } 
  

	//std::cout<<" taking rations  "<<hist_slope_integratelumi[i]->GetNbinsX()<<std::endl;
	//std::cout<<" taking rations ME13HV3 "<<hist_slope_integratelumi_13HV3[i]->GetNbinsX()<<std::endl;
  std::cout<<"channel totla "<<channels_total<<std::endl;
	for(int i =0; i<channels_total; i++){
//	for(int i =0; i<3; i++){
			if(integratelumi.at(i)==NULL || integratelumi_ME13HV3.at(i) == NULL) { std::cout<<"print channel .........................................................................................................        number not there "<<i<<std::endl; 
				continue;}
	    std::cout<<"channel number  "<<i<<std::endl;
	    std::cout<<"total bins  "<<integratelumi.at(i)->GetNbinsX()<<std::endl;
      

   	for(int j=1; j<= integratelumi.at(i)->GetNbinsX()+1 ; j++){

	    std::cout<<"loop value "<<j<<std::endl;
  		std::cout<<"checking loop thigs here"<<std::endl;	

	    if (integratelumi.at(i)->GetBinContent(j) == 0 || integratelumi_ME13HV3.at(i)->GetBinContent(j) ==0) continue;
      new_hist_value = integratelumi.at(i)->GetBinContent(j)/integratelumi_ME13HV3.at(i)->GetBinContent(j);
	    new_hist_value_error =  new_hist_value * sqrt(pow(integratelumi.at(i)->GetBinError(j)/integratelumi.at(i)->GetBinContent(j),2) +pow(integratelumi_ME13HV3.at(i)->GetBinError(j)/integratelumi_ME13HV3.at(i)->GetBinContent(j),2) ) ;
 // new_hist_value = j;
	    std::cout<<integratelumi.at(i)->GetBinContent(j)<<std::endl;	
	    std::cout<<integratelumi_ME13HV3.at(i)->GetBinContent(j)<<std::endl;	
	    std::cout<<" in loop evaluting  rations  "<<new_hist_value<<std::endl;
	    std::cout<<" in loop evaluting  ration error  "<<new_hist_value_error<<std::endl;
      new_integratelumi.at(i).SetBinContent(j,new_hist_value);
	  	new_integratelumi.at(i).SetBinError(j,new_hist_value_error);
	 }
		std::cout<<"done with channel loop"<<std::endl;
	}
  
	std::cout<<" reached canvas here "<<std::endl;
	std::cout<<"length of new integratelumi "<<new_integratelumi.size()<<std::endl;
  for(int i=0; i<3;i++){	
	std::cout<<" new integratelumi hist size "<<new_integratelumi.at(i).GetEntries()<<std::endl;
	}
	int chamber_number;
	int layer_number;
	int endcap_number;

  // if(thevar.Index("pressure")>=0)fa1= new TF1("f1","expo", fitlowedge,fithighedge ); 
  //else if(thevar.Index("instlumi")>=0)fa1= new TF1("f1","expo", fitlowedge,fithighedge );                                                                                                                                                                               
  TF1 *f1= new TF1("f1","pol1", 0,45);  
	f1->SetParNames("Constant","Slope");
	TCanvas *c_intlumi = new TCanvas("c_intlumi","int lumi plot of i th file after pressure and instlumi  correction",700,700);
	int channel;
  gStyle->SetOptFit(0111);
	for(int i=0; i<channels_total; i++){
//	for(int i=0; i<3; i++){
//		if(channels_total
   c_intlumi->cd();
/*   new_integratelumi.at(i)->GetXaxis()->SetTitle("integrated luminoisty (fb^{-1})");
   new_integratelumi.at(i)->GetYaxis()->SetTitle("Trim mean charge/ME13HV3 ref");
	 new_integratelumi.at(i)->SetMarkerStyle(kFullCircle);
   new_integratelumi.at(i)->Draw("PE"); */
   //c_intlumi->SaveAs(result_path+chamber+"/slope_intlumi_"+channel_nb+".pdf");
   new_integratelumi.at(i).GetXaxis()->SetTitle("integrated luminoisty (fb^{-1})");
   new_integratelumi.at(i).GetYaxis()->SetTitle("Trim mean charge/ME13HV3 ref");
   new_integratelumi.at(i).GetYaxis()->SetRangeUser(0.5,1.5);
   new_integratelumi.at(i).SetMarkerStyle(kFullCircle);
   new_integratelumi.at(i).Fit(f1,"R");
   new_integratelumi.at(i).Draw("PE");
  
   channel = i+1;
   chamber_number = (channel%12==0) ? channel/12 : channel/12+1 ; 
	 endcap_number = ( (channel%12) >6 || channel%12==0) ?  2 : 1 ;
	 layer_number = ( channel%6==0 || channel%12==0) ? 6 : channel%6;

	 TString string_saving = TString::Format("/slope_intlumi_chamber%d_layer%d_endcap%d.pdf",chamber_number,layer_number, endcap_number);
	// TString string_saving = TString::Format("/slope_intlumi_%d.pdf",channel);
	 std::cout<<"saving string name for value :  "<<channel<<" : "<<string_saving<<std::endl;
   c_intlumi->SaveAs(result_path+chamber+string_saving);
	 c_intlumi->Clear();
//   c_intlumi->Close();

   if(new_integratelumi.at(i).GetEntries() ==0) continue;
   slope = f1->GetParameter(1);
   slope_error = f1->GetParError(1);
   chi2 = f1->GetChisquare();
   ndf  = f1->GetNDF();
   tree_intlumi->Fill();

	}


 output_file->cd();
 tree_intlumi->Write();
 output_file->Close();
	std::cout<<"************************************"<<std::endl;
  
//	if(debug) std::cout<<" bin number and the setted mean value for pressure "<<i<<" mean "<<mean_slope_pressure[i]<<" chamber[i] "<<chamber[i]<<std::endl;
  

 // file->Close();
  //hist_slope_pressure[i]->Write();	
	//hist_slope_instlumi[i]->Write();
	}
