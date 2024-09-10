#include <iostream>
#include <vector>
#include <string>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TLegend.h>

// Function to extract the HV segment from the filename
std::string extractHVSegment(TString filename) {
      int start = filename.Index("ME");
    if (start != kNPOS) {
        return filename(start, 7);  // "ME31HV3" or similar
    }
    return ""; 
}

// Function to get the total number of entries in a ROOT file
int getTotalEntries(TString filename) {
    TString full_path = "../output_root_files/"+ filename;
    //TFile* file = TFile::Open(filename.c_str(), "READ");
    TFile* file = TFile::Open(full_path, "READ");
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return -1;
    }

    TTree* tree = nullptr;
    file->GetObject("tree", tree);
    if (!tree) {
        std::cerr << "Error: 'tree' not found in file: " << filename << std::endl;
        file->Close();
        return -1;
    }

    int entries = tree->GetEntries();
    file->Close();
    return entries;
}

void number_of_hits() {
    // Define your file names and collect data
    std::vector<TString> single_layer_files = {
        "csc_output_40_single_layer_better_selectionsME11a_tree.root",
        "csc_output_40_single_layer_better_selectionsME11b_tree.root",
        "csc_output_40_single_layer_better_selectionsME12HV1_tree.root",
        "csc_output_40_single_layer_better_selectionsME12HV2_tree.root",
        "csc_output_40_single_layer_better_selectionsME12HV3_tree.root",
        "csc_output_40_single_layer_better_selectionsME13HV1_tree.root",
        "csc_output_40_single_layer_better_selectionsME13HV2_tree.root",
        "csc_output_40_single_layer_better_selectionsME13HV3_tree.root",
        "csc_output_40_single_layer_better_selectionsME21HV1_tree.root",
        "csc_output_40_single_layer_better_selectionsME21HV2_tree.root",
        "csc_output_40_single_layer_better_selectionsME21HV3_tree.root",
        "csc_output_40_single_layer_better_selectionsME22HV1_tree.root",
        "csc_output_40_single_layer_better_selectionsME22HV2_tree.root",
        "csc_output_40_single_layer_better_selectionsME22HV3_tree.root",
        "csc_output_40_single_layer_better_selectionsME22HV4_tree.root",
        "csc_output_40_single_layer_better_selectionsME22HV5_tree.root",
        "csc_output_40_single_layer_better_selectionsME31HV1_tree.root",
        "csc_output_40_single_layer_better_selectionsME31HV2_tree.root",
        "csc_output_40_single_layer_better_selectionsME31HV3_tree.root",
        "csc_output_40_single_layer_better_selectionsME32HV1_tree.root",
        "csc_output_40_single_layer_better_selectionsME32HV2_tree.root",
        "csc_output_40_single_layer_better_selectionsME32HV3_tree.root",
        "csc_output_40_single_layer_better_selectionsME32HV4_tree.root",
        "csc_output_40_single_layer_better_selectionsME32HV5_tree.root",
        "csc_output_40_single_layer_better_selectionsME41HV1_tree.root",
        "csc_output_40_single_layer_better_selectionsME41HV2_tree.root",
        "csc_output_40_single_layer_better_selectionsME41HV3_tree.root",
        "csc_output_40_single_layer_better_selectionsME42HV1_tree.root",
        "csc_output_40_single_layer_better_selectionsME42HV1_tree.root",
        "csc_output_40_single_layer_better_selectionsME42HV2_tree.root",
        "csc_output_40_single_layer_better_selectionsME42HV3_tree.root",
        "csc_output_40_single_layer_better_selectionsME42HV4_tree.root",
        "csc_output_40_single_layer_better_selectionsME42HV5_tree.root",
        // Add all other single layer filenames
    };

    std::vector<TString> all_layer_files = {
        "csc_output_40_all_layer_better_selectionsME11a_tree.root",
        "csc_output_40_all_layer_better_selectionsME11b_tree.root",
        "csc_output_40_all_layer_better_selectionsME12HV1_tree.root",
        "csc_output_40_all_layer_better_selectionsME12HV2_tree.root",
        "csc_output_40_all_layer_better_selectionsME12HV3_tree.root",
        "csc_output_40_all_layer_better_selectionsME13HV1_tree.root",
        "csc_output_40_all_layer_better_selectionsME13HV2_tree.root",
        "csc_output_40_all_layer_better_selectionsME13HV3_tree.root",
        "csc_output_40_all_layer_better_selectionsME21HV1_tree.root",
        "csc_output_40_all_layer_better_selectionsME21HV2_tree.root",
        "csc_output_40_all_layer_better_selectionsME21HV3_tree.root",
        "csc_output_40_all_layer_better_selectionsME22HV1_tree.root",
        "csc_output_40_all_layer_better_selectionsME22HV2_tree.root",
        "csc_output_40_all_layer_better_selectionsME22HV3_tree.root",
        "csc_output_40_all_layer_better_selectionsME22HV4_tree.root",
        "csc_output_40_all_layer_better_selectionsME22HV5_tree.root",
        "csc_output_40_all_layer_better_selectionsME31HV1_tree.root",
        "csc_output_40_all_layer_better_selectionsME31HV2_tree.root",
        "csc_output_40_all_layer_better_selectionsME31HV3_tree.root",
        "csc_output_40_all_layer_better_selectionsME32HV1_tree.root",
        "csc_output_40_all_layer_better_selectionsME32HV2_tree.root",
        "csc_output_40_all_layer_better_selectionsME32HV3_tree.root",
        "csc_output_40_all_layer_better_selectionsME32HV4_tree.root",
        "csc_output_40_all_layer_better_selectionsME32HV5_tree.root",
        "csc_output_40_all_layer_better_selectionsME41HV1_tree.root",
        "csc_output_40_all_layer_better_selectionsME41HV2_tree.root",
        "csc_output_40_all_layer_better_selectionsME41HV3_tree.root",
        "csc_output_40_all_layer_better_selectionsME42HV1_tree.root",
        "csc_output_40_all_layer_better_selectionsME42HV1_tree.root",
        "csc_output_40_all_layer_better_selectionsME42HV2_tree.root",
        "csc_output_40_all_layer_better_selectionsME42HV3_tree.root",
        "csc_output_40_all_layer_better_selectionsME42HV4_tree.root",
        "csc_output_40_all_layer_better_selectionsME42HV5_tree.root",
        // Add all other all layer filenames
    };

    std::vector<int> single_layer_entries;
    std::vector<int> all_layer_entries;
    std::vector<std::string> hv_segments;

    // Get total number of entries for each file
    for (size_t i = 0; i < single_layer_files.size(); ++i) {
        int single_entries = getTotalEntries(single_layer_files[i]);
        int all_entries = getTotalEntries(all_layer_files[i]);

        if (single_entries != -1 && all_entries != -1) {
            single_layer_entries.push_back(single_entries);
            all_layer_entries.push_back(all_entries);
            hv_segments.push_back(extractHVSegment(single_layer_files[i]));
        }
    }

    // Create histograms for the overview plots
    int num_segments = single_layer_entries.size();
    TH1F* h_single = new TH1F("h_single", "Total Entries in Single Layer Files", num_segments, 0, num_segments);
    TH1F* h_all = new TH1F("h_all", "Total Entries in All Layer Files", num_segments, 0, num_segments);
    TH1F* h_diff = new TH1F("h_diff", "Difference in Entries Between Single and All Layer Files", num_segments, 0, num_segments);

    // Fill histograms
    for (int i = 0; i < num_segments; ++i) {
        h_single->SetBinContent(i + 1, single_layer_entries[i]);
        h_all->SetBinContent(i + 1, all_layer_entries[i]);
        std::cout<<" single layer "<<single_layer_entries[i]<<std::endl;
        std::cout<<" all layers "<<all_layer_entries[i]<<std::endl;
        float per_diff = (( static_cast<float>(all_layer_entries[i] - single_layer_entries[i])/ all_layer_entries[i]) * 100);
        std::cout<<" diff in per "<<per_diff<<std::endl;
        h_diff->SetBinContent(i + 1, per_diff);

        h_single->GetXaxis()->SetBinLabel(i + 1, hv_segments[i].c_str());
        h_all->GetXaxis()->SetBinLabel(i + 1, hv_segments[i].c_str());
        h_diff->GetXaxis()->SetBinLabel(i + 1, hv_segments[i].c_str());
    }

    // Draw and save the plots
    TCanvas* c1 = new TCanvas("c1", "Total Entries", 800, 600);
    c1->cd();
    h_single->SetFillColor(kBlue);
//    h_single->Draw("hbar1");
        h_single->Draw("hbar1 text");

    // Adjust the histogram for better display of the text
    h_single->SetBarWidth(0.5);
    h_single->SetBarOffset(0.2);
    h_single->SetStats(0);
    c1->SaveAs("no_iso_selections_single_layer_plots.pdf");

    TCanvas* c2 = new TCanvas("c2", "Total Entries", 800, 600);
    c2->cd(2);
    h_all->SetFillColor(kGreen);
    h_all->SetBarWidth(0.5);
    h_all->SetBarOffset(0.2);
    h_all->SetStats(0);

    h_all->Draw("hbar1 text");
    c2->SaveAs("no_iso_selections_all_layers_plots.pdf");

    TCanvas* c3 = new TCanvas("c3", "Total Entries", 800, 600);
    c3->cd(3);
    h_diff->SetFillColor(kRed);
    h_diff->SetBarWidth(0.5);
    h_diff->SetBarOffset(0.2);
    h_diff->SetStats(0);

    h_diff->Draw("hbar1 text");

    c3->SaveAs("no_iso_selections_overview_plots.pdf");

}

