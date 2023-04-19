void plotting_graph(TGraphErrors *gr, TString layer_nb, TString);
void plotting_graph_chi2(TGraphErrors *gr, TString layer_nb, TString);
void plotting_histogram(TH1D *gr, TString layer_nb, TString);
void plotting_histogram_chi2(TH1D *gr, TString layer_nb, TString);
void instlumi_analysis_per_layer(){

 TString input_file_chamber[32]; 
//  TString input_file_chamber[1]; 
  TFile *file;	
	//TFile *file[2];
  //TString chamber[2] = {"ME11a", "ME11b", "ME12HV1", "ME12HV2", "ME12HV3", "ME13HV1", "ME13HV2", "ME13HV3", "ME21HV1", "ME21HV2", "ME21HV3", "ME22HV1", "ME22HV2", "ME22HV3", "ME22HV4", "ME22HV5", "ME31HV1", "ME31HV2", "ME31HV3", "ME2HV1", "ME2HV2", "ME2HV3", "ME2HV4", "ME2HV5", "ME41HV1", "ME41HV2" ,"ME41HV3", "ME42HV1", "ME42HV2", "ME42HV3", "ME42HV4", "ME42HV5"}; 
 // TString chamber[1] = {"ME12HV1"}; 
 TString chamber[32] = {"ME11a", "ME11b", "ME12HV1", "ME12HV2","ME12HV3", "ME13HV1","ME13HV2","ME13HV3","ME21HV1", "ME21HV2", "ME21HV3", "ME22HV1", "ME22HV2", "ME22HV3", "ME22HV4","ME22HV5","ME31HV1","ME31HV2", "ME31HV3", "ME32HV1", "ME32HV2", "ME32HV3", "ME32HV4","ME32HV5","ME41HV1","ME41HV2", "ME41HV3", "ME42HV1", "ME42HV2", "ME42HV3", "ME42HV4","ME42HV5"}; 
  
	bool debug = true;

//	TH1D *hist_slope_instlumi[32];
//	TH1D *hist_slope_instlumi_2[32];
//
///  TGraph *gr_instlumi_slope_plus[6];
  //TGraph *gr_instlumi_slope_minus[6];
	TH1D *hist_slope_instlumi_endcap_plus[32];
	TH1D *hist_slope_instlumi_endcap_plus_outer[32];
	TH1D *hist_slope_instlumi_endcap_minus[32];
	TH1D *hist_slope_instlumi_endcap_minus_outer[32];
	
	TH1D *hist_chi2_instlumi_endcap_plus[32];
	TH1D *hist_chi2_instlumi_endcap_minus[32];


	TCanvas *c, *c1;
	TCanvas *c_first, *c_second;
	TCanvas *c_first_minus, *c_second_minus;

  TString input_file_path = "/cmsuf/data/store/user/t2/users/neha.rawal/CSCAgeing_2022/analysis_2022/2022_output_files_new_way/";
	//outf_dataset15to23fbonly_ME12HV1_output.root";
	TString result_path = "/cmsuf/data/store/user/t2/users/neha.rawal/CSCAgeing_2022/analysis_2022/analysis_gas_gain/all_channels_per_layer_plots_instlumi/";
  
//	TFile *file = TFile::Open(input_file_path+"DUMMYFILENAME_2017_all_"+chamber[i]+"_tree.root";
  TFile *output_file = new TFile(result_path+"output_file_instlumi.root","RECREATE");

  if(debug) std::cout<<"after opening root file"<<std::endl;

  if(debug) std::cout<<"going to start the loop"<<std::endl;

	for(int i=0; i<32;i++){
   	TH1D *hist_slope_instlumi_all_layer = new TH1D("hist_slope_instlumi_all_layer", "slope distribution : all channels " , 80,-0.02,0.02); ;
   	TH1D *hist_chi2_instlumi_all_layer = new TH1D("hist_chi2_instlumi_all_layer", "chi2/ndf distribution : all channels " , 30,0,15); ;
		Float_t _slope, _slope_error, _chi2;
		Int_t _ndof, _chamber,_endcap;
	  Int_t	_layer;

		TGraphErrors *gr_instlumi_slope_plus[6];
 		TGraphErrors *gr_instlumi_slope_minus[6];
 		TGraphErrors *gr_instlumi_chi2_plus[6];
 		TGraphErrors *gr_instlumi_chi2_minus[6];

    THStack* hs_plus = new THStack("hs_plus", "Slope distribution");
    THStack* hs_minus = new THStack("hs_minus", "Slope distribution");
    TH1D *hist_instlumi_slope_per_layer_endcap[6];
    TH1D *hist_instlumi_slope_per_layer_endcap_plus[6];
    TH1D *hist_instlumi_slope_per_layer_endcap_minus[6];

    TH1D *hist_instlumi_chi2_per_layer_endcap[6];
    TH1D *hist_instlumi_chi2_per_layer_endcap_plus[6];
    TH1D *hist_instlumi_chi2_per_layer_endcap_minus[6];

		TString hist_string = TString::Format("hist_slope_instlumi_endcap_plus[%d]",i);
	  hist_slope_instlumi_endcap_plus[i] = new TH1D(hist_string, " slope of gas gain dependence ", 80,-0.00004,0.00004);
		hist_string = TString::Format("hist_slope_instlumi_endcap_plus_outer[%d]",i);
	  hist_slope_instlumi_endcap_plus_outer[i] = new TH1D(hist_string, " slope of gas gain dependence ", 80,-0.00004,0.00004);
		hist_string = TString::Format("hist_slope_instlumi_endcap_minus[%d]",i);
	  hist_slope_instlumi_endcap_minus[i] = new TH1D(hist_string, " slope of gas gain dependence ", 80,-0.00004,0.00004);
		hist_string = TString::Format("hist_slope_instlumi_endcap_minus_outer[%d]",i);
	  hist_slope_instlumi_endcap_minus_outer[i] = new TH1D(hist_string, " slope of gas gain dependence ", 80,-0.00004,0.00004);

 	  hist_string = TString::Format("hist_chi2_instlumi_endcap_plus[%d]",i);
	  hist_chi2_instlumi_endcap_plus[i] = new TH1D(hist_string, " chi2 of gas gain dependence ", 30,0,15);
		hist_string = TString::Format("hist_chi2_instlumi_endcap_minus[%d]",i);
	  hist_chi2_instlumi_endcap_minus[i] = new TH1D(hist_string, " chi2 of gas gain dependence ",30,0,15);


		for (int points = 0; points < 6; points++) {
			  gr_instlumi_slope_plus[points] = new TGraphErrors();
			  gr_instlumi_slope_minus[points] = new TGraphErrors();
			  gr_instlumi_chi2_plus[points] = new TGraphErrors();
			  gr_instlumi_chi2_minus[points] = new TGraphErrors();
		}

		for (int points = 0; points < 6; points++) {
			  hist_string = TString::Format("hist_instlumi_slope_per_layer_endcap[%d]",points);
				hist_instlumi_slope_per_layer_endcap[points] = new TH1D(hist_string," slope per layer ", 80, -0.00004,0.00004);

			  hist_string = TString::Format("hist_instlumi_slope_per_layer_endcap_plus[%d]",points);
				hist_instlumi_slope_per_layer_endcap_plus[points] = new TH1D(hist_string," slope per layer ", 80, -0.00004,0.00004);
  			hist_string = TString::Format("hist_instlumi_slope_per_layer_endcap_minus[%d]",points);
				hist_instlumi_slope_per_layer_endcap_minus[points] = new TH1D(hist_string," slope per layer ", 80, -0.00004,0.00004);

				hist_string = TString::Format("hist_instlumi_chi2_per_layer_endcap[%d]",points);
				hist_instlumi_chi2_per_layer_endcap[points] = new TH1D(hist_string," chi2 per layer ",30,0,15);

			  hist_string = TString::Format("hist_instlumi_chi2_per_layer_endcap_plus[%d]",points);
				hist_instlumi_chi2_per_layer_endcap_plus[points] = new TH1D(hist_string," chi2 per layer ",30,0,15);
  			hist_string = TString::Format("hist_instlumi_chi2_per_layer_endcap_minus[%d]",points);
				hist_instlumi_chi2_per_layer_endcap_minus[points] = new TH1D(hist_string," chi2 per layer ", 30,0,15);


    }	

		TTree * tree_instlumi;
//  input_file_chamber[i] = input_file_path + "DUMMYFILENAME_2017_all_"+chamber[i]+"_tree.root";outf_dataset25to36fbonly_ME11a_output.root
    input_file_chamber[i] = input_file_path + "outf_dataset25to36fbonly_" +chamber[i]+"_output.root";
    std::cout<<"filename "<<input_file_chamber[i]<<std::endl;	
	
 	  file = TFile::Open(input_file_chamber[i]);
	//std::cout<<"input file "<<file<<std::endl; 
	 tree_instlumi = (TTree*) file->Get("tree__instlumi");	
	 tree_instlumi->SetBranchAddress("_slope",&_slope);
	 tree_instlumi->SetBranchAddress("_slope_error",&_slope_error);
	 tree_instlumi->SetBranchAddress("_layer",&_layer);
	 tree_instlumi->SetBranchAddress("_chamber",&_chamber);
	 tree_instlumi->SetBranchAddress("_endcap",&_endcap);
	 tree_instlumi->SetBranchAddress("_chi2",&_chi2);
	 tree_instlumi->SetBranchAddress("_ndof",&_ndof);


		//ofstream text_file; 
		//text_file.open("ME12HV1_test.txt");
	 std::cout<<"entering into tree"<<std::endl; 
	 for(int entry=0; entry<tree_instlumi->GetEntries(); entry++) {
    tree_instlumi->GetEntry(entry);
		//text_file<<"entering the tree : entry number "<<entry<<" channel "<<_chamber<<" layer "<<_layer<<" endcap "<<_endcap<<std::endl;
		double chi2_ndof = _chi2/_ndof;
	 
		for(int k=0; k<6; k++){
	   if(_layer ==k+1 && _endcap==1) {
          hist_slope_instlumi_all_layer->Fill(_slope); 

         hist_chi2_instlumi_all_layer->Fill(chi2_ndof); 
		     //text_file<<" chamber "<<_chamber<<" endcap "<<_endcap<<" layer "<<_layer<<" slope "<<_slope<<std::endl; 	 
				 hist_instlumi_slope_per_layer_endcap_plus[k]->Fill(_slope);
				 hist_instlumi_slope_per_layer_endcap[k]->Fill(_slope);
    		 gr_instlumi_slope_plus[k]->SetPoint(_chamber,_chamber,_slope);
	 	  	 gr_instlumi_slope_plus[k]->SetPointError(_chamber,0, _slope_error);

				 hist_instlumi_chi2_per_layer_endcap_plus[k]->Fill(chi2_ndof);
				 hist_instlumi_chi2_per_layer_endcap[k]->Fill(chi2_ndof);
    		 gr_instlumi_chi2_plus[k]->SetPoint(_chamber,_chamber,chi2_ndof);
	 			 gr_instlumi_chi2_plus[k]->SetPointError(_chamber,0, 0);

					 }

	 if(_layer ==k+1 && _endcap==2) {
//		     std::cout<<" chamber "<<_chamber<<" endcap "<<_endcap<<" layer "<<_layer<<" slope "<<_slope<<std::endl; 	 
	    	 
          hist_slope_instlumi_all_layer->Fill(_slope); 

         hist_chi2_instlumi_all_layer->Fill(chi2_ndof); 
		     hist_instlumi_slope_per_layer_endcap_minus[k]->Fill(_slope);
				 hist_instlumi_slope_per_layer_endcap[k]->Fill(_slope);
	    	 std::cout<<" channe; "<<_chamber<<" endcap "<<_endcap<<" layer "<<_layer<<" slope "<<_slope<<std::endl; 	 
		     gr_instlumi_slope_minus[k]->SetPoint(_chamber,_chamber,_slope);
	 			 gr_instlumi_slope_minus[k]->SetPointError(_chamber,0, _slope_error);

				 hist_instlumi_chi2_per_layer_endcap_minus[k]->Fill(chi2_ndof);
				 hist_instlumi_chi2_per_layer_endcap[k]->Fill(chi2_ndof);
    		 gr_instlumi_chi2_minus[k]->SetPoint(_chamber,_chamber,chi2_ndof);
	 			 gr_instlumi_chi2_minus[k]->SetPointError(_chamber,0, 0);

					}
	 }
	 if(_layer ==1 ||_layer==6) {
		 if(_endcap==1)  hist_slope_instlumi_endcap_plus_outer[i]->Fill(_slope);
		 else hist_slope_instlumi_endcap_minus_outer[i]->Fill(_slope);
	 }
	 if(_layer ==2 ||_layer==3 || _layer==4 || _layer==5 ) {
		    if(_endcap==1)  hist_slope_instlumi_endcap_plus[i]->Fill(_slope);
		    if(_endcap==2) 	 hist_slope_instlumi_endcap_minus[i]->Fill(_slope);
	 }

  }
	 // ended reading the tree
	 for(int k=0; k<6; k++){	
 		 TString layer_nb_plus = TString::Format("layer_%d_plus",k+1);
		 TString layer_nb_minus = TString::Format("layer_%d_minus",k+1);
		 plotting_graph(gr_instlumi_slope_plus[k],layer_nb_plus,chamber[i] );
		 plotting_graph(gr_instlumi_slope_minus[k], layer_nb_minus,chamber[i]);
	   plotting_histogram(hist_instlumi_slope_per_layer_endcap_plus[k], layer_nb_plus,chamber[i]);
	   plotting_histogram(hist_instlumi_slope_per_layer_endcap_minus[k], layer_nb_minus,chamber[i]);

		 TString layer_nb = TString::Format("layer_%d_both",k+1);
	   plotting_histogram(hist_instlumi_slope_per_layer_endcap[k], layer_nb,chamber[i]);

		 plotting_graph_chi2(gr_instlumi_chi2_plus[k],layer_nb_plus,chamber[i] );
		 plotting_graph_chi2(gr_instlumi_chi2_minus[k], layer_nb_minus,chamber[i]);
	   plotting_histogram_chi2(hist_instlumi_chi2_per_layer_endcap_plus[k], layer_nb_plus,chamber[i]);
	   plotting_histogram_chi2(hist_instlumi_chi2_per_layer_endcap_minus[k], layer_nb_minus,chamber[i]);
	   plotting_histogram_chi2(hist_instlumi_chi2_per_layer_endcap[k], layer_nb,chamber[i]);


	 }


	   plotting_histogram(hist_slope_instlumi_all_layer, "all_chamber_slope",chamber[i]);
	   plotting_histogram_chi2(hist_chi2_instlumi_all_layer, "all_chamber_chi2",chamber[i]);

	 hist_slope_instlumi_endcap_plus[i]->SetFillColor(kBlue);
	 hist_slope_instlumi_endcap_plus_outer[i]->SetFillColor(kRed);
	 hist_slope_instlumi_endcap_minus[i]->SetFillColor(kBlue);
	 hist_slope_instlumi_endcap_minus_outer[i]->SetFillColor(kRed);

//	 hist_slope_instlumi_endcap_plus[i]->SetStats(1);
//	 hist_slope_instlumi_endcap_plus_outer[i]->SetStats(1);
//	 hist_slope_instlumi_endcap_minus[i]->SetStats(1);
//	 hist_slope_instlumi_endcap_minus_outer[i]->SetStats(1);

/*	 hist_slope_instlumi_endcap_plus[i]->SetStatFormat("Variable 1: Mean=%f, RMS=%f");
	 hist_slope_instlumi_endcap_plus_outer[i]->SetStatFormat("Variable 2: Mean=%f, RMS=%f");
	 hist_slope_instlumi_endcap_minus[i]->SetStatFormat("Variable 3: Mean=%f, RMS=%f");
	 hist_slope_instlumi_endcap_minus_outer[i]->SetStatFormat("Variable 4: Mean=%f, RMS=%f");

	 hist_slope_instlumi_endcap_plus[i]->SetStatTextColor(kBlue); 
	 hist_slope_instlumi_endcap_plus_outer[i]->SetStatTextColor(kRed); 
	 hist_slope_instlumi_endcap_minus[i]->SetStatTextColor(kBlue); 
	 hist_slope_instlumi_endcap_minus_outer[i]->SetStatTextColor(kRed); 

	 TString label1 = "Variable 1";
	 TString label2 = "Variable 2";
	 TString label3 = "Variable 3";
	 TString label4 = "Variable 4";

	 hist_slope_instlumi_endcap_plus[i]->SetLabel(label1);
	 hist_slope_instlumi_endcap_plus_outer[i]->SetLabel(label2);
	 hist_slope_instlumi_endcap_minus[i]->SetLabel(label3);
	 hist_slope_instlumi_endcap_minus_outer[i]->SetLabel(label4);
*/

   c_first = new TCanvas("c_first"," canvas firsrt" );
	 c_first->cd(); 
	 hist_slope_instlumi_endcap_plus[i]->Draw();
   c_first->Update();
	 TPaveStats *st1 = (TPaveStats*)hist_slope_instlumi_endcap_plus[i]->FindObject("stats");
	 c_first->Close();

	 c_second = new TCanvas("c_second"," canvas firsrt" );
	 c_second->cd(); 
	 hist_slope_instlumi_endcap_plus_outer[i]->Draw();
	 c_second->Update();
   TPaveStats *st2 = (TPaveStats*)hist_slope_instlumi_endcap_plus_outer[i]->FindObject("stats");
	 hist_slope_instlumi_endcap_plus_outer[i]->Draw();
	 c_second->Close();

	 c_first_minus = new TCanvas("c_first_minus"," canvas firsrt" );
	 c_first_minus->cd(); 
	 hist_slope_instlumi_endcap_minus[i]->Draw();
   c_first_minus->Update();
	 TPaveStats *st3 = (TPaveStats*)hist_slope_instlumi_endcap_minus[i]->FindObject("stats");
	 c_first_minus->Close();

	 c_second_minus = new TCanvas("c_second_minus"," canvas fsecond" );
	 c_second_minus->cd(); 
	 hist_slope_instlumi_endcap_minus_outer[i]->Draw();
   c_second_minus->Update();
	 TPaveStats *st4 = (TPaveStats*)hist_slope_instlumi_endcap_minus_outer[i]->FindObject("stats");
	 c_second_minus->Close();

	 
   hs_plus->Add(hist_slope_instlumi_endcap_plus_outer[i]);
   hs_plus->Add(hist_slope_instlumi_endcap_plus[i]);

	 hs_minus->Add(hist_slope_instlumi_endcap_minus_outer[i]);
   hs_minus->Add(hist_slope_instlumi_endcap_minus[i]);
   st1->SetX1NDC(.7); st1->SetX2NDC(.9); 
   st1->SetY1NDC(.7); st1->SetY2NDC(.9); 
   st2->SetX1NDC(.7); st2->SetX2NDC(.9); 
   st2->SetY1NDC(.5); st2->SetY2NDC(.7); 
   st1->SetLineColor(kBlue);
   st2->SetLineColor(kRed);

   st3->SetX1NDC(.7); st3->SetX2NDC(.9); 
   st3->SetY1NDC(.7); st3->SetY2NDC(.9); 
   st4->SetX1NDC(.7); st4->SetX2NDC(.9); 
   st4->SetY1NDC(.5); st4->SetY2NDC(.7); 
   st3->SetLineColor(kBlue);
   st4->SetLineColor(kRed);

	 c = new TCanvas("c","canvas ", 1000,800);
	 c->cd();
//	 gStyle->SetOptStat();
	 hs_plus->Draw();
	 hs_plus->GetXaxis()->SetTitle("Slope of charge  vs instlumi (/#mu b s)");
   c->Update(); //to for the generation of the 'stat" boxes 
	 st1->Draw();
	 st2->Draw();
//TPaveStats *st1 = (TPaveStats*)hs_plus->GetListOfFunctions()->FindObject("stats");
//TPaveStats *st1 = (TPaveStats*)hist_slope_instlumi_endcap_plus[i]->FindObject("stats");
//TPaveStats *st2 = (TPaveStats*)hist_slope_instlumi_endcap_plus_outer[i]->FindObject("stats");
//TPaveStats *st2 = (TPaveStats*)hist_slope_instlumi_endcap_plus_outer[i]->GetListOfFunctions()->FindObject("stats");

//TPaveStats *st2 = (TPaveStats*)hs_plus->GetStack()->FindObject("hist_slope_instlumi_endcap_plus_outer[i]")->FindObject("stats"); 
//c->Modified();
	 c->SaveAs("./all_channels_per_layer_plots_instlumi/histogram_"+chamber[i]+"_plus.pdf");
	 c->Close();


	 c1 = new TCanvas("c1","canvas ", 1000,800);
	 c1->cd();
	 hs_minus->Draw();
	 hs_minus->GetXaxis()->SetTitle("Slope of charge  vs instlumi (/#mu b s)");
	 c1->Update();
	 st3->Draw(); 
	 st4->Draw(); 
	 c1->SaveAs("./all_channels_per_layer_plots_instlumi/histogram_"+chamber[i]+"_minus.pdf");
	 c1->Close();


	 // canvas plotting chi2
}

}
	 // plotting the graphs on canvas
	 //if(_layer ==2 && endcap==2) hist_slope_instlumi_layer2_endcap_plus[i]->Fill(_slope);
	 //if(_layer ==3 && endcap==2) hist_slope_instlumi_layer3_endcap_plus[i]->Fill(_slope);	 std::cout<<"existing filling entrues"<<std::endl;
	 //if(_layer ==4 && endcap==2) hist_slope_instlumi_layer4_endcap_plus[i]->Fill(_slope);	 }
	 //if(_layer ==5 && endcap==2) hist_slope_instlumi_layer5_endcap_plus[i]->Fill(_slope);//	hist_slope_instlumi_2[i] = (TH1D*) file->Get("h_slope_instlumi_2__dataset25to36fbonly");	
	 //if(_layer ==6 && endcap==2) hist_slope_instlumi_layer6_endcap_plus[i]->Fill(_slope);//  hist_slope_instlumi[i] = (TH1D*) file->Get("h_slope_instlumi__dataset25to36fbonly");	
