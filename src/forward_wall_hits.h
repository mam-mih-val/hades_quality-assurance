//
// Created by mikhail on 5/31/20.
//

#ifndef QUALITY_ASSURANCE_SRC_FORWARD_WALL_HITS_H_
#define QUALITY_ASSURANCE_SRC_FORWARD_WALL_HITS_H_
#include <Manager.h>

class ForwardWallHits {
public:
  static void Add(QA::Manager& qa_manager){
    Variable module_id( "FW channel", "forward_wall_hits", "module_id" );

    qa_manager.AddEntry({"Wall Hit Charge", "forward_wall_hits", "signal"},
                        {100, 0.0, 30});
    qa_manager.AddEntry2D({{"Wall Hit Charge", "forward_wall_hits", "signal"}, module_id },
                          {{100, 0.0, 30}, {304, 0.0, 304}});
    qa_manager.AddEntry2D({{"#beta", "forward_wall_hits", "beta"}, module_id },
                          {{120, 0.0, 1.2}, {304, 0.0, 304}});

    Cuts* inner_modules = new Cuts("inner modules", "forward_wall_hits");
    inner_modules->AddCut({"ring", 0.9, 5.1});

    Cuts* medium_modules = new Cuts("medium modules", "forward_wall_hits");
    medium_modules->AddCut({"ring", 5.9, 7.1});

    Cuts* perip_modules = new Cuts("peripheral modules", "forward_wall_hits");
    perip_modules->AddCut({"ring", 7.9, 10.1});

    qa_manager.AddEntry2D({{"module X, mm", "forward_wall_hits", "x"},
                           { "module Y, mm", "forward_wall_hits", "y" }},
                          {{100, -1000.0, 1000.0}, {100, -1000.0, 1000.0}});

    qa_manager.AddEntry2D({{"module X, mm", "forward_wall_hits", "x"},
                           { "module Y, mm", "forward_wall_hits", "y" }},
                          {{100, -1000.0, 1000.0}, {100, -1000.0, 1000.0}},
                          inner_modules);
    qa_manager.AddEntry2D({{"module X, mm", "forward_wall_hits", "x"},
                           { "module Y, mm", "forward_wall_hits", "y" }},
                          {{100, -1000.0, 1000.0}, {100, -1000.0, 1000.0}},
                          medium_modules);
    qa_manager.AddEntry2D({{"module X, mm", "forward_wall_hits", "x"},
                           { "module Y, mm", "forward_wall_hits", "y" }},
                          {{100, -1000.0, 1000.0}, {100, -1000.0, 1000.0}},
                          perip_modules);
  }
};

#endif // QUALITY_ASSURANCE_SRC_FORWARD_WALL_HITS_H_
