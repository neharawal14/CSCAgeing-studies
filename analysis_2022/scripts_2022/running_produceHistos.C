////#include "/home/neha.rawal/uf_home/CSCAgeingP5/CMSSW_8_0_27/src/CSCAgeingP5/Src/ProduceHistosPerChannel.h"
////#include "/home/neha.rawal/uf_home/CSCAgeingP5/CMSSW_8_0_27/src/CSCAgeingP5/Src/ProduceHistosPerChannel.C"
//void macro_running(TString input_file, TString input_chamber){
// //gSystem->AddIncludePath(" -I /home/neha.rawal/uf_home/CSCAgeingP5/CMSSW_8_0_27/src/CSCAgeingP5/Src/ProduceHistosPerChannel.h");
// //gSystem->Load("/home/neha.rawal/uf_home/CSCAgeingP5/CMSSW_8_0_27/src/CSCAgeingP5/Src/ProduceHistosPerChannel_C.so");	
// //gROOT->LoadMacro("/home/neha.rawal/uf_home/CSCAgeingP5/CMSSW_8_0_27/src/CSCAgeingP5/Src/ProduceHistosPerChannel.C++");
// gROOT->ProcessLine(".L /home/neha.rawal/uf_home/CSCAgeingP5/CMSSW_8_0_27/src/CSCAgeingP5/Src/ProduceHistosPerChannel.C++");
//// gROOT->LoadClass("/home/neha.rawal/uf_home/CSCAgeingP5/CMSSW_8_0_27/src/CSCAgeingP5/Src/ProduceHistosPerChannel");
// gROOT->LoadClass("ProduceHistosPerChannel");
//// gSystem->AddIncludePath(" -I /home/neha.rawal/uf_home/CSCAgeingP5/CMSSW_8_0_27/src/CSCAgeingP5/Src/ProduceHistosPerChannel.h");
// //gSystem->AddIncludePath(" -I /home/neha.rawal/uf_home/CSCAgeingP5/CMSSW_8_0_27/src/CSCAgeingP5/Src/ProduceHistosPerChannel.C");
// //gSystem->Load("/home/neha.rawal/uf_home/CSCAgeingP5/CMSSW_8_0_27/src/CSCAgeingP5/Src/ProduceHistosPerChannel_C.so");	
//ProduceHistosPerChannel d;
////d.Loop("DUMMYFILENAME_2017_new_all_ME13HV2_tree","ME13HV2");
//std::cout<<"input file running d.("<<input_file<<","<<input_chamber<<")"<<std::endl;
//}

#include "/blue/avery/neha.rawal/CSCAgeing_2022_study/CMSSW_12_4_6/src/Src/ProduceHistosPerChannel.C+"
void running_produceHistos(TString input_file_path,TString input_file_name,TString input_chamber, TString output_file_path, TString output_path_folder){
ProduceHistosPerChannel m;
m.Loop(input_file_path,input_file_name,  input_chamber, output_file_path, output_path_folder);
//m.plot_gain_time();
//gROOT->ProcessLine(macro m);
//gROOT->ProcessLine(m.print());
}


