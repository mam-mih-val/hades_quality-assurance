//
// Created by mikhail on 5/31/20.
//

#ifndef QUALITY_ASSURANCE_SRC_FORWARD_WALL_HITS_H_
#define QUALITY_ASSURANCE_SRC_FORWARD_WALL_HITS_H_
#include <Manager.h>
namespace AnalysisTree {
class ForwardWallHits {
public:
  static void Add(QA::Task* qa_manager) {
    Variable module_id("FW channel", "forward_wall_hits", "module_id");

    qa_manager->AddEntry({"Wall Hit Charge", "forward_wall_hits", "signal"},
                        {100, 0.0, 1000});
    qa_manager->AddEntry2D(
        {{"Wall Hit Charge", "forward_wall_hits", "signal"}, module_id},
        {{100, 0.0, 1000}, {304, 0.0, 304}});
    qa_manager->AddEntry2D({{"#beta", "forward_wall_hits", "beta"}, module_id},
                          {{120, 0.0, 1.2}, {304, 0.0, 304}});

    Cuts *inner_modules = new Cuts("inner modules");
    inner_modules->AddCut({{"forward_wall_hits","ring"}, 0.9, 5.1});

    Cuts *medium_modules = new Cuts("medium modules");
    medium_modules->AddCut({{"forward_wall_hits","ring"}, 5.9, 7.1});

    Cuts *perip_modules = new Cuts("peripheral modules");
    perip_modules->AddCut({{"forward_wall_hits","ring"}, 7.9, 10.1});

    qa_manager->AddEntry2D({{"module X, mm", "forward_wall_hits", "x"},
                           {"module Y, mm", "forward_wall_hits", "y"}},
                          {{100, -1000.0, 1000.0}, {100, -1000.0, 1000.0}});

    qa_manager->AddEntry2D({{"module X, mm", "forward_wall_hits", "x"},
                           {"module Y, mm", "forward_wall_hits", "y"}},
                          {{100, -1000.0, 1000.0}, {100, -1000.0, 1000.0}},
                          inner_modules);
    qa_manager->AddEntry2D({{"module X, mm", "forward_wall_hits", "x"},
                           {"module Y, mm", "forward_wall_hits", "y"}},
                          {{100, -1000.0, 1000.0}, {100, -1000.0, 1000.0}},
                          medium_modules);
    qa_manager->AddEntry2D({{"module X, mm", "forward_wall_hits", "x"},
                           {"module Y, mm", "forward_wall_hits", "y"}},
                          {{100, -1000.0, 1000.0}, {100, -1000.0, 1000.0}},
                          perip_modules);
  }
};
} // namespace AnalysisTree
#endif // QUALITY_ASSURANCE_SRC_FORWARD_WALL_HITS_H_
