void analysis(){

  TString input_file_chamber[32]; 
  TFile *file;	
	//TFile *file[2];
  //TString chamber[2] = {"ME11a", "ME11b", "ME12HV1", "ME12HV2", "ME12HV3", "ME13HV1", "ME13HV2", "ME13HV3", "ME21HV1", "ME21HV2", "ME21HV3", "ME22HV1", "ME22HV2", "ME22HV3", "ME22HV4", "ME22HV5", "ME31HV1", "ME31HV2", "ME31HV3", "ME2HV1", "ME2HV2", "ME2HV3", "ME2HV4", "ME2HV5", "ME41HV1", "ME41HV2" ,"ME41HV3", "ME42HV1", "ME42HV2", "ME42HV3", "ME42HV4", "ME42HV5"}; 
//  TString chamber[1] = {"ME21HV1"}; 
 //TString chamber[32] = {"ME11a", "ME11b", "ME12HV1", "ME12HV2","ME12HV3", "ME13HV1","ME13HV2","ME13HV3","ME21HV1", "ME21HV2", "ME21HV3", "ME22HV1", "ME22HV2", "ME22HV3", "ME22HV4","ME22HV5","ME31HV1","ME31HV2", "ME31HV3", "ME32HV1", "ME32HV2", "ME32HV3", "ME32HV4","ME32HV5","ME41HV1","ME41HV2", "ME41HV3", "ME42HV1", "ME42HV2", "ME42HV3", "ME42HV4","ME42HV5"}; 
 TString chamber[32] = {"ME11b", "ME12HV1","ME12HV2", "ME12HV3","ME13HV1", "ME13HV2","ME13HV3", "ME21HV2","ME21HV3", "ME31HV2","ME31HV3", "ME41HV1","ME22HV3", "ME11b","ME11b", "ME11b","ME11b", "ME11b","ME11b", "ME11b","ME11b", "ME11b","ME11b", "ME11b","ME11b", "ME11b","ME11b", "ME11b","ME11b", "ME11b","ME11b", "ME11b"}; 
	bool debug = true;

	TH1D *hist_slope_pressure[32];
	TH1D *hist_slope_pressure_2[32];
	TH1D *hist_slope_instlumi[32];
	TH1D *hist_slope_instlumi_2[32];
//	TH1D *hist_slope_instlumi_new[32];
//	TH1D *hist_slope_integratelumi_initial[32];
//	TH1D *hist_slope_integratelumi[32];

	float mean_slope_pressure[32] = {0};
  float mean_slope_pressure_unc[32] = {0} ;
  float mean_slope_instlumi[32] = {0} ;
  float mean_slope_instlumi_unc[32] = {0} ;
  float mean_slope_instlumi_new[32] = {0} ;
  float mean_slope_instlumi_unc_new[32] = {0} ;

//  float mean_slope_integratelumi_initial[32] = {0} ;
  //float mean_slope_integratelumi_initial_unc[32] = {0} ;

 float mean_slope_pressure_2[32] = {0} ;
  float mean_slope_pressure_unc_2[32] = {0} ;
  float mean_slope_instlumi_2[32] = {0} ;
  float mean_slope_instlumi_unc_2[32] = {0} ; 
  float mean_slope_integratelumi[32] = {0} ;
 // float mean_slope_integratelumi_unc[32] = {0} ;

	TGraphErrors *graph_slope_pressure_chamber_1 ;
	TGraphErrors *graph_slope_pressure_chamber_2 ;
	TGraphErrors *graph_slope_instlumi_chamber_1 ;
	TGraphErrors *graph_slope_instlumi_chamber_2 ; 
//	TGraphErrors *graph_slope_integratelumi_chamber_initial;
	//TGraphErrors *graph_slope_integratelumi_chamber;

	TString input_file_path = "/cmsuf/data/store/user/t2/users/neha.rawal/CSCAgeing_2022/analysis_2022/2022_output_files_final/";
	//outf_dataset15to23fbonly_ME12HV1_output.root";
	TString result_path = "/cmsuf/data/store/user/t2/users/neha.rawal/CSCAgeing_2022/analysis_2022/analysis_gas_gain/result_analysis_new_way/";
  
//	TFile *file = TFile::Open(input_file_path+"DUMMYFILENAME_2017_all_"+chamber[i]+"_tree.root";
  TFile *output_file = new TFile(result_path+"output_file_intlumi.root","RECREATE");

  if(debug) std::cout<<"after opening root file"<<std::endl;

	// to put slopes separately for each layer
/*	 TTree *tree_pressure = (TTree*) file->Get("tree__pressure");
	 TH1F *slope_presure = new TH1F("slope_pressure", "slope of chamber", 100,-0.002,0.02);
	 TH1F *slope_presure_2 = new TH1F("slope_pressure_2", "slope of chamber", 100,-0.002,0.02);
*/
	// TH1F *slope_presure_1stlayer = new TH1F("slope_pressure_1stlayer", "slope of chamber", 100,-0.002,0.02);
	 //TH1F *slope_presure_2 = new TH1F("slope_pressure_2", "slope of chamber", 100,-0.002,0.02);
	//axis_integratelumi->SetTickSize(0.7);
  if(debug) std::cout<<"going to start the loop"<<std::endl;

	for(int i=0; i<32;i++){
//  input_file_chamber[i] = input_file_path + "DUMMYFILENAME_2017_all_"+chamber[i]+"_tree.root";
  input_file_chamber[i] = input_file_path + "outf_dataset25to36fbonly_" +chamber[i]+"_output.root";
  std::cout<<"filename "<<input_file_chamber[i]<<std::endl;	
	
	file = TFile::Open(input_file_chamber[i]);
	//std::cout<<"input file "<<file<<std::endl;
	hist_slope_pressure[i] = (TH1D*) file->Get("h_slope_pressure__dataset25to36fbonly");	
	hist_slope_pressure_2[i] = (TH1D*) file->Get("h_slope_pressure_2__dataset25to36fbonly");	
  hist_slope_instlumi[i] = (TH1D*) file->Get("h_slope_instlumi__dataset25to36fbonly");	
  hist_slope_instlumi_2[i] = (TH1D*) file->Get("h_slope_instlumi_2__dataset25to36fbonly");	
//	 for(int bin =1 ; bin<=hist_slope_instlumi[i]->GetNbinsX(); bin++){
//	 hist_slope_instlumi_new[i]->Fill(hist_slope_instlumi[i]->GetBinContent(bin));
//	 }
 // hist_slope_integratelumi_initial[i] = (TH1D*) file->Get("h_slope_integratelumi_initial_DUMMYFILENAME_2017_new_all_"+chamber[i]+"_tree14to26fbonly_7e33to9e33");	
//  hist_slope_integratelumi[i] = (TH1D*) file->Get("h_slope_integratelumi_DUMMYFILENAME_2017_all_"+chamber[i]+"_tree14to26fbonly_7e33to9e33");	

//	hist_slope_instlumi[i]->Rebin(3);

	TF1 *gaus1 = new TF1("gaus1","gaus",-0.016,0.001);
	TF1 *gaus2 = new TF1("gaus2","gaus",-0.00004,0.00004);
//	TF1 *gaus_3 = new TF1("gaus_3","gaus",-0.00001,0.00001);
  TF1 *gaus1_2 = new TF1("gaus1_2","gaus",-0.001,0.001);
	TF1 *gaus2_2 = new TF1("gaus2_2","gaus",-0.000002,0.000002);
//	TF1 *gaus2_new = new TF1("gaus2_new","gaus",-0.000002,0.000002);
//	TF1 *gaus3_initial = new TF1("gaus3_initial","gaus",-0.005,0.005);
//	TF1 *gaus3 = new TF1("gaus3","gaus",-0.005,0.005);

	gStyle->SetOptFit(1011);
	hist_slope_pressure[i]->Fit(gaus1,"R");
 	
	mean_slope_pressure[i] = gaus1->GetParameter(1);
	//mean_slope_pressure_unc[i] = gaus1->GetParameter(2);
	mean_slope_pressure_unc[i] = gaus1->GetParError(1);
	
	hist_slope_pressure_2[i]->Fit(gaus1_2,"R");
 	
	mean_slope_pressure_2[i] = gaus1_2->GetParameter(1);
	//mean_slope_pressure_unc_2[i] = gaus1_2->GetParameter(2);
	mean_slope_pressure_unc_2[i] = gaus1_2->GetParError(1);

/*	if(i== 0 || i ==1 || i==8 |  i==9 |   i==10 || i==16 |  i==17 |   i==18 || i==24 |  i==25 |   i==26 ){
	hist_slope_instlumi[i]->Fit(gaus_3,"R");
	mean_slope_instlumi[i] = gaus_3->GetParameter(1);
	mean_slope_instlumi_unc[i] = gaus_3->GetParError(1); }

	else */
	hist_slope_instlumi[i]->Fit(gaus2,"R");
	mean_slope_instlumi[i] = gaus2->GetParameter(1);
	//mean_slope_instlumi_unc[i] = gaus2->GetParameter(2); 
	mean_slope_instlumi_unc[i] = gaus2->GetParError(1); 
 
/*	hist_slope_instlumi_new[i]->Fit(gaus2_new,"R");

	mean_slope_instlumi_new[i] = gaus2_new->GetParameter(1);
	mean_slope_instlumi_unc_new[i] = gaus2_new->GetParError(1);
*/

	hist_slope_instlumi_2[i]->Fit(gaus2_2,"R");

	mean_slope_instlumi_2[i] = gaus2_2->GetParameter(1);
	//mean_slope_instlumi_unc_2[i] = gaus2_2->GetParameter(2);
	mean_slope_instlumi_unc_2[i] = gaus2_2->GetParError(1);

///	hist_slope_integratelumi[i]->Fit(gaus3,"R");

//	mean_slope_integratelumi[i] = gaus3->GetParameter(1);
//	mean_slope_integratelumi_unc[i] = gaus3->GetParError(1);
/*
	hist_slope_integratelumi_initial[i]->Fit(gaus3_initial,"R");

	mean_slope_integratelumi_initial[i] = gaus3_initial->GetParameter(1);
	mean_slope_integratelumi_initial_unc[i] = gaus3_initial->GetParError(1);


*/
 	TCanvas *c_pressure = new TCanvas("c_pressure","pressure plot of i th file after pressure correction for first time",700,700);
  c_pressure->cd();
	hist_slope_pressure[i]->GetXaxis()->SetRangeUser(-0.016, 0.0);
	hist_slope_pressure[i]->GetXaxis()->SetTitle("slope of #Delta Q vs pressure (hPa)");
	hist_slope_pressure[i]->SetTitle(chamber[i]);
  hist_slope_pressure[i]->Draw();
  c_pressure->SaveAs(result_path+"slope_pressure_"+chamber[i]+".pdf");
  c_pressure->Close();

	TCanvas *c_pressure_2 = new TCanvas("c_pressure_2","pressure plot of i th file after pressure correction for second time",700,700);
  c_pressure_2->cd();
	hist_slope_pressure_2[i]->GetXaxis()->SetRangeUser(-0.01, 0.01);
	hist_slope_pressure_2[i]->GetXaxis()->SetTitle("slope of #Delta Q vs pressure (hPa)");

	hist_slope_pressure_2[i]->SetTitle(chamber[i]);
  hist_slope_pressure_2[i]->Draw();
  c_pressure_2->SaveAs(result_path+"slope_pressure_"+chamber[i]+"_second.pdf");
  c_pressure_2->Close();

	TCanvas *c_instlumi = new TCanvas("c_instlumi","instlumi plot of i th file after instlumi correction for first time",700,700);
  c_instlumi->cd();
	hist_slope_instlumi[i]->GetXaxis()->SetRangeUser(-0.00004, 0.00004);
	hist_slope_instlumi[i]->GetXaxis()->SetTitle("slope of #Delta Q vs inst lumi (#mu b^{-1} s^{-1})");
	hist_slope_instlumi[i]->SetTitle(chamber[i]);
  hist_slope_instlumi[i]->Draw();
  c_instlumi->SaveAs(result_path+"slope_instlumi_"+chamber[i]+".pdf");
  c_instlumi->Close();

	TCanvas *c_instlumi_2 = new TCanvas("c_instlumi_2","instlumi plot of i th file after instlumi correction for second time",700,700);
  c_instlumi_2->cd();
	hist_slope_instlumi_2[i]->GetXaxis()->SetRangeUser(-0.00004, 0.00004);
	hist_slope_instlumi_2[i]->GetXaxis()->SetTitle("slope of #Delta Q vs inst lumi (#mu b^{-1} s^{-1})");
	hist_slope_instlumi_2[i]->SetTitle(chamber[i]);
  hist_slope_instlumi_2[i]->Draw();
  c_instlumi_2->SaveAs(result_path+"slope_instlumi_"+chamber[i]+"_second.pdf");
  c_instlumi_2->Close();
/*
	TCanvas *c_instlumi_new = new TCanvas("c_instlumi_new","instlumi plot of i th file before instlumi correction ",700,700);
  c_instlumi_new->cd();
	hist_slope_instlumi_new[i]->GetXaxis()->SetRangeUser(-0.00002, 0.00002);
	hist_slope_instlumi_new[i]->GetXaxis()->SetTitle("slope of #Delta Q vs inst lumi (#mu b^{-1} s^{-1})");
  hist_slope_instlumi_new[i]->Draw();
  c_instlumi_new->SaveAs(result_path+"slope_instlumi_"+chamber[i]+"_new.pdf");
  c_instlumi_new->Close();


	TCanvas *c_intlumi_initial = new TCanvas("c_intlumi_initial","int lumi plot of i th file before any corrections",700,700);
  c_intlumi_initial->cd();
  hist_slope_integratelumi_initial[i]->Draw();
  c_intlumi_initial->SaveAs(result_path+"slope_intlumi_initial"+chamber[i]+".pdf");
  c_intlumi_initial->Close();


	TCanvas *c_intlumi = new TCanvas("c_intlumi","int lumi plot of i th file after pressure and instlumi  correction",700,700);
  c_intlumi->cd();
  hist_slope_integratelumi[i]->Draw();
  c_intlumi->SaveAs(result_path+"slope_intlumi_"+chamber[i]+".pdf");
  c_intlumi->Close();
*/

  std::cout<<"mean slope value for chamber "<<chamber[i]<<std::endl;
	std::cout<<mean_slope_pressure[i]<<std::endl;
	std::cout<<mean_slope_pressure_2[i]<<std::endl;
	std::cout<<mean_slope_instlumi[i]<<std::endl;
	std::cout<<mean_slope_instlumi_2[i]<<std::endl; 
//	std::cout<<mean_slope_integratelumi_initial[i]<<std::endl;
	//std::cout<<mean_slope_integratelumi[i]<<std::endl;
	std::cout<<"************************************"<<std::endl;
  
	//if(debug) std::cout<<" bin number and the setted mean value for pressure "<<i<<" mean "<<mean_slope_pressure[i]<<" chamber[i] "<<chamber[i]<<std::endl;
  

  file->Close();
	
 // output_file->cd();
  //hist_slope_pressure[i]->Write();	
//	hist_slope_instlumi[i]->Write();
//	hist_slope_integratelumi[i]->Write();
	}

 float i_list[32] ={1,2,3,4,5,6,7,8,9,10,11,12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};
//  float i_list[32] ={1,3,5,7,9,11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63};
	// make the graphs 
  graph_slope_pressure_chamber_1 = new TGraphErrors(32,i_list,mean_slope_pressure, 0,mean_slope_pressure_unc);
  graph_slope_pressure_chamber_2 = new TGraphErrors(32,i_list,mean_slope_pressure_2, 0, mean_slope_pressure_unc_2);
  graph_slope_instlumi_chamber_1 = new TGraphErrors(32,i_list,mean_slope_instlumi, 0,mean_slope_instlumi_unc);
  graph_slope_instlumi_chamber_2 = new TGraphErrors(32,i_list,mean_slope_instlumi_2, 0,mean_slope_instlumi_unc_2); 
//  graph_slope_integratelumi_chamber_initial = new TGraphErrors(32,i_list,mean_slope_integratelumi_initial, 0 , mean_slope_integratelumi_initial_unc);
  //graph_slope_integratelumi_chamber = new TGraphErrors(32,i_list,mean_slope_integratelumi, 0 , mean_slope_integratelumi_unc);

	graph_slope_pressure_chamber_1->GetYaxis()->SetTitle("Mean of slope(rel charge vs pressure(hPa))");
  graph_slope_instlumi_chamber_1->GetYaxis()->SetTitle("Mean of slope(rel charge vs inst lumi (#mu b^{-1} s^{-1}))");
  graph_slope_pressure_chamber_2->GetYaxis()->SetTitle("Mean of slope(rel charge vs pressure (hPa))");
  graph_slope_instlumi_chamber_2->GetYaxis()->SetTitle("Mean of slope(rel charge vs inst lumi (#mu b^{-1} s^{-1}))"); 
 // graph_slope_integratelumi_chamber->GetYaxis()->SetTitle("Mean of slope(rel charge vs integrate lumi) (/fb)");
//  graph_slope_integratelumi_chamber_initial->GetYaxis()->SetTitle("Mean of slope(rel charge vs integrate lumi) initial (/fb)");


	
  output_file->cd();
	graph_slope_pressure_chamber_1->GetXaxis()->SetTickLength(1);
	graph_slope_pressure_chamber_2->GetXaxis()->SetTickLength(1);
	graph_slope_instlumi_chamber_1->GetXaxis()->SetTickLength(1);
	graph_slope_instlumi_chamber_2->GetXaxis()->SetTickLength(1);
//	graph_slope_integratelumi_chamber_initial->GetXaxis()->SetTickLength(1);
//	graph_slope_integratelumi_chamber->GetXaxis()->SetTickLength(1);

//	axis_pressure_1->SetTickSize(0.7);
//	axis_pressure_1->GetTicks();
	if(debug) std::cout<<" before declaring axes "<<std::endl;
	TAxis *axis_pressure_1 = graph_slope_pressure_chamber_1->GetXaxis();
	axis_pressure_1->SetLabelSize(0.03);
	TAxis *axis_pressure_2 = graph_slope_pressure_chamber_2->GetXaxis();
	axis_pressure_2->SetLabelSize(0.03);
//	axis_pressure_2->SetTickSize(0.7);
	TAxis *axis_instlumi_1 = graph_slope_instlumi_chamber_1->GetXaxis();
	axis_instlumi_1->SetLabelSize(0.03);
//	axis_instlumi_1->SetTickSize(0.7);
	TAxis *axis_instlumi_2 = graph_slope_instlumi_chamber_2->GetXaxis();
	axis_instlumi_2->SetLabelSize(0.03); 
//	axis_instlumi_2->SetTickSize(0.7);
//	TAxis *axis_integratelumi_initial = graph_slope_integratelumi_chamber_initial->GetXaxis();
//	axis_integratelumi_initial->SetLabelSize(0.03);
//	axis_integratelumi_initial->SetTickSize(0.7);
/* 	TAxis *axis_integratelumi = graph_slope_integratelumi_chamber->GetXaxis();
	axis_integratelumi->SetLabelSize(0.03);
	if(debug) std::cout<<" after declaring axes "<<std::endl;
*/

//	graph_slope_pressure_chamber->GetXaxis()->SetLabelSize(0.03);
	for(int i=0; i<32; i++){  
  graph_slope_pressure_chamber_1->GetXaxis()->SetBinLabel(graph_slope_pressure_chamber_1->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label
  graph_slope_pressure_chamber_2->GetXaxis()->SetBinLabel(graph_slope_pressure_chamber_2->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label
  graph_slope_instlumi_chamber_1->GetXaxis()->SetBinLabel(graph_slope_instlumi_chamber_1->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label
  graph_slope_instlumi_chamber_2->GetXaxis()->SetBinLabel(graph_slope_instlumi_chamber_2->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label
 // graph_slope_integratelumi_chamber_initial->GetXaxis()->SetBinLabel(graph_slope_integratelumi_chamber_initial->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label
  //graph_slope_integratelumi_chamber->GetXaxis()->SetBinLabel(graph_slope_integratelumi_chamber->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label
//  graph_slope_pressure_chamber_2->GetXaxis()->SetBinLabel(graph_slope_pressure_chamber_2->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label
 // graph_slope_instlumi_chamber_1->GetXaxis()->SetBinLabel(graph_slope_instlumi_chamber_1->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label
 // graph_slope_instlumi_chamber_2->GetXaxis()->SetBinLabel(graph_slope_instlumi_chamber_2->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label
//  graph_slope_integratelumi_chamber_initial->GetXaxis()->SetBinLabel(graph_slope_integratelumi_chamber_initial->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label
//  graph_slope_integratelumi_chamber->GetXaxis()->SetBinLabel(graph_slope_integratelumi_chamber->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label


//	ofstream myfile_slope_values; 
//	myfile_slope_values.open("slope_values.txt");
//  myfile_slope_values<<graph_slope_pressure_chamber_1->GetPoint(i,


	}




///  TFile *output_file = new TFile("output_file.root","RECREATE");
	graph_slope_pressure_chamber_1->GetXaxis()->SetTitleOffset(0.1); 
	graph_slope_pressure_chamber_2->GetXaxis()->SetTitleOffset(0.1); 
	graph_slope_instlumi_chamber_1->GetXaxis()->SetTitleOffset(0.1); 
	graph_slope_instlumi_chamber_2->GetXaxis()->SetTitleOffset(0.1); 
//	graph_slope_integratelumi_chamber_initial->GetXaxis()->SetTitleOffset(0.1); 
//	graph_slope_integratelumi_chamber->GetXaxis()->SetTitleOffset(0.1); 


	graph_slope_pressure_chamber_1->GetYaxis()->SetTitleOffset(1.5); 
	graph_slope_pressure_chamber_2->GetYaxis()->SetTitleOffset(1.5); 
	graph_slope_instlumi_chamber_1->GetYaxis()->SetTitleOffset(1.5); 
	graph_slope_instlumi_chamber_2->GetYaxis()->SetTitleOffset(1.5); 
//	graph_slope_integratelumi_chamber_initial->GetYaxis()->SetTitleOffset(1.7); 
//	graph_slope_integratelumi_chamber->GetYaxis()->SetTitleOffset(1.7); 

	graph_slope_pressure_chamber_1->GetYaxis()->SetRangeUser(-0.010,0.002); 
	graph_slope_pressure_chamber_2->GetYaxis()->SetRangeUser(-0.01,0.01); 
	graph_slope_instlumi_chamber_1->GetYaxis()->SetRangeUser(-0.000004, 0.000004); 
	graph_slope_instlumi_chamber_2->GetYaxis()->SetRangeUser(-0.000004, 0.000004); 
//	graph_slope_integratelumi_chamber_initial->GetYaxis()->SetRangeUser(-0.004,0.004); 
//	graph_slope_integratelumi_chamber->GetYaxis()->SetRangeUser(-0.004,0.004); 


	TCanvas *c = new TCanvas("c","pressure slope mean vs chamber",800,800);
	c->cd();
	c->SetGrid();
	gPad->SetGrid();
	axis_pressure_1->Draw();
  graph_slope_pressure_chamber_1->Draw("AP");
Double_t *gr_xarray_pressure = graph_slope_pressure_chamber_1->GetX();
Double_t *gr_yarray_pressure = graph_slope_pressure_chamber_1->GetY();
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
	graph_slope_pressure_chamber_2->Draw("AP");
  Double_t *gr_xarray_pressure_2 = graph_slope_pressure_chamber_2->GetX();
  Double_t *gr_yarray_pressure_2 = graph_slope_pressure_chamber_2->GetY();
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
	graph_slope_instlumi_chamber_1->Draw("AP");
  Double_t *gr_xarray_instlumi = graph_slope_instlumi_chamber_1->GetX();
  Double_t *gr_yarray_instlumi = graph_slope_instlumi_chamber_1->GetY();
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
	graph_slope_instlumi_chamber_2->Draw("AP");
  Double_t *gr_xarray_instlumi_2 = graph_slope_instlumi_chamber_2->GetX();
  Double_t *gr_yarray_instlumi_2 = graph_slope_instlumi_chamber_2->GetY();
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
*/
	output_file->cd();
  c->Write();
  c_2->Write();
  c1->Write();
  c1_2->Write();
  //c2_1->Write();
//  c2_initial->Write(); 
	output_file->Close();
}
