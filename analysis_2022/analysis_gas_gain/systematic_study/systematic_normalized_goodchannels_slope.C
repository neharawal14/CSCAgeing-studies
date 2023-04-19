void systematic_normalized_goodchannels_slope(){

 //  TString chamber[2] = {"ME11a", "ME11b" }; 
// TString chamber[32] = {"ME11a", "ME11b", "ME12HV1", "ME12HV2","ME12HV3", "ME13HV1","ME13HV2","ME13HV3","ME21HV1","ME21HV2", "ME21HV3", "ME22HV1", "ME22HV2", "ME22HV3", "ME22HV4","ME22HV5","ME31HV1","ME31HV2", "ME31HV3", "ME32HV1", "ME32HV2", "ME32HV3", "ME32HV4","ME32HV5","ME41HV1","ME41HV2", "ME41HV3", "ME42HV1", "ME42HV2", "ME42HV3", "ME42HV4","ME42HV5" };  
	bool debug = false;
 
     TString chamber[32] = {"ME11a", "ME11b", "ME12HV1", "ME12HV2","ME12HV3", "ME13HV1","ME13HV2","ME13HV3","ME21HV1","ME21HV2", "ME21HV3", "ME22HV1", "ME22HV2", "ME22HV3", "ME22HV4","ME22HV5","ME31HV1","ME31HV2", "ME31HV3", "ME32HV1", "ME32HV2", "ME32HV3", "ME32HV4","ME32HV5","ME41HV1","ME41HV2", "ME41HV3", "ME42HV1", "ME42HV2", "ME42HV3", "ME42HV4", "ME42HV5"};
	TString input_file_path = "/cmsuf/data/store/user/t2/users/neha.rawal/CSCAgeing_2022/analysis_2022/analysis_gas_gain/systematic_study/result_systematic_intlumi/";
	//TString result_path = "/cmsuf/data/store/user/t2/users/neha.rawal/CSCAgeing_newfiles/2017_again/final_files/final_analysis/result_systematic_slopes/";
	TString result_path = "/cmsuf/data/store/user/t2/users/neha.rawal/CSCAgeing_2022/analysis_2022/analysis_gas_gain/systematic_study/result_normalized_afterfit_intlumi/";
//	 TH1F *hist_chi_square_ndf[4];
 //  TString hist_chi_square_ndf_string;	 
/*
   for(int i=0; i<4; i++){ 	 
    hist_chi_square_ndf_string = TString::Format("hist_chi_square_ndf[%d]",i);	 
	  hist_chi_square_ndf[i] = new TH1F(hist_chi_square_ndf_string, " #chi^2 distribution",50,0,25);
	 } */
  if(debug) std::cout<<"going to start the loop"<<std::endl;

	 TH1F *hist_slope[32];
	
	for(int i=0; i<32;i++){
		TFile *f = TFile ::Open(input_file_path+"output_file_"+chamber[i]+".root");
		TString string_name = "intlumi_only_goodchannels";
	  hist_slope[i]	= (TH1F*) f->Get(string_name); 
 }	
	TF1 *f1;

	TFile *input_file;
	TTree *tree;
  TCanvas *c = new TCanvas("c","Slope");
  /* float chi2_per_ndf;
	 float mean_slope[2];
	 float mean_slope_error[2];
	 float sigma_slope[2];
 float i_list[2] ={1,2};

*/	
 	 float mean_slope[32];
	 float mean_slope_error[32];
	 float sigma_slope[32];
   float i_list[32] ={1,2,3,4,5,6,7,8,9,10,11,12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}; 
  if(debug) std::cout<<"going to start the loop again "<<std::endl;
	for(int i=0; i<32;i++){
//	for(int i=0; i<2;i++){
  if(debug) std::cout<<"will open root file "<<std::endl;
//	std::cout<<input_file_path<<chamber[i]+"/output_file.root"<<std::endl;
//  input_file = TFile::Open(input_file_path+"output_file"+chamber[i]+".root");
//  if(debug) std::cout<<"after opening root file"<<input_file<<std::endl;
	f1 = new TF1("f1","pol1",0,40); 
	f1->SetParName(1,"Slope");
	f1->SetParName(0,"Constant");

	// to put slopes separately for each layer
	c->SetName(chamber[i]);
  c->cd();
  gStyle->SetOptFit(1011);
	hist_slope[i]->SetTitle(chamber[i]);
	hist_slope[i]->GetXaxis()->SetTitle("Slope of Q vs #int L (/fb)");
	hist_slope[i]->GetYaxis()->SetRangeUser(0.9,1.1);                                                                                                                                                                                               
	hist_slope[i]->Fit(f1,"R");
  hist_slope[i]->Draw();
  c->SaveAs(result_path+"slope_"+chamber[i]+".pdf");
  c->Clear();
	mean_slope[i]  = f1->GetParameter(1);
	mean_slope_error[i]  = f1->GetParError(1);
		std::cout<<"issue just after canvas"<<std::endl;
		std::cout<<"mean and sigma from fit "<<mean_slope[i]<<" "<<sigma_slope[i]<<std::endl;  
		}

  	TGraphErrors *graph_integratelumi = new TGraphErrors(32,i_list, mean_slope,0,  mean_slope_error);
    TAxis *axis_integratelumi = graph_integratelumi->GetXaxis();
    axis_integratelumi->SetLabelSize(0.03);  

   for(int i=0; i<32;i++){ 
   //for(int i=0; i<2;i++){ 
		graph_integratelumi->GetXaxis()->SetBinLabel(graph_integratelumi->GetXaxis()->FindBin(i + 1.), chamber[i]); 
	 }
		graph_integratelumi->GetYaxis()->SetTitleOffset(1.7);                                                                                                                                                                                               
		graph_integratelumi->GetYaxis()->SetTitle("Mean of slope (rel charge vs int lumi) (/fb)");                                                                                                                                                                                               
    graph_integratelumi->GetYaxis()->SetRangeUser(-0.002,0.002);   

   TCanvas *c2_1 = new TCanvas("c2_1","intlumi slope mean vs chamber",1000,800); 
  c2_1->cd();                                                                                                                                                                                            
  c2_1->SetGrid(1,1); 
  axis_integratelumi->Draw();
  graph_integratelumi->Draw("AP*"); 
  c2_1->SaveAs(result_path+"mean_slope_integratelumi_chamber.pdf"); 
	std::cout<<"done with everything"<<std::endl;
}
