//
// Created by mikhail on 5/27/20.
//

#include <Manager.h>
#include <chrono>
#include <iostream>

#include "event_info.h"
#include "forward_wall_hits.h"
#include "mdc_vertex_tracks.h"
#include "meta_hits.h"
#include "sim_data.h"

int main(int argv, char **argc){
  auto start = std::chrono::system_clock::now();
  if( argv < 2 ){
    std::cout << "Error: Incorrect number of arguments. Minimum 1 argument required." << std::endl;
    std::cout << "Example: ./run_qa path/to/input.root path/to/output.root" << std::endl;
    return 1;
  }
  std::string file_list{argc[argv-1]};
  std::string flag{argc[1]};
  std::string file_output{"output.root"};
  if( argv > 2 )
    file_output = argc[2];
  TFile* file = TFile::Open( "~/a_tree_mc.root" );
  AnalysisTree::Configuration* config{nullptr};
  file->GetObject("Configuration", config);
  config->Print();
  AnalysisTree::QA::Manager qa_manager(file_list, "hades_analysis_tree");
  MdcVertexTracks::Add(qa_manager);
  MetaHits::Add(qa_manager);
  ForwardWallHits::Add(qa_manager);
  EventInfo::Add(qa_manager);
  if( flag == "--mc" )
    SimData::Add(qa_manager);
  qa_manager.Run();
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::cout << "Elapsed time: " << elapsed_seconds.count() << " s" << std::endl;
  return 0;
}