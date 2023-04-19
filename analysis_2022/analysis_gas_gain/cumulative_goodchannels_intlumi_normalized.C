// Cumulative plots for intlumi which is normalized wrt average
// and pressure and instlumi fit plots complete
void cumulative_goodchannels_intlumi_normalized(){

  TString input_file_chamber[32]; 
  TFile *file;	
	//TFile *file[2];
  //TString chamber[2] = {"ME11a", "ME11b", "ME12HV1", "ME12HV2", "ME12HV3", "ME13HV1", "ME13HV2", "ME13HV3", "ME21HV1", "ME21HV2", "ME21HV3", "ME22HV1", "ME22HV2", "ME22HV3", "ME22HV4", "ME22HV5", "ME31HV1", "ME31HV2", "ME31HV3", "ME2HV1", "ME2HV2", "ME2HV3", "ME2HV4", "ME2HV5", "ME41HV1", "ME41HV2" ,"ME41HV3", "ME42HV1", "ME42HV2", "ME42HV3", "ME42HV4", "ME42HV5"}; 
//TString chamber[32] = {"ME11a", "ME11a", "ME12HV2", "ME12HV2","ME12HV3", "ME13HV1","ME13HV2","ME13HV2","ME21HV2", "ME21HV2", "ME21HV3", "ME22HV1", "ME22HV2", "ME22HV3", "ME22HV4","ME22HV5","ME31HV1","ME31HV1", "ME31HV1", "ME32HV1", "ME32HV2", "ME32HV3", "ME32HV4","ME32HV5","ME41HV2","ME41HV2", "ME41HV3", "ME42HV1", "ME42HV2", "ME42HV3", "ME42HV4","ME42HV5"}; 
// TString chamber[32] = {"ME21HV2"}; 
 TString chamber[32] = {"ME11b", "ME12HV1","ME12HV2", "ME12HV3","ME13HV1", "ME13HV2","ME13HV3", "ME21HV2","ME21HV3", "ME31HV2","ME31HV3", "ME41HV1","ME22HV3", "ME11b","ME11b", "ME11b","ME11b",     "ME11b","ME11b", "ME11b","ME11b", "ME11b","ME11b", "ME11b","ME11b", "ME11b","ME11b", "ME11b","ME11b", "ME11b","ME11b", "ME11b"};             
	bool debug = true;

	TGraphErrors *graph_slope_pressure ;
	TGraphErrors *graph_slope_instlumi ;
	TGraphErrors *graph_slope_pressure_2 ;
	TGraphErrors *graph_slope_instlumi_2 ;
	TString input_file_path = "/cmsuf/data/store/user/t2/users/neha.rawal/CSCAgeing_2022/analysis_2022/2022_output_files_final/";
	TString result_path = "/cmsuf/data/store/user/t2/users/neha.rawal/CSCAgeing_2022/analysis_2022/analysis_gas_gain/intlumi_plots_normalized/";
  if(debug) std::cout<<"after opening root file"<<std::endl;
  if(debug) std::cout<<"going to start the loop"<<std::endl;

	TFile *output_file = TFile::Open(result_path+"Cumulative_plots.root", "RECREATE");
	float mean_value_pressure[32];
	float mean_error_value_pressure[32];
	float mean_value_pressure_2[32];
	float mean_error_value_pressure_2[32];

	float mean_value_instlumi[32];
	float mean_error_value_instlumi[32];
	float mean_value_instlumi_2[32];
	float mean_error_value_instlumi_2[32];

	Float_t _slope_goodchannels_pressure;
	Float_t _slope_error_goodchannels_pressure;
	Float_t _slope_goodchannels_pressure_2;
	Float_t _slope_error_goodchannels_pressure_2;

	Float_t _slope_goodchannels_instlumi;
	Float_t _slope_error_goodchannels_instlumi;
	Float_t _slope_goodchannels_instlumi_2;
	Float_t _slope_error_goodchannels_instlumi_2;
 float i_list[32] ={1,2,3,4,5,6,7,8,9,10,11,12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};  
// float i_list[1] ={1};  
	for(int i=0; i<32;i++){
//  input_file_chamber[i] = input_file_path + "DUMMYFILENAME_2017_all_"+chamber[i]+"_tree.root";
  input_file_chamber[i] = input_file_path + "outf_dataset25to36fbonly_" +chamber[i]+"_output.root";
  std::cout<<"filename "<<input_file_chamber[i]<<std::endl;	
	file = TFile::Open(input_file_chamber[i]);

  TDirectory *dir_intlumi_before = (TDirectory*) file->Get("_integratelumi_initial");
  TDirectory *dir_intlumi_after = (TDirectory*) file->Get("_integratelumi");
  TH1D *intlumi_before_all_goodchannels = (TH1D*) dir_intlumi_before->Get("_dataset25to36fbonlytrimmean_allgoodchannelsvs_integratelumi_initial");
  TH1D *intlumi_after_all_goodchannels = (TH1D*) dir_intlumi_after->Get("_dataset25to36fbonlytrimmean_allgoodchannelsvs_integratelumi");
/*
	float mean_intlumi_before = 0, error_mean_intlumi_before ; 
	float mean_intlumi_after = 0, error_mean_intlumi_after ; 
	float error_intlumi_before, error_intlumi_after; 
	float total_error_intlumi_before, total_error_intlumi_after;

 for(int i=1; i<= intlumi_before_all_goodchannels->GetNbinsX(); i++){

        mean_intlumi_before +=  intlumi_before_all_goodchannels->GetBinContent(i);
        mean_intlumi_after +=  intlumi_after_all_goodchannels->GetBinContent(i);
 }
 mean_intlumi_before = mean_intlumi_before/intlumi_before_all_goodchannels->GetNbinsX();
 mean_intlumi_after = mean_intlumi_after/intlumi_after_all_goodchannels->GetNbinsX();
	// go through all bin contents 
//        mean_intlumi_before =  intlumi_before_all_goodchannels->GetMean(2);
	      error_mean_intlumi_before = intlumi_before_all_goodchannels->GetMeanError(2);
        mean_intlumi_after =  intlumi_after_all_goodchannels->GetMean(2);
	      error_mean_intlumi_after = intlumi_after_all_goodchannels->GetMeanError(2);
				std::cout<<"mean_intlumi before"<<mean_intlumi_before<<std::endl;

 for(int i=1; i<= intlumi_before_all_goodchannels->GetNbinsX(); i++){
	 // need to change the errror for this points
	 error_intlumi_before = intlumi_before_all_goodchannels->GetBinError(i);
	 error_intlumi_after = intlumi_after_all_goodchannels->GetBinError(i);
	 total_error_intlumi_before = sqrt(error_intlumi_before * error_intlumi_before + ( (intlumi_before_all_goodchannels->GetBinContent(i)*intlumi_before_all_goodchannels->GetBinContent(i) * error_mean_intlumi_before*error_mean_intlumi_before)/ mean_intlumi_before*mean_intlumi_before) ) * (1/mean_intlumi_before);
	 total_error_intlumi_after = sqrt(error_intlumi_after * error_intlumi_after + ( (intlumi_after_all_goodchannels->GetBinContent(i) *intlumi_after_all_goodchannels->GetBinContent(i) * error_mean_intlumi_after*error_mean_intlumi_after)/ mean_intlumi_after*mean_intlumi_after) ) * (1/mean_intlumi_after);
	 intlumi_before_all_goodchannels->SetBinContent(i, intlumi_before_all_goodchannels->GetBinContent(i)/mean_intlumi_before);
	 intlumi_before_all_goodchannels->SetBinError(i,total_error_intlumi_before);

	 intlumi_after_all_goodchannels->SetBinContent(i, intlumi_after_all_goodchannels->GetBinContent(i)/mean_intlumi_after);
	 intlumi_after_all_goodchannels->SetBinError(i,total_error_intlumi_after);
 } */
  TDirectory *dir_pressure= (TDirectory*) file->Get("_pressure");
  TDirectory *dir_instlumi= (TDirectory*) file->Get("_instlumi");
  TH1D *pressure_goodchannels = (TH1D*) dir_pressure->Get("_dataset25to36fbonlytrimmean_allgoodchannelsvs_pressure");
  TH1D *instlumi_goodchannels = (TH1D*) dir_instlumi->Get("_dataset25to36fbonlytrimmean_allgoodchannelsvs_instlumi");

	// Put pressure, lumi and everytgibng in a output file
	
  TCanvas *c_intlumi_before = new TCanvas("c_intlumi_before"," intlumi before correction "); 
  TCanvas *c_intlumi_after = new TCanvas("c_intlumi_after"," intlumi after correction "); 
  TCanvas *c_pressure = new TCanvas("c_pressure"," pressure before correction "); 
  TCanvas *c_instlumi = new TCanvas("c_instlumi"," instlumi before correction "); 

	/// intlumi plot
	c_intlumi_before->cd();
	intlumi_before_all_goodchannels->Draw();
	intlumi_before_all_goodchannels->SetTitle(" intlumi before correction (cumulative) : "+chamber[i]);
	intlumi_before_all_goodchannels->GetYaxis()->SetTitle("Normalized Trimmed Charge");
	intlumi_before_all_goodchannels->GetYaxis()->SetRangeUser(0.9,1.1);
	intlumi_before_all_goodchannels->GetXaxis()->SetTitle("integrate lumi (fb^{-1})");
	c_intlumi_before->SaveAs(result_path+"intlumi_before_"+chamber[i]+".pdf");

	c_intlumi_after->cd();
	intlumi_after_all_goodchannels->Draw();
	intlumi_after_all_goodchannels->SetTitle(" intlumi_after correction (cumulative) : "+chamber[i]);
	intlumi_after_all_goodchannels->GetYaxis()->SetTitle("Normalized Trimmed Charge");
	intlumi_after_all_goodchannels->GetXaxis()->SetTitle("integrate lumi (fb^{-1})");
	intlumi_after_all_goodchannels->GetYaxis()->SetRangeUser(0.9,1.1);
	c_intlumi_after->SaveAs(result_path+"intlumi_after_"+chamber[i]+".pdf");

	c_pressure->cd();
	pressure_goodchannels->Draw();
	pressure_goodchannels->SetTitle(" pressure before correction (cumulative) : "+chamber[i]);
	pressure_goodchannels->GetYaxis()->SetTitle(" Trimmed Charge");
	pressure_goodchannels->GetXaxis()->SetTitle("Pressure (hPa)");
	c_pressure->SaveAs(result_path+"pressure_"+chamber[i]+".pdf");

	c_instlumi->cd();
	instlumi_goodchannels->Draw();
	instlumi_goodchannels->SetTitle(" instlumi before correction (cumulative) : "+chamber[i]);
	instlumi_goodchannels->GetYaxis()->SetTitle(" Trimmed Charge");
	instlumi_goodchannels->GetXaxis()->SetTitle("inst lumi (#mu b^{-1} s^{-1})");
	c_instlumi->SaveAs(result_path+"instlumi_"+chamber[i]+".pdf");

	 // write these four plots in the output root file
	 
	intlumi_before_all_goodchannels->SetName("intlumi_before_correction_"+chamber[i]);
	intlumi_after_all_goodchannels->SetName("intlumi_after_correction_"+chamber[i]);
  pressure_goodchannels->SetName("pressure_before_correction_"+chamber[i]);
  instlumi_goodchannels->SetName("instlumi_before_correction_"+chamber[i]);

 output_file->cd();
intlumi_before_all_goodchannels->Write(); 
intlumi_after_all_goodchannels->Write(); 
pressure_goodchannels->Write(); 
instlumi_goodchannels->Write(); 


	TTree * tree = (TTree*) file->Get("tree_all_goodchannels_pressure");
	tree->SetBranchAddress("_slope_goodchannels",&_slope_goodchannels_pressure);
	tree->SetBranchAddress("_slope_error_goodchannels",&_slope_error_goodchannels_pressure);
		tree->GetEntry(0);
		mean_value_pressure[i] = _slope_goodchannels_pressure;
		mean_error_value_pressure[i] = _slope_error_goodchannels_pressure;

	TTree * tree_2 = (TTree*) file->Get("tree_all_goodchannels_pressure_2");
	tree_2->SetBranchAddress("_slope_goodchannels",&_slope_goodchannels_pressure_2);
	tree_2->SetBranchAddress("_slope_error_goodchannels",&_slope_error_goodchannels_pressure_2);
		tree_2->GetEntry(0);
		mean_value_pressure_2[i] = _slope_goodchannels_pressure_2;
		mean_error_value_pressure_2[i] = _slope_error_goodchannels_pressure_2;

		TTree * tree_3 = (TTree*) file->Get("tree_all_goodchannels_instlumi");
	tree_3->SetBranchAddress("_slope_goodchannels",&_slope_goodchannels_instlumi);
	tree_3->SetBranchAddress("_slope_error_goodchannels",&_slope_error_goodchannels_instlumi);
		tree_3->GetEntry(0);
		mean_value_instlumi[i] = _slope_goodchannels_instlumi;
		mean_error_value_instlumi[i] = _slope_error_goodchannels_instlumi;

	TTree * tree_4 = (TTree*) file->Get("tree_all_goodchannels_instlumi_2");
	tree_4->SetBranchAddress("_slope_goodchannels",&_slope_goodchannels_instlumi_2);
	tree_4->SetBranchAddress("_slope_error_goodchannels",&_slope_error_goodchannels_instlumi_2);
		tree_4->GetEntry(0);
		mean_value_instlumi_2[i] = _slope_goodchannels_instlumi_2;
		mean_error_value_instlumi_2[i] = _slope_error_goodchannels_instlumi_2;

  }

	// make the graphs 
  graph_slope_pressure = new TGraphErrors(32,i_list,mean_value_pressure, 0,mean_error_value_pressure);
  graph_slope_pressure_2 = new TGraphErrors(32,i_list,mean_value_pressure_2, 0,mean_error_value_pressure_2);
  graph_slope_instlumi = new TGraphErrors(32,i_list,mean_value_instlumi, 0,mean_error_value_instlumi);
  graph_slope_instlumi_2 = new TGraphErrors(32,i_list,mean_value_instlumi_2, 0,mean_error_value_instlumi_2);

	graph_slope_pressure->GetYaxis()->SetTitle("Mean of slope(rel charge vs pressure(hPa))");
  graph_slope_instlumi->GetYaxis()->SetTitle("Mean of slope(rel charge vs inst lumi (#mu b^{-1} s^{-1}))");
	graph_slope_pressure_2->GetYaxis()->SetTitle("Mean of slope(rel charge vs pressure(hPa)) after correction ");
  graph_slope_instlumi_2->GetYaxis()->SetTitle("Mean of slope(rel charge vs inst lumi (#mu b^{-1} s^{-1})) after correction ");
	
  output_file->cd();
	graph_slope_pressure->GetXaxis()->SetTickLength(1);
	graph_slope_pressure_2->GetXaxis()->SetTickLength(1);
	graph_slope_instlumi->GetXaxis()->SetTickLength(1);
	graph_slope_instlumi_2->GetXaxis()->SetTickLength(1);
	
	if(debug) std::cout<<" before declaring axes "<<std::endl;
	TAxis *axis_pressure_1 = graph_slope_pressure->GetXaxis();
	axis_pressure_1->SetLabelSize(0.03);
	TAxis *axis_pressure_2 = graph_slope_pressure_2->GetXaxis();
	axis_pressure_2->SetLabelSize(0.03);
	TAxis *axis_instlumi_1 = graph_slope_instlumi->GetXaxis();
	axis_instlumi_1->SetLabelSize(0.03);
	TAxis *axis_instlumi_2 = graph_slope_instlumi_2->GetXaxis();
	axis_instlumi_2->SetLabelSize(0.03); 
	for(int i=0; i<32; i++){  
  graph_slope_pressure->GetXaxis()->SetBinLabel(graph_slope_pressure->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label
  graph_slope_pressure_2->GetXaxis()->SetBinLabel(graph_slope_pressure_2->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label
  graph_slope_instlumi->GetXaxis()->SetBinLabel(graph_slope_instlumi->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label
  graph_slope_instlumi_2->GetXaxis()->SetBinLabel(graph_slope_instlumi_2->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label

	}




///  TFile *output_file = new TFile("output_file.root","RECREATE");
	graph_slope_pressure->GetXaxis()->SetTitleOffset(0.1); 
	graph_slope_pressure_2->GetXaxis()->SetTitleOffset(0.1); 
	graph_slope_instlumi->GetXaxis()->SetTitleOffset(0.1); 
	graph_slope_instlumi_2->GetXaxis()->SetTitleOffset(0.1); 
//	graph_slope_integratelumi_chamber_initial->GetXaxis()->SetTitleOffset(0.1); 
//	graph_slope_integratelumi_chamber->GetXaxis()->SetTitleOffset(0.1); 


	graph_slope_pressure->GetYaxis()->SetTitleOffset(1.5); 
	graph_slope_pressure_2->GetYaxis()->SetTitleOffset(1.5); 
	graph_slope_instlumi->GetYaxis()->SetTitleOffset(1.5); 
	graph_slope_instlumi_2->GetYaxis()->SetTitleOffset(1.5); 
//	graph_slope_integratelumi_chamber_initial->GetYaxis()->SetTitleOffset(1.7); 
//	graph_slope_integratelumi_chamber->GetYaxis()->SetTitleOffset(1.7); 

	graph_slope_pressure->GetYaxis()->SetRangeUser(-0.010,0.002); 
	graph_slope_pressure_2->GetYaxis()->SetRangeUser(-0.01,0.002); 
	graph_slope_instlumi->GetYaxis()->SetRangeUser(-0.000004, 0.000004); 
	graph_slope_instlumi_2->GetYaxis()->SetRangeUser(-0.000004, 0.000004); 
//	graph_slope_integratelumi_chamber_initial->GetYaxis()->SetRangeUser(-0.004,0.004); 
//	graph_slope_integratelumi_chamber->GetYaxis()->SetRangeUser(-0.004,0.004); 


	TCanvas *c = new TCanvas("c","pressure slope mean vs chamber",800,800);
	c->cd();
	c->SetGrid();
	gPad->SetGrid();
	axis_pressure_1->Draw();
  graph_slope_pressure->Draw("AP");
Double_t *gr_xarray_pressure = graph_slope_pressure->GetX();
Double_t *gr_yarray_pressure = graph_slope_pressure->GetY();
   for (Int_t j=0; j<32; j++) {
      TMarker *m = new TMarker(gr_xarray_pressure[j], gr_yarray_pressure[j], 20+j%4);
      m->SetMarkerSize(1);
      m->SetMarkerColor(25+j);
      m->Draw();
   }
	c->SaveAs(result_path+"mean_slope_pressure_with_chamber.pdf"); 
	TCanvas *c_2 = new TCanvas("c_2","pressure slope mean vs chamber after second correction",800,800);
	c_2->cd();
	c_2->SetGrid();
	gPad->SetGrid();
	axis_pressure_2->Draw();
	graph_slope_pressure_2->Draw("AP");
  Double_t *gr_xarray_pressure_2 = graph_slope_pressure_2->GetX();
  Double_t *gr_yarray_pressure_2 = graph_slope_pressure_2->GetY();
   for (Int_t j=0; j<32; j++) {
      TMarker *m = new TMarker(gr_xarray_pressure_2[j], gr_yarray_pressure_2[j], 20+j%4);
      m->SetMarkerSize(1);
      m->SetMarkerColor(25+j);
      m->Draw();
   }


	c_2->SaveAs(result_path+"mean_slope_pressure_with_chamber_2.pdf"); 

	TCanvas *c1 = new TCanvas("c1","instlumi slope mean vs chamber",800,800);
	c1->cd();
	c1->SetGrid();
	gPad->SetGrid();
	axis_instlumi_1->Draw();
	graph_slope_instlumi->Draw("AP");
  Double_t *gr_xarray_instlumi = graph_slope_instlumi->GetX();
  Double_t *gr_yarray_instlumi = graph_slope_instlumi->GetY();
   for (Int_t j=0; j<32; j++) {
      TMarker *m = new TMarker(gr_xarray_instlumi[j], gr_yarray_instlumi[j], 20+j%4);
      m->SetMarkerSize(1);
      m->SetMarkerColor(25+j);
      m->Draw();
   }



	c1->SaveAs(result_path+"mean_slope_instlumi_with_chamber.pdf"); 

	TCanvas *c1_2 = new TCanvas("c1_2","instlumi slope mean vs chamber",800,800);
	c1_2->cd();
	c1_2->SetGrid();
	gPad->SetGrid();
	axis_instlumi_2->Draw();
	graph_slope_instlumi_2->Draw("AP");
  Double_t *gr_xarray_instlumi_2 = graph_slope_instlumi_2->GetX();
  Double_t *gr_yarray_instlumi_2 = graph_slope_instlumi_2->GetY();
   for (Int_t j=0; j<32; j++) {
      TMarker *m = new TMarker(gr_xarray_instlumi_2[j], gr_yarray_instlumi_2[j], 20+j%4);
      m->SetMarkerSize(1);
      m->SetMarkerColor(25+j);
      m->Draw();
   }


	c1_2->SaveAs(result_path+"mean_slope_instlumi_with_chamber_2.pdf"); 

/*	TCanvas *c2_1 = new TCanvas("c2_1","intlumi slope mean vs chamber",1000,800);
	c2_1->cd();
	c2_1->SetGrid(1,1);
	axis_integratelumi->Draw();
	graph_slope_integratelumi_chamber->Draw("AP*");
	c2_1->SaveAs(result_path+"mean_slope_integratelumi_chamber.pdf"); 

	TCanvas *c2_initial = new TCanvas("c2_initial","intlumi slope mean vs chamber (initial)",1000,800);
	c2_initial->cd();
	c2_initial->SetGrid(1,1);
	axis_integratelumi_initial->Draw();
	graph_slope_integratelumi_chamber_initial->Draw("AP*");
	c2_initial->SaveAs(result_path+"mean_slope_integratelumi_chamber_initial.pdf"); 

 
		TCanvas *c_pressure = new TCanvas("c_pressure","pressure plot of i th file after pressure correction for first time",700,700);
  c_pressure->cd();
   graph_slope_pressure->Draw();
   graph_slope_pressure->GetXaxis()->SetRangeUser(-0.016, 0.0);
  c_pressure->SaveAs(result_path+"slope_pressure_"+chamber[i]+".pdf");
  c_pressure->Close();

	TCanvas *c_pressure_2 = new TCanvas("c_pressure_2","pressure plot of i th file after pressure correction for second time",700,700);
  c_pressure_2->cd();
   graph_slope_pressure_2->Draw();
  c_pressure_2->SaveAs(result_path+"slope_pressure_"+chamber[i]+"_second.pdf");
  c_pressure_2->Close();

	TCanvas *c_instlumi = new TCanvas("c_instlumi","instlumi plot of i th file after instlumi correction for first time",700,700);
  c_instlumi->cd();
   graph_slope_instlumi->Draw();
  c_instlumi->SaveAs(result_path+"slope_instlumi_"+chamber[i]+".pdf");
  c_instlumi->Close();

	TCanvas *c_instlumi_2 = new TCanvas("c_instlumi_2","instlumi plot of i th file after instlumi correction for second time",700,700);
  c_instlumi_2->cd();
  graph_slope_instlumi_2->Draw();
  c_instlumi_2->SaveAs(result_path+"slope_instlumi_"+chamber[i]+"_second.pdf");
  c_instlumi_2->Close();
*/
 	 
  c->Write();
  c_2->Write();
  c1->Write();
  c1_2->Write();
//  c2_initial->Write(); 
	output_file->Close();
} 