//  hist_slope_instlumi_2[i] = (TH1D*) file->Get("h_slope_instlumi_2__dataset25to36fbonly");	
//	 for(int bin =1 ; bin<=hist_slope_instlumi[i]->GetNbinsX(); bin++){
//	 hist_slope_instlumi_new[i]->Fill(hist_slope_instlumi[i]->GetBinContent(bin));
//	 }
 // hist_slope_integratelumi_initial[i] = (TH1D*) file->Get("h_slope_integratelumi_initial_DUMMYFILENAME_2017_new_all_"+chamber[i]+"_tree14to26fbonly_7e33to9e33");	
//  hist_slope_integratelumi[i] = (TH1D*) file->Get("h_slope_integratelumi_DUMMYFILENAME_2017_all_"+chamber[i]+"_tree14to26fbonly_7e33to9e33");	

//	hist_slope_instlumi[i]->Rebin(3);

//	TF1 *gaus1_layer1 = new TF1("gaus1_layer1","gaus",-0.016,0.001);
//	TF1 *gaus1_layer2 = new TF1("gaus1_layer2","gaus",-0.016,0.001);
//	TF1 *gaus1_layer3 = new TF1("gaus1_layer3","gaus",-0.016,0.001);
//	TF1 *gaus1_layer4 = new TF1("gaus1_layer4","gaus",-0.016,0.001);
//	TF1 *gaus1_layer5 = new TF1("gaus1_layer5","gaus",-0.016,0.001);
//	TF1 *gaus1_layer6 = new TF1("gaus1_layer6","gaus",-0.016,0.001);
//	TF1 *gaus1 = new TF1("gaus1","gaus",-0.016,0.001);
//	TF1 *gaus2 = new TF1("gaus2","gaus",-0.00004,0.00004);
////	TF1 *gaus_3 = new TF1("gaus_3","gaus",-0.00001,0.00001);
//  TF1 *gaus1_2 = new TF1("gaus1_2","gaus",-0.001,0.001);
//	TF1 *gaus2_2 = new TF1("gaus2_2","gaus",-0.000002,0.000002);
//	TF1 *gaus2_new = new TF1("gaus2_new","gaus",-0.000002,0.000002);
//	TF1 *gaus3_initial = new TF1("gaus3_initial","gaus",-0.005,0.005);
//	TF1 *gaus3 = new TF1("gaus3","gaus",-0.005,0.005);

