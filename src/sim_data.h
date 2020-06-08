//
// Created by mikhail on 6/8/20.
//

#ifndef QUALITY_ASSURANCE_SRC_SIM_DATA_H_
#define QUALITY_ASSURANCE_SRC_SIM_DATA_H_
#include <Manager.h>

class SimData {
public:
  static void Add(QA::Manager& qa_manager){
    qa_manager.AddEntry({"b, fm", "sim_header", "impact_parameter"},
                        {110, 0.0, 11.0});
    qa_manager.AddEntry({"#Psi_{RP}, rad", "sim_header", "reaction_plane"},
                        {100, 0.0, 6.29});
  }
};

#endif // QUALITY_ASSURANCE_SRC_SIM_DATA_H_
