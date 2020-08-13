//
// Created by mikhail on 5/27/20.
//

#include <chrono>
#include <iostream>

#include <Manager.hpp>
#include <Task.hpp>

#include "branches_qa.h"

#include <cuts.h>

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

  AnalysisTree::QA::Manager qa_manager({file_list}, {"hades_analysis_tree"});
  qa_manager.SetOutFileName(file_output);
  auto* qa_task = new AnalysisTree::QA::Task;

  qa_manager.SetEventCuts(HadesUtils::Cuts::Get(HadesUtils::Cuts::BRANCH_TYPE::EVENT_HEADER,
                                                HadesUtils::DATA_TYPE::AgAg_1_23AGeV));
  qa_manager.AddBranchCut(HadesUtils::Cuts::Get(HadesUtils::Cuts::BRANCH_TYPE::WALL_HITS,
                                                HadesUtils::DATA_TYPE::AgAg_1_23AGeV));
  qa_manager.AddBranchCut(HadesUtils::Cuts::Get(HadesUtils::Cuts::BRANCH_TYPE::MDC_TRACKS,
                                                HadesUtils::DATA_TYPE::AgAg_1_23AGeV));
  qa_manager.AddBranchCut(HadesUtils::Cuts::Get(HadesUtils::Cuts::BRANCH_TYPE::META_HITS,
                                                HadesUtils::DATA_TYPE::AgAg_1_23AGeV));

  AnalysisTree::AddEventHeaderQA(qa_task);
  AnalysisTree::AddMdcVtxTracksQA(qa_task);
  AnalysisTree::AddMetaHitsQA(qa_task);
  AnalysisTree::AddForwardWallHitsQA(qa_task);

  qa_manager.AddTask(qa_task);
  qa_manager.Init();
  qa_manager.Run(10000);
  qa_manager.Finish();
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::cout << "Elapsed time: " << elapsed_seconds.count() << " s" << std::endl;
  return 0;
}