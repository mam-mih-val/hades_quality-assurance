//
// Created by mikhail on 5/27/20.
//

#include <Manager.h>
#include <chrono>
#include <iostream>

int main(int argv, char **argc){
  auto start = std::chrono::system_clock::now();
  if( argv < 2 ){
    std::cout << "Error: Incorrect number of arguments. Minimum 1 argument required." << std::endl;
    std::cout << "Example: ./run_qa path/to/input.root path/to/output.root" << std::endl;
    return 1;
  }
  std::string file_list;
  file_list = argc[1];
  std::string file_output{"output.root"};
  if( argv > 2 )
    file_output = argc[2];
  TFile* file = TFile::Open( file_list.data() );
  AnalysisTree::Configuration* config{nullptr};
  file->GetObject("Configuration", config);
  AnalysisTree::QA::Manager qa_manager(file_list, "hades_analysis_tree");
  return 0;
}
