//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jun 30 10:27:38 2023 by ROOT version 6.24/07
// from TTree tree_new/tree
// found on file: tmp.root
//////////////////////////////////////////////////////////

#ifndef equalizing_gas_gain_plus_minus_h
#define equalizing_gas_gain_plus_minus_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class equalizing_gas_gain_plus_minus {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   ULong64_t       new_eventNb;
   ULong64_t       new_runNb;
   ULong64_t       new_lumiBlock;
   Int_t           new_rhid;
   Int_t           new_stationring;
   Double_t        new_rhsumQ;
   Double_t        new_rhsumQ_RAW;
   Double_t        new_pressure;
   Double_t        new_temperature;
   Double_t        new_instlumi;
   Double_t        new_integratelumi;
   UInt_t          new_timesecond;
   Int_t           new_n_PV;
   Int_t           new_bunchcrossing;

   // List of branches
   TBranch        *b_new_eventNb;   //!
   TBranch        *b_new_runNb;   //!
   TBranch        *b_new_lumiBlock;   //!
   TBranch        *b_new_rhid;   //!
   TBranch        *b_new_stationring;   //!
   TBranch        *b_new_rhsumQ;   //!
   TBranch        *b_new_rhsumQ_RAW;   //!
   TBranch        *b_new_pressure;   //!
   TBranch        *b_new_temperature;   //!
   TBranch        *b_new_instlumi;   //!
   TBranch        *b_new_integratelumi;   //!
   TBranch        *b_new_timesecond;   //!
   TBranch        *b_new_n_PV;   //!
   TBranch        *b_new_bunchcrossing;   //!

   equalizing_gas_gain_plus_minus(TTree *tree=0);
   virtual ~equalizing_gas_gain_plus_minus();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
	 std::vector<float>  trimmed_mean(TH2D*);

	  TString output_plots_folder = "/cmsuf/data/store/user/t2/users/neha.rawal/CSCAgeing_2022/analysis_2022/2022_output_files_for_equalization_ME11/old_final_results_ME11_plus/";   
		TString chamber_string_name = "ME11";
		TString gas_gain_plots  = output_plots_folder+"charge_plots_outliers/";
		TString gas_gain_plots_all  = output_plots_folder+"charge_plots_all/";
		float trimmean = 0.7;
    bool analyzing_plus =true;   
     bool analyzing_minus =false; 
 		 float trimmed_mean_special(TH1D *myh,int chambernb,int endcap,int layer);
};

#endif

#ifdef equalizing_gas_gain_plus_minus_cxx
equalizing_gas_gain_plus_minus::equalizing_gas_gain_plus_minus(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
}

equalizing_gas_gain_plus_minus::~equalizing_gas_gain_plus_minus()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t equalizing_gas_gain_plus_minus::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t equalizing_gas_gain_plus_minus::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void equalizing_gas_gain_plus_minus::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
//   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("new_eventNb", &new_eventNb, &b_new_eventNb);
   fChain->SetBranchAddress("new_runNb", &new_runNb, &b_new_runNb);
   fChain->SetBranchAddress("new_lumiBlock", &new_lumiBlock, &b_new_lumiBlock);
   fChain->SetBranchAddress("new_rhid", &new_rhid, &b_new_rhid);
   fChain->SetBranchAddress("new_stationring", &new_stationring, &b_new_stationring);
   fChain->SetBranchAddress("new_rhsumQ", &new_rhsumQ, &b_new_rhsumQ);
   fChain->SetBranchAddress("new_rhsumQ_RAW", &new_rhsumQ_RAW, &b_new_rhsumQ_RAW);
   fChain->SetBranchAddress("new_pressure", &new_pressure, &b_new_pressure);
   fChain->SetBranchAddress("new_temperature", &new_temperature, &b_new_temperature);
   fChain->SetBranchAddress("new_instlumi", &new_instlumi, &b_new_instlumi);
   fChain->SetBranchAddress("new_integratelumi", &new_integratelumi, &b_new_integratelumi);
   fChain->SetBranchAddress("new_timesecond", &new_timesecond, &b_new_timesecond);
   fChain->SetBranchAddress("new_n_PV", &new_n_PV, &b_new_n_PV);
   fChain->SetBranchAddress("new_bunchcrossing", &new_bunchcrossing, &b_new_bunchcrossing);
   Notify();
}

Bool_t equalizing_gas_gain_plus_minus::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void equalizing_gas_gain_plus_minus::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t equalizing_gas_gain_plus_minus::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef equalizing_gas_gain_plus_minus_cxx
