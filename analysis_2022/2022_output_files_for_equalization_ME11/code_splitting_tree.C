#include <TFile.h>
#include <TTree.h>

void splitTree(TTree* originalTree, const char* branchName, const char* outputFileName) {
    TFile* outputFile = new TFile(outputFileName, "RECREATE");

    // Create separate trees for different values
    TTree* tree1 = originalTree->CloneTree(0);
    TTree* tree2 = originalTree->CloneTree(0);

    // Variables to hold the element value
    Int_t value;

    // Set branch addresses
    originalTree->SetBranchAddress(branchName, &value);
    tree1->SetBranchAddress(branchName, &value);
    tree2->SetBranchAddress(branchName, &value);

    // Loop over the entries in the original tree
    Long64_t nEntries = originalTree->GetEntries();
    for (Long64_t i = 0; i < nEntries; ++i) {
        originalTree->GetEntry(i);

        // Fill entries into appropriate trees based on the value of the element
        if (value >2000000) {
            tree1->Fill();
        } else {
            tree2->Fill();
        }
    }

    // Write and close the output file
    outputFile->Write();
    outputFile->Close();
    delete outputFile;
}

void code_splitting_tree() {
    // Assuming you have an existing TTree named 'originalTree' with the desired elements

    const char* branchName = "_rhid"; // Name of the branch to check
    const char* outputFileName1 = "minus_endcap.root"; // Output file for tree1
    const char* outputFileName2 = "plus_endcap.root"; // Output file for tree2
TFile *f = TFile::Open("old_file_ME11.root");
TTree *originalTree = (TTree*) f->Get("tree_new");
    splitTree(originalTree, branchName, outputFileName1);
    splitTree(originalTree, branchName, outputFileName2);
}