//	gStyle->SetOptFit(1011);
//	hist_slope_instlumi[i]->Fit(gaus1,"R");
 
//	gStyle->SetOptFit(1011);
//	hist_slope_instlumi_layer1[i]->Fit(gaus1_layer1,"R");
//  gStyle->SetOptFit(1011);                
//	hist_slope_instlumi_layer2[i]->Fit(gaus1_layer2,"R");
//  gStyle->SetOptFit(1011);                
//	hist_slope_instlumi_layer3[i]->Fit(gaus1_layer3,"R");
//  gStyle->SetOptFit(1011);               
//	hist_slope_instlumi_layer4[i]->Fit(gaus1_layer4,"R");
//  gStyle->SetOptFit(1011);              
//	hist_slope_instlumi_layer5[i]->Fit(gaus1_layer5,"R");
//  gStyle->SetOptFit(1011);             
//	hist_slope_instlumi_layer6[i]->Fit(gaus1_layer6,"R");

/*	mean_slope_instlumi[i] = gaus1->GetParameter(1);
	mean_slope_instlumi_unc[i] = gaus1->GetParameter(2);
	
	hist_slope_instlumi_2[i]->Fit(gaus1_2,"R");
 	
	mean_slope_instlumi_2[i] = gaus1_2->GetParameter(1);
	mean_slope_instlumi_unc_2[i] = gaus1_2->GetParameter(2);

	if(i== 0 || i ==1 || i==8 |  i==9 |   i==10 || i==16 |  i==17 |   i==18 || i==24 |  i==25 |   i==26 ){
	hist_slope_instlumi[i]->Fit(gaus_3,"R");
	mean_slope_instlumi[i] = gaus_3->GetParameter(1);
	mean_slope_instlumi_unc[i] = gaus_3->GetParError(1); }

	else */
/*	hist_slope_instlumi[i]->Fit(gaus2,"R");
	mean_slope_instlumi[i] = gaus2->GetParameter(1);
	mean_slope_instlumi_unc[i] = gaus2->GetParameter(2); 
*/ 
/*	hist_slope_instlumi_new[i]->Fit(gaus2_new,"R");

	mean_slope_instlumi_new[i] = gaus2_new->GetParameter(1);
	mean_slope_instlumi_unc_new[i] = gaus2_new->GetParError(1);
*/
/*
	hist_slope_instlumi_2[i]->Fit(gaus2_2,"R");

	mean_slope_instlumi_2[i] = gaus2_2->GetParameter(1);
	mean_slope_instlumi_unc_2[i] = gaus2_2->GetParameter(2); */

///	hist_slope_integratelumi[i]->Fit(gaus3,"R");

//	mean_slope_integratelumi[i] = gaus3->GetParameter(1);
//	mean_slope_integratelumi_unc[i] = gaus3->GetParError(1);
/*
	hist_slope_integratelumi_initial[i]->Fit(gaus3_initial,"R");

	mean_slope_integratelumi_initial[i] = gaus3_initial->GetParameter(1);
	mean_slope_integratelumi_initial_unc[i] = gaus3_initial->GetParError(1);



 	TCanvas *c_instlumi = new TCanvas("c_instlumi","instlumi plot of i th file after instlumi correction for first time",700,700);
  c_instlumi->cd();
	hist_slope_instlumi[i]->GetXaxis()->SetRangeUser(-0.016, 0.0);
	hist_slope_instlumi[i]->GetXaxis()->SetTitle("slope of #Delta Q vs instlumi (hPa)");
  hist_slope_instlumi[i]->Draw();
  c_instlumi->SaveAs(result_path+"slope_instlumi_"+chamber[i]+".pdf");
  c_instlumi->Close();
*/
void plotting_histogram(TH1D *h, TString layer_nb, TString chamber_name){	

	TF1 *f = new TF1("f","gaus",-0.00004,0.00004);
  h->Fit(f,"R");
	gStyle->SetOptFit(1011);  
  TCanvas *c_instlumi = new TCanvas("c_instlumi","instlumi plot of i th file after instlumi correction for first time",1300,1000);
  c_instlumi->cd();
	//gr->GetXaxis()->SetTickLength(1);
//  gr->GetXaxis()->SetBinLabel(gr->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label
	h->GetXaxis()->SetTitle("Slope of charge vs instlumi (/#mu b s)");
	h->GetYaxis()->SetTitle("Nb of channels");
  h->Draw();
  c_instlumi->SaveAs("./all_channels_per_layer_plots/instlumi_"+chamber_name+"_per_"+layer_nb+"layer.pdf");
  c_instlumi->Close();
}
void plotting_histogram_chi2(TH1D *h, TString layer_nb, TString chamber_name){	
	gStyle->SetOptFit(1011);  
  TCanvas *c_instlumi = new TCanvas("c_instlumi","instlumi plot of i th file after instlumi correction for first time",1300,1000);
  c_instlumi->cd();
	//gr->GetXaxis()->SetTickLength(1);
//  gr->GetXaxis()->SetBinLabel(gr->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label
	h->GetXaxis()->SetTitle("chi2/ndf");
	h->GetYaxis()->SetTitle("Nb of channels");
  h->Draw();
  c_instlumi->SaveAs("./all_channels_per_layer_plots/chi2_"+chamber_name+"_per_"+layer_nb+"layer.pdf");
  c_instlumi->Close();
}
void plotting_graph(TGraphErrors *gr, TString layer_nb, TString chamber_name){	
  TCanvas *c_instlumi = new TCanvas("c_instlumi","instlumi plot of i th file after instlumi correction for first time",1300,1000);
  c_instlumi->cd();
	gr->GetXaxis()->SetRangeUser(0, 37);
	gr->GetYaxis()->SetRangeUser(-0.00004,0.00004);
	//gr->GetXaxis()->SetTickLength(1);
	TAxis *axis_instlumi_1 = gr->GetXaxis();
	axis_instlumi_1->SetLabelSize(0.03);
//  gr->GetXaxis()->SetBinLabel(gr->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label
	gr->GetYaxis()->SetTitle("slope of Charge vs instlumi (/#mu b s)");
	gr->GetYaxis()->SetTitleOffset(1.5);
	gr->GetXaxis()->SetTitle("chamber number");
  gr->Draw("AP*");
  c_instlumi->SaveAs("./all_channels_per_layer_plots_instlumi/slope_instlumi_"+chamber_name+"_"+layer_nb+".pdf");
  c_instlumi->Close();
}
void plotting_graph_chi2(TGraphErrors *gr, TString layer_nb, TString chamber_name){	
  TCanvas *c_instlumi = new TCanvas("c_instlumi","chi 2 /ndf ",1300,1000);
  c_instlumi->cd();
	gr->GetXaxis()->SetRangeUser(0, 36);
	gr->GetYaxis()->SetRangeUser(0,10);
	//gr->GetXaxis()->SetTickLength(1);
	TAxis *axis_instlumi_1 = gr->GetXaxis();
	axis_instlumi_1->SetLabelSize(0.03);
//  gr->GetXaxis()->SetBinLabel(gr->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label
	gr->GetYaxis()->SetTitle("chi2/ndf ");
	gr->GetYaxis()->SetTitleOffset(1.0);
	gr->GetXaxis()->SetTitle("chamber number");
  gr->Draw("AP*");
  c_instlumi->SaveAs("./all_channels_per_layer_plots_instlumi/chi2_instlumi_"+chamber_name+"_"+layer_nb+".pdf");
  c_instlumi->Close();
}

 // c_instlumi->Delete();
