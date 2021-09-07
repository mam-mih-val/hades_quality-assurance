//
// Created by mikhail on 5/27/20.
//

#include <iostream>

#include <boost/program_options.hpp>

#include <AnalysisTree/DataHeader.hpp>
#include <cuts.h>

#include "branches_qa.h"

int main(int argv, char **argc){
  namespace po = boost::program_options;
  if( argv < 2 ){
    throw std::runtime_error( "No arguments are specified. Try ./run_qa --help for more information" );
  }
  std::string input_list;
  std::string tree_name{"hades_analysis_tree"};
  std::string output_file{"output.root"};
  int n_events{-1};
  po::options_description options("Options");
  options.add_options()
      ("help,h", "Help screen")
      ("MC,m", "MC data sample")
      ("reco-fw", "Reconstructed FW-hits QA")
      ("cuts", "Apply cuts on data")
      ("input,i", po::value<std::string>(&input_list),
       "Input file list")
      ("tree-name", po::value<std::string>(&tree_name),
       "Input file list")
      ("output,o", po::value<std::string>(&output_file),
       "Name of output file")
      ("events,N", po::value<int>(&n_events),
       "Number of analysing events");
  po::variables_map vm;
  po::parsed_options parsed = po::command_line_parser(argv, argc).options(options).run();
  po::store(parsed, vm);
  po::notify(vm);
  if (vm.count("help")){
    std::cout << options << std::endl;
    return 0;
  }
  bool is_mc=vm.count("MC");
  bool is_reco_fw=vm.count("reco-fw");
  bool is_cuts=vm.count("cuts");

  if( std::empty(input_list) )
    throw std::runtime_error( "Input file is not specified. Try ./run_qa --help for more information" );
  const double beam_y = AnalysisTree::GetObjectFromFileList<AnalysisTree::DataHeader>(
      input_list, "DataHeader")->GetBeamRapidity();
  AnalysisTree::QA::Manager qa_manager({input_list}, {tree_name});
  qa_manager.SetOutFileName(output_file);
  auto* qa_task = new AnalysisTree::QA::Task;
  auto event_cuts = new AnalysisTree::Cuts("evt_cuts", {
                                                           AnalysisTree::SimpleCut( {"event_header", "vtx_x"}, -3.0, 3.0 ),
                                                           AnalysisTree::SimpleCut( {"event_header", "vtx_y"}, -3.0, 3.0 ),
                                                           AnalysisTree::SimpleCut( {"event_header", "vtx_z"}, -70.0, 0.0 ),
                                                           AnalysisTree::SimpleCut( {"event_header", "vtx_chi2"}, 0.5, 40.0 ),
                                                           AnalysisTree::SimpleCut( {"event_header", "good_vertex_cluster"}, 0.5, 1.5 ),
                                                           AnalysisTree::SimpleCut( {"event_header", "good_vertex_candidate"}, 0.5, 1.5 ),
                                                           AnalysisTree::SimpleCut( {"event_header", "good_start"}, 0.5, 1.5 ),
                                                           AnalysisTree::SimpleCut( {"event_header", "no_pile_up_start"}, 0.5, 1.5 ),
                                                           AnalysisTree::SimpleCut( {"event_header", "no_veto"}, 0.5, 1.5 ),
                                                           AnalysisTree::SimpleCut( {"event_header", "good_start_veto"}, 0.5, 1.5 ),
                                                           AnalysisTree::SimpleCut( {"event_header", "good_start_meta"}, 0.5, 1.5 ),
                                                           AnalysisTree::SimpleCut( {"event_header", "selected_tof_rpc_hits_centrality"}, 0.0, 45.0 ),
                                                       });
  if( is_cuts && !is_reco_fw ) {
    qa_manager.AddBranchCut(
        HadesUtils::Cuts::Get(HadesUtils::Cuts::BRANCH_TYPE::WALL_HITS,
                              HadesUtils::DATA_TYPE::AuAu_1_23AGeV));
//    qa_manager.AddBranchCut(
//        HadesUtils::Cuts::Get(HadesUtils::Cuts::BRANCH_TYPE::MDC_TRACKS,
//                              HadesUtils::DATA_TYPE::AuAu_1_23AGeV));
//    qa_manager.AddBranchCut(
//        HadesUtils::Cuts::Get(HadesUtils::Cuts::BRANCH_TYPE::META_HITS,
//                              HadesUtils::DATA_TYPE::AuAu_1_23AGeV));
    qa_manager.SetEventCuts(event_cuts);
  }
  if( !is_reco_fw ) {
    AnalysisTree::AddEventHeaderQA(qa_task, is_mc);
    AnalysisTree::AddMdcVtxTracksQA(qa_task, beam_y);
    AnalysisTree::AddMetaHitsQA(qa_task);
    AnalysisTree::AddParticleQA(qa_task, 2212, beam_y);
    AnalysisTree::AddParticleQA(qa_task, 211, beam_y);
    AnalysisTree::AddParticleQA(qa_task, -211, beam_y);
    AnalysisTree::AddParticleQA(qa_task, 321, beam_y);
    AnalysisTree::AddParticleQA(qa_task, -321, beam_y);
    AnalysisTree::AddParticleQA(qa_task, 11, beam_y);
    AnalysisTree::AddParticleQA(qa_task, -11, beam_y);
//    AnalysisTree::AddParticleQA(qa_task, 45, beam_y);
//    AnalysisTree::AddParticleQA(qa_task, 46, beam_y);
    AnalysisTree::AddForwardWallHitsQA(qa_task);
  }
  if( is_reco_fw ) {
    auto branch="reconstructed_forward_wall_hits";
    AnalysisTree::SimpleCut beta_cut({branch, "beta"}, 0, 1.0);
    AnalysisTree::SimpleCut ring_by_ring_cuts({{branch, "ring"}, {branch, "signal"}},
                                              [](std::vector<double> vars) {
                                                if (1.0 <= vars.at(0) && vars.at(0) <= 5)
                                                  return vars.at(1) > 80.0;
                                                if (vars.at(0) >= 6.0 && vars.at(0) <= 7.0)
                                                  return vars.at(1) > 85.0;
                                                if (8.0 <= vars.at(0) && vars.at(0) <= 10.0)
                                                  return vars.at(1) > 88.0;
                                                return false;
                                              });
    auto *wall_cuts = new AnalysisTree::Cuts("good_fw_hits", {ring_by_ring_cuts});
    if( is_cuts )
      qa_manager.AddBranchCut(wall_cuts);
    AnalysisTree::AddReconstructedForwardWallHitsQA(qa_task);
  }
  if( is_mc ) {
    AnalysisTree::AddSimDataQA(qa_task, beam_y);
    AnalysisTree::AddSimParticlesQA(qa_task, 2212, beam_y);
    AnalysisTree::AddSimParticlesQA(qa_task, 211, beam_y);
    AnalysisTree::AddSimParticlesQA(qa_task, -211, beam_y);
//    AnalysisTree::AddSimParticlesQA(qa_task, 45, beam_y);
//    AnalysisTree::AddSimParticlesQA(qa_task, 46, beam_y);
    AnalysisTree::AddSimParticlesQA(qa_task, 321, beam_y);
    AnalysisTree::AddSimParticlesQA(qa_task, -321, beam_y);
  }
  qa_manager.AddTask(qa_task);
  qa_manager.Init();
  qa_manager.Run(n_events);
  qa_manager.Finish();
  return 0;
}