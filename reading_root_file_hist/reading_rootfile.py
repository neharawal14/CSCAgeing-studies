import ROOT
from ROOT import TFile, TCanvas, gROOT
import os
import argparse
ROOT.gROOT.SetBatch(True)

def save_histograms_to_pdf(root_file_name,dir_name):
    # Open the ROOT file
    root_file = TFile.Open(root_file_name, "READ")
    
    if not root_file or root_file.IsZombie():
        print(f"Error opening ROOT file: {root_file_name}")
        return

    directory = root_file.Get("Test")

    # Create a canvas to draw histograms

    # Create a list to keep track of histograms and the first page of the PDF

    # Loop over all keys in the ROOT file
    for key in directory.GetListOfKeys():
        obj = key.ReadObj()
        print(" obj is ",obj.GetName())
        
        # Check if the object is a histogram
        if obj.InheritsFrom("TH1"):

          c = TCanvas("canvas", "canvas", 800, 600)
          c.cd()
          ROOT.gStyle.SetOptStat(111112211);
          obj.Draw()
          save_name = obj.GetName()
          if(obj.GetName()=="dxy(PV)"): 
            obj.GetXaxis().SetRangeUser(0,0.5)
          if(obj.GetName()=="dz(PV)") : 
            obj.GetXaxis().SetRangeUser(0,0.5)
          if(obj.GetName()=="muon isolation") : 
            obj.GetXaxis().SetRangeUser(0,0.5)

          print(" name ",save_name)
          c.SaveAs(dir_name+"/"+save_name+".pdf")

    root_file.Close()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Process some input parameters.")

    # Add arguments for root_file_name and dir_name
    parser.add_argument("file_name", type=str, help="Path to the ROOT file")
    parser.add_argument("input_dir_name", type=str, help="Directory name")

    # Parse the arguments
    args = parser.parse_args()
    root_file_name = args.file_name
    dir_name = args.input_dir_name
    # Example usage
    save_histograms_to_pdf(root_file_name,  dir_name)