/*

	TCanvas *c_instlumi_2 = new TCanvas("c_instlumi_2","instlumi plot of i th file after instlumi correction for second time",700,700);
  c_instlumi_2->cd();
	hist_slope_instlumi_2[i]->GetXaxis()->SetRangeUser(-0.001, 0.001);
	hist_slope_instlumi_2[i]->GetXaxis()->SetTitle("slope of #Delta Q vs instlumi (hPa)");
  hist_slope_instlumi_2[i]->Draw();
  c_instlumi_2->SaveAs(result_path+"slope_instlumi_"+chamber[i]+"_second.pdf");
  c_instlumi_2->Close();

	TCanvas *c_instlumi = new TCanvas("c_instlumi","instlumi plot of i th file after instlumi correction for first time",700,700);
  c_instlumi->cd();
	hist_slope_instlumi[i]->GetXaxis()->SetRangeUser(-0.00004, 0.00004);
	hist_slope_instlumi[i]->GetXaxis()->SetTitle("slope of #Delta Q vs inst lumi (#mu b^{-1} s^{-1})");
  hist_slope_instlumi[i]->Draw();
  c_instlumi->SaveAs(result_path+"slope_instlumi_"+chamber[i]+".pdf");
  c_instlumi->Close();

	TCanvas *c_instlumi_2 = new TCanvas("c_instlumi_2","instlumi plot of i th file after instlumi correction for second time",700,700);
  c_instlumi_2->cd();
	hist_slope_instlumi_2[i]->GetXaxis()->SetRangeUser(-0.000002, 0.000002);
	hist_slope_instlumi_2[i]->GetXaxis()->SetTitle("slope of #Delta Q vs inst lumi (#mu b^{-1} s^{-1})");
  hist_slope_instlumi_2[i]->Draw();
  c_instlumi_2->SaveAs(result_path+"slope_instlumi_"+chamber[i]+"_second.pdf");
  c_instlumi_2->Close();

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


	TCanvas *c_intlumi = new TCanvas("c_intlumi","int lumi plot of i th file after instlumi and instlumi  correction",700,700);
  c_intlumi->cd();
  hist_slope_integratelumi[i]->Draw();
  c_intlumi->SaveAs(result_path+"slope_intlumi_"+chamber[i]+".pdf");
  c_intlumi->Close();


  std::cout<<"mean slope value for chamber "<<chamber[i]<<std::endl;
	std::cout<<mean_slope_instlumi[i]<<std::endl;
	std::cout<<mean_slope_instlumi_2[i]<<std::endl;
//	std::cout<<mean_slope_instlumi[i]<<std::endl;
//	std::cout<<mean_slope_instlumi_2[i]<<std::endl; 
//	std::cout<<mean_slope_integratelumi_initial[i]<<std::endl;
	//std::cout<<mean_slope_integratelumi[i]<<std::endl;
	std::cout<<"************************************"<<std::endl;
  
	//if(debug) std::cout<<" bin number and the setted mean value for instlumi "<<i<<" mean "<<mean_slope_instlumi[i]<<" chamber[i] "<<chamber[i]<<std::endl;
  

  file->Close();
*/	
 // output_file->cd();
  //hist_slope_instlumi[i]->Write();	
