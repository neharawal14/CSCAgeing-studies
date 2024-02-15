void tmp(){
	TFile *f = TFile::Open("old_file_ME11.root");
		TTree *tree_new = (TTree*) f->Get("tree_new");
	  Int_t _rhid;
		Double_t _rhsumQ_RAW;
	  tree_new->SetBranchAddress("_rhid",&_rhid);
	  tree_new->SetBranchAddress("_rhsumQ_RAW",&_rhsumQ_RAW);
		int sum_plus=0, sum_minus=0, sum_not =0;
	for(int i=0 ;i<tree_new->GetEntries(); i++){
  tree_new->GetEntry(i);
	if(_rhid>2000000) sum_minus +=1;
	else if(_rhid<2000000) sum_plus +=1;
	else { sum_not+=1;}
	
	}
	std::cout<<" plus "<<sum_plus<<std::endl;
	std::cout<<" minus "<<sum_minus<<std::endl;
	std::cout<<" not "<<sum_not<<std::endl;
}
