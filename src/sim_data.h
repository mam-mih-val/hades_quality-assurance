//
// Created by mikhail on 6/8/20.
//

#ifndef QUALITY_ASSURANCE_SRC_SIM_DATA_H_
#define QUALITY_ASSURANCE_SRC_SIM_DATA_H_
#include <Manager.h>

namespace AnalysisTree {
class SimData {
public:
  static void Add(QA::Manager &qa_manager) {
    qa_manager.AddEntry({"b, fm", "sim_header", "impact_parameter"},
                        {110, 0.0, 11.0});
    qa_manager.AddEntry({"#Psi_{RP}, rad", "sim_header", "reaction_plane"},
                        {100, 0.0, 6.29});
    qa_manager.AddEntry({"mass, [#frac{GeV}{c}]", "sim_tracks", "mass"},
                        {500, 0.0, 10.0});
    
    Cuts *protons = new Cuts("protons", "sim_tracks");
    protons->AddCut({"geant_pid", 14. - 0.5, 14. + 0.5});
    protons->AddCut({"is_primary", 0. - 0.5, 0. + 0.5});

    Cuts *pions_plus = new Cuts("pions_plus", "sim_tracks");
    pions_plus->AddCut({"geant_pid", 8. - 0.5, 8. + 0.5});

    Cuts *pions_minus = new Cuts("pions_minus", "sim_tracks");
    pions_minus->AddCut({"geant_pid", 9. - 0.5, 9. + 0.5});

    Cuts *kaons_plus = new Cuts("kaons_plus", "sim_tracks");
    kaons_plus->AddCut({"geant_pid", 11. - 0.5, 11. + 0.5});

    Cuts *kaons_minus = new Cuts("kaons_minus", "sim_tracks");
    kaons_minus->AddCut({"geant_pid", 12. - 0.5, 12. + 0.5});
    Variable y_cm("y_{cm}", "sim_tracks", {"rapidity"},
                  [](const std::vector<double> &vars){
                    return vars.at(0)-0.74;
                  });
    
    qa_manager.AddEntry2D({{"pt_{p}, #frac{GeV}{c}", "sim_tracks", "pT"}, y_cm},
                          {{200, 0.0, 2.0}, {200, -1.0, 1.0}}, protons);
    qa_manager.AddEntry2D({{"pt_{#pi+}, #frac{GeV}{c}", "sim_tracks", "pT"},
                           {"y_{#pi+}", "sim_tracks", "rapidity"}},
                          {{250, 0.0, 2.5}, {200, 0.0, 2.0}}, pions_plus);
    qa_manager.AddEntry2D({{"pt_{#pi-}, #frac{GeV}{c}", "sim_tracks", "pT"},
                           {"y_{#pi-}", "sim_tracks", "rapidity"}},
                          {{250, 0.0, 2.5}, {200, 0.0, 2.0}}, pions_minus);

  }
};
} // namespace AnalysisTree
#endif // QUALITY_ASSURANCE_SRC_SIM_DATA_H_