//	hist_slope_instlumi[i]->Write();
//	hist_slope_integratelumi[i]->Write();
	
/*
 float i_list[32] ={1,2,3,4,5,6,7,8,9,10,11,12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};
//  float i_list[32] ={1,3,5,7,9,11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63};
	// make the graphs 
  graph_slope_instlumi_chamber_1 = new TGraphErrors(32,i_list,mean_slope_instlumi, 0,mean_slope_instlumi_unc);
  graph_slope_instlumi_chamber_2 = new TGraphErrors(32,i_list,mean_slope_instlumi_2, 0, mean_slope_instlumi_unc_2);
  graph_slope_instlumi_chamber_1 = new TGraphErrors(32,i_list,mean_slope_instlumi, 0,mean_slope_instlumi_unc);
  graph_slope_instlumi_chamber_2 = new TGraphErrors(32,i_list,mean_slope_instlumi_2, 0,mean_slope_instlumi_unc_2); 
//  graph_slope_integratelumi_chamber_initial = new TGraphErrors(32,i_list,mean_slope_integratelumi_initial, 0 , mean_slope_integratelumi_initial_unc);
  //graph_slope_integratelumi_chamber = new TGraphErrors(32,i_list,mean_slope_integratelumi, 0 , mean_slope_integratelumi_unc);

	graph_slope_instlumi_chamber_1->GetYaxis()->SetTitle("Mean of slope(rel charge vs instlumi(hPa))");
  graph_slope_instlumi_chamber_1->GetYaxis()->SetTitle("Mean of slope(rel charge vs inst lumi (#mu b^{-1} s^{-1}))");
  graph_slope_instlumi_chamber_2->GetYaxis()->SetTitle("Mean of slope(rel charge vs instlumi (hPa))");
  graph_slope_instlumi_chamber_2->GetYaxis()->SetTitle("Mean of slope(rel charge vs inst lumi (#mu b^{-1} s^{-1}))"); 
 // graph_slope_integratelumi_chamber->GetYaxis()->SetTitle("Mean of slope(rel charge vs integrate lumi) (/fb)");
//  graph_slope_integratelumi_chamber_initial->GetYaxis()->SetTitle("Mean of slope(rel charge vs integrate lumi) initial (/fb)");


	
  output_file->cd();
	graph_slope_instlumi_chamber_1->GetXaxis()->SetTickLength(1);
	graph_slope_instlumi_chamber_2->GetXaxis()->SetTickLength(1);
	graph_slope_instlumi_chamber_1->GetXaxis()->SetTickLength(1);
	graph_slope_instlumi_chamber_2->GetXaxis()->SetTickLength(1);
//	graph_slope_integratelumi_chamber_initial->GetXaxis()->SetTickLength(1);
//	graph_slope_integratelumi_chamber->GetXaxis()->SetTickLength(1);

//	axis_instlumi_1->SetTickSize(0.7);
//	axis_instlumi_1->GetTicks();
	if(debug) std::cout<<" before declaring axes "<<std::endl;
	TAxis *axis_instlumi_1 = graph_slope_instlumi_chamber_1->GetXaxis();
	axis_instlumi_1->SetLabelSize(0.03);
	TAxis *axis_instlumi_2 = graph_slope_instlumi_chamber_2->GetXaxis();
	axis_instlumi_2->SetLabelSize(0.03);
//	axis_instlumi_2->SetTickSize(0.7);
	TAxis *axis_instlumi_1 = graph_slope_instlumi_chamber_1->GetXaxis();
	axis_instlumi_1->SetLabelSize(0.03);
//	axis_instlumi_1->SetTickSize(0.7);
	TAxis *axis_instlumi_2 = graph_slope_instlumi_chamber_2->GetXaxis();
	axis_instlumi_2->SetLabelSize(0.03); 
//	axis_instlumi_2->SetTickSize(0.7);
//	TAxis *axis_integratelumi_initial = graph_slope_integratelumi_chamber_initial->GetXaxis();
//	axis_integratelumi_initial->SetLabelSize(0.03);
//	axis_integratelumi_initial->SetTickSize(0.7);
 	TAxis *axis_integratelumi = graph_slope_integratelumi_chamber->GetXaxis();
	axis_integratelumi->SetLabelSize(0.03);
	if(debug) std::cout<<" after declaring axes "<<std::endl;


//	graph_slope_instlumi_chamber->GetXaxis()->SetLabelSize(0.03);
	for(int i=0; i<32; i++){  
  graph_slope_instlumi_chamber_1->GetXaxis()->SetBinLabel(graph_slope_instlumi_chamber_1->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label
  graph_slope_instlumi_chamber_2->GetXaxis()->SetBinLabel(graph_slope_instlumi_chamber_2->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label
  graph_slope_instlumi_chamber_1->GetXaxis()->SetBinLabel(graph_slope_instlumi_chamber_1->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label
  graph_slope_instlumi_chamber_2->GetXaxis()->SetBinLabel(graph_slope_instlumi_chamber_2->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label
 // graph_slope_integratelumi_chamber_initial->GetXaxis()->SetBinLabel(graph_slope_integratelumi_chamber_initial->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label
  //graph_slope_integratelumi_chamber->GetXaxis()->SetBinLabel(graph_slope_integratelumi_chamber->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label
//  graph_slope_instlumi_chamber_2->GetXaxis()->SetBinLabel(graph_slope_instlumi_chamber_2->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label
 // graph_slope_instlumi_chamber_1->GetXaxis()->SetBinLabel(graph_slope_instlumi_chamber_1->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label
 // graph_slope_instlumi_chamber_2->GetXaxis()->SetBinLabel(graph_slope_instlumi_chamber_2->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label
//  graph_slope_integratelumi_chamber_initial->GetXaxis()->SetBinLabel(graph_slope_integratelumi_chamber_initial->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label
//  graph_slope_integratelumi_chamber->GetXaxis()->SetBinLabel(graph_slope_integratelumi_chamber->GetXaxis()->FindBin(i + 1.), chamber[i]); // Find out which bin on the x-axis the point corresponds to and set the bin label


//	ofstream myfile_slope_values; 
//	myfile_slope_values.open("slope_values.txt");
//  myfile_slope_values<<graph_slope_instlumi_chamber_1->GetPoint(i,


	}




///  TFile *output_file = new TFile("output_file.root","RECREATE");
	graph_slope_instlumi_chamber_1->GetXaxis()->SetTitleOffset(0.1); 
	graph_slope_instlumi_chamber_2->GetXaxis()->SetTitleOffset(0.1); 
	graph_slope_instlumi_chamber_1->GetXaxis()->SetTitleOffset(0.1); 
	graph_slope_instlumi_chamber_2->GetXaxis()->SetTitleOffset(0.1); 
//	graph_slope_integratelumi_chamber_initial->GetXaxis()->SetTitleOffset(0.1); 
//	graph_slope_integratelumi_chamber->GetXaxis()->SetTitleOffset(0.1); 


	graph_slope_instlumi_chamber_1->GetYaxis()->SetTitleOffset(1.5); 
	graph_slope_instlumi_chamber_2->GetYaxis()->SetTitleOffset(1.5); 
	graph_slope_instlumi_chamber_1->GetYaxis()->SetTitleOffset(1.5); 
	graph_slope_instlumi_chamber_2->GetYaxis()->SetTitleOffset(1.5); 
//	graph_slope_integratelumi_chamber_initial->GetYaxis()->SetTitleOffset(1.7); 
//	graph_slope_integratelumi_chamber->GetYaxis()->SetTitleOffset(1.7); 

	graph_slope_instlumi_chamber_1->GetYaxis()->SetRangeUser(-0.010,0.002); 
	graph_slope_instlumi_chamber_2->GetYaxis()->SetRangeUser(-0.01,0.002); 
	graph_slope_instlumi_chamber_1->GetYaxis()->SetRangeUser(-0.000001, 0.000003); 
	graph_slope_instlumi_chamber_2->GetYaxis()->SetRangeUser(-0.000001, 0.000003); 
//	graph_slope_integratelumi_chamber_initial->GetYaxis()->SetRangeUser(-0.004,0.004); 
//	graph_slope_integratelumi_chamber->GetYaxis()->SetRangeUser(-0.004,0.004); 


	TCanvas *c = new TCanvas("c","instlumi slope mean vs chamber",800,800);
	c->cd();
	c->SetGrid();
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
	c->SaveAs(result_path+"mean_slope_instlumi_with_chamber.pdf"); 
	TCanvas *c_2 = new TCanvas("c_2","instlumi slope mean vs chamber after second correction",800,800);
	c_2->cd();
	c_2->SetGrid();
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


	c_2->SaveAs(result_path+"mean_slope_instlumi_with_chamber_2.pdf"); 

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
*/
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
/*	output_file->cd();
  c->Write();
  c_2->Write();
  c1->Write();
  c1_2->Write();
  //c2_1->Write();
//  c2_initial->Write(); 
	output_file->Close(); */
//}
