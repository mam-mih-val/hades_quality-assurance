//
// Created by mikhail on 5/28/20.
//

#ifndef QUALITY_ASSURANCE_SRC_CMAKE_BUILD_DEBUG_MDC_VERTEX_TRACKS_H_
#define QUALITY_ASSURANCE_SRC_CMAKE_BUILD_DEBUG_MDC_VERTEX_TRACKS_H_
#include <AnalysisTree/Cuts.hpp>
#include <Manager.h>

namespace AnalysisTree {
class MdcVertexTracks {
public:
  MdcVertexTracks() = delete;
  static void Add(QA::Task* qa_manager) {
    qa_manager->AddEntry({"Vertex tracks p_{T}, #frac{GeV}{c}", "mdc_vtx_tracks", "pT"},
                        {250, 0.0, 2.5});
    qa_manager->AddEntry({"#chi^{2}_{RK}", "mdc_vtx_tracks", "chi2"},
                        {100, 0.0, 250});
    qa_manager->AddEntry({"DCA_{XY}", "mdc_vtx_tracks", "dca_xy"},
                        {500, -15.0, 15});
    qa_manager->AddEntry({"DCA_{Z}", "mdc_vtx_tracks", "dca_z"},
                        {500, -20., 20});
    qa_manager->AddEntry({"phi, [rad]", "mdc_vtx_tracks", "phi"},
                        {200, -4., 4});
    qa_manager->AddEntry({"geant pid", "mdc_vtx_tracks", "geant_pid"},
                        {50, 0.0, 50});

    Cuts *protons = new Cuts("protons");
    protons->AddCut({{"mdc_vtx_tracks", "geant_pid"}, 14. - 0.5, 14. + 0.5});
    protons->AddCut({{"mdc_vtx_tracks", "dca_xy"}, 0.0, 3.0});
    protons->AddCut({{"mdc_vtx_tracks", "dca_z"}, -3.0, 3.0});

    qa_manager->AddEntry({"geant pid", "mdc_vtx_tracks", "geant_pid"},
                         {50, 0.0, 50}, protons);
    Variable charge_p(
        "p #times z, [z #times #frac{GeV}{c}]", {
                                                    {"mdc_vtx_tracks", "charge"},
                                                    {"mdc_vtx_tracks","p" }},
        [](std::vector<double> &var) { return var.at(0) * var.at(1); });

    Variable y_cm("y-y_{beam}", {{"mdc_vtx_tracks", "rapidity"}},
                  [](const std::vector<double> &vars){
                    return vars.at(0)-0.74;
                  });

    qa_manager->AddEntry2D({y_cm, {"pt, #frac{GeV}{c}", "mdc_vtx_tracks", "pT"}},
                           {{50, -1.0, 1.0}, {50, 0.0, 2.0}});

    qa_manager->AddEntry2D({y_cm, {"pt, #frac{GeV}{c}", "mdc_vtx_tracks", "pT"}},
                           {{50, -1.0, 1.0}, {50, 0.0, 2.0}}, protons);

    qa_manager->AddEntry2D({charge_p, {"#frac{dE}{dx} MDC", "mdc_vtx_tracks", "dEdx"}},
                          {{200, -2.0, 5.0}, {200, 0.0, 20.0}});
    qa_manager->AddEntry2D({charge_p, {"#frac{dE}{dx} MDC", "mdc_vtx_tracks", "dEdx"}},
                          {{200, -2.0, 5.0}, {200, 0.0, 20.0}}, protons);
    Variable theta( "#theta, [rad]", {{"mdc_vtx_tracks", "eta"}},
                   []( const std::vector<double>& vars ){
      auto eta = vars.at(0);
      return 2*atan( exp( -eta ) );
    } );
    qa_manager->AddEntry2D({{"#phi, [rad]", "mdc_vtx_tracks", "phi"},
                            theta},
                           {{315, -3.15, 3.15}, {170, 0.0, 1.7}});
    qa_manager->AddEntry2D({{"#phi, [rad]", "mdc_vtx_tracks", "phi"},
                            theta},
                           {{315, -3.15, 3.15}, {170, 0.0, 1.7}}, protons);

    qa_manager->AddEntry2D({{"#eta", "mdc_vtx_tracks", "eta"},
                            {"#phi, [rad]", "mdc_vtx_tracks", "phi"}},
                           {{200, 0.0, 2.0},{315, -3.15, 3.15}});
    qa_manager->AddEntry2D({{"#eta", "mdc_vtx_tracks", "eta"},
                            {"#phi, [rad]", "mdc_vtx_tracks", "phi"}},
                           {{200, 0.0, 2.0},{315, -3.15, 3.15}}, protons);

    Variable vertex_xy( "VTX_{XY}, [mm]", {{"event_header", "vtx_x"}, {"event_header", "vtx_x"}},
                       [](std::vector<double> r){
      return sqrt(r.at(0)*r.at(0) + r.at(1)*r.at(1));
    } );

    qa_manager->AddEntry2D({vertex_xy,
                            {"DCA_{XY}", "mdc_vtx_tracks", "dca_xy"}},
                           {{200, 0.0, 5.0},{500, -15.0, 15.0}}, protons);

    qa_manager->AddEntry2D({{"event_header", "vtx_x"},
                            {"DCA_{XY}", "mdc_vtx_tracks", "dca_xy"}},
                           {{200, -5.0, 5.0},{500, -15.0, 15.0}});

    qa_manager->AddEntry2D({{"event_header", "vtx_y"},
                            {"DCA_{XY}", "mdc_vtx_tracks", "dca_xy"}},
                           {{200, -5.0, 5.0},{500, -15.0, 15.0}});
  }
};
} // namespace AnalysisTree
#endif // QUALITY_ASSURANCE_SRC_CMAKE_BUILD_DEBUG_MDC_VERTEX_TRACKS_H_
