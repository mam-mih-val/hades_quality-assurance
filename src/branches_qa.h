//
// Created by mikhail on 8/11/20.
//

#ifndef QUALITY_ASSURANCE_SRC_BRANCHES_QA_H_
#define QUALITY_ASSURANCE_SRC_BRANCHES_QA_H_

#include "AnalysisTree/Variable.hpp"
#include <AnalysisTree/Cuts.hpp>

namespace AnalysisTree{

void AddEventHeaderQA(QA::Task* qa_manager) {
  qa_manager->AddH1({"VTX_{z}, mm", {"event_header", "vtx_z"}, {500, -80.0, 20.0}});
  qa_manager->AddH1({"VTX_{x}, mm", {"event_header", "vtx_x"}, {500, -10.0, 10.0}});
  qa_manager->AddH1({"VTX_{y}, mm", {"event_header", "vtx_y"}, {500, -10.0, 10.0}});

  qa_manager->AddH1({"selected META hits", {"event_header", "selected_tof_rpc_hits"}, {250, 0.0, 250.0}});

  qa_manager->AddH2({"VTX_{x}, mm", {"event_header", "vtx_x"}, {250, -10.0, 10.0}},
                    {"VTX_{y}, mm", {"event_header", "vtx_y"}, {250, -10.0, 10.0}});
  qa_manager->AddH2({"selected META hits", {"event_header", "selected_tof_rpc_hits"}, {250, 0.0, 250.0}},
                    {"selected MDC hits", {"event_header", "selected_mdc_tracks"}, {100, 0.0, 100.0}});
}

void AddMdcVtxTracksQA(QA::Task* qa_manager) {
  qa_manager->AddH1({"Vertex tracks p_{T}, #frac{GeV}{c}", {"mdc_vtx_tracks", "pT"}, {500, 0.0, 2.5}});
  qa_manager->AddH1({"#chi^{2}_{RK}", {"mdc_vtx_tracks", "chi2"}, {500, 0.0, 250.0}});
  qa_manager->AddH1({"DCA_{xy}", {"mdc_vtx_tracks", "dca_xy"}, {500, -15.0, 15.0}});
  qa_manager->AddH1({"DCA_{z}", {"mdc_vtx_tracks", "dca_z"}, {500, -20.0, 20.0}});
  qa_manager->AddH1({"#phi, [rad]", {"mdc_vtx_tracks", "phi"}, {500, -4.0, 4.0}});
  qa_manager->AddH1({"geant pid", {"mdc_vtx_tracks", "geant_pid"}, {50, 0.0, 50.0}});

  Cuts *protons = new Cuts("protons",
      {SimpleCut({"mdc_vtx_tracks", "geant_pid"}, 14. - 0.5, 14. + 0.5)});

  Variable charge_p(
      "p #times z, [z #times #frac{GeV}{c}]", {
          {"mdc_vtx_tracks", "charge"},
          {"mdc_vtx_tracks","p" }},
      [](std::vector<double> &var) { return var.at(0) * var.at(1); });

  Variable y_cm("y-y_{beam}", {{"mdc_vtx_tracks", "rapidity"}},
                [](const std::vector<double> &vars){
                  return vars.at(0)-0.74;
                });

  qa_manager->AddH2({"y-y_{cm}", y_cm, {250, -1.0, 1.0}},
                    {"pt, #frac{GeV}{c}", {"mdc_vtx_tracks", "pT"}, {250, 0.0, 2.5}});
  qa_manager->AddH2({"y-y_{cm}", y_cm, {250, -1.0, 1.0}},
                    {"pt, #frac{GeV}{c}", {"mdc_vtx_tracks", "pT"}, {250, 0.0, 2.5}},
                    protons);

  qa_manager->AddH2({"p #times z, [z #times #frac{GeV}{c^{2}}]", charge_p, {250, -2.0, 5.0}},
                    {"#frac{dE}{dx} MDC", {"mdc_vtx_tracks", "dEdx"}, {200, 0.0, 20.0}});

  qa_manager->AddH2({"p #times z, [z #times #frac{GeV}{c^{2}}]", charge_p, {250, -2.0, 5.0}},
                    {"#frac{dE}{dx} MDC", {"mdc_vtx_tracks", "dEdx"}, {200, 0.0, 20.0}},
                    protons);

  Variable theta( "#theta, [rad]", {{"mdc_vtx_tracks", "eta"}},
                  []( const std::vector<double>& vars ){
                    auto eta = vars.at(0);
                    return 2*atan( exp( -eta ) );
                  } );

  qa_manager->AddH2({"#phi, [rad]", {"mdc_vtx_tracks", "phi"}, {315, -3.15, 3.15}},
                    {"#theta [rad]", theta, {170, 0.0, 1.7}});

  qa_manager->AddH2({"#phi, [rad]", {"mdc_vtx_tracks", "phi"}, {315, -3.15, 3.15}},
                    {"#theta [rad]", theta, {170, 0.0, 1.7}},
                    protons);
}

void AddMetaHitsQA(QA::Task* qa_manager) {
  qa_manager->AddH1({"META match radius, [mm]", {"meta_hits", "match_radius"}, {100, 0.0, 40.0}});
  qa_manager->AddH1({"beta, [#frac{1}{c}]", {"meta_hits", "beta"}, {500, 0.0, 1.5}});
  qa_manager->AddH1({"time, [ns]", {"meta_hits", "time_of_flight"}, {500, 0.0, 100.0}});

  Cuts *protons = new Cuts("protons", {{{"mdc_vtx_tracks", "geant_pid"}, 14. - 0.5, 14. + 0.5}});

  Variable charged_p(
      "p #times z, [z #times #frac{GeV}{c}]", {{"mdc_vtx_tracks","charge"}, {"mdc_vtx_tracks","p"}},
      [](std::vector<double> &var) { return var.at(0) * var.at(1); });

  Variable sqrt_m2("mass META, [#frac{GeV}{c}^{2}]", {{"meta_hits", "mass2"}},
                   [](std::vector<double> &var) { return sqrtf(var.at(0)); });
  Variable charged_mass(
      "m*z META, [z*#frac{GeV}{c}^{2}]", {
          {"meta_hits","mass2"},
          {"meta_hits", "charge"}},
      [](std::vector<double> &var) { return sqrtf(var.at(0)) * var.at(1); });

  qa_manager->AddH2({"p #times z, [z #times #frac{GeV}{c^{2}}]", charged_p, {200, -2.0, 5.0}},
                    {"#frac{dE}{dx} META", {"meta_hits", "dEdx"}, {200, 0.0, 20.0}});
  qa_manager->AddH2({"p #times z, [z #times #frac{GeV}{c^{2}}]", charged_p, {200, -2.0, 5.0}},
                    {"#frac{dE}{dx} META", {"meta_hits", "dEdx"}, {200, 0.0, 20.0}},
                    protons);

  qa_manager->AddH2({"pt, [#frac{GeV}{c}]", {"mdc_vtx_tracks", "pT"}, {250, 0.0, 2.5}},
                    {"m*z META, [z*#frac{GeV}{c}^{2}]", charged_mass, {250, -1.0, 5.0}});
  qa_manager->AddH2({"pt, [#frac{GeV}{c}]", {"mdc_vtx_tracks", "pT"}, {250, 0.0, 2.5}},
                    {"m*z META, [z*#frac{GeV}{c}^{2}]", charged_mass, {250, -1.0, 5.0}},
                    protons);
}

void AddForwardWallHitsQA(QA::Task* qa_manager) {
  Variable module_id("forward_wall_hits", "module_id");

  qa_manager->AddH1({"Wall Hit Charge", {"forward_wall_hits", "signal"}, {500, 0.0, 1000.0}});
  qa_manager->AddH2({"Wall Hit Charge", {"forward_wall_hits", "signal"}, {250, 0.0, 1000.0}},
                    {"Wall Channel", module_id, {304, 0.0, 304.0}});
  qa_manager->AddH2({"#beta", {"forward_wall_hits", "beta"}, {240, 0.0, 1.2}},
                    {"Wall Channel", module_id, {304, 0.0, 304.0}});
  qa_manager->AddH2({"time, [ns]", {"forward_wall_hits", "time"}, {300, 20.0, 50.0}},
                    {"Wall Channel", module_id, {304, 0.0, 304.0}});

  qa_manager->AddH2({"module X, mm", {"forward_wall_hits", "x"}, {100, -1000.0, 1000.0}},
                    {"module Y, mm", {"forward_wall_hits", "y"}, {100, -1000.0, 1000.0}});

  Cuts *inner_modules = new Cuts("inner modules", {{{"forward_wall_hits","ring"}, 0.9, 5.1}});
  Cuts *medium_modules = new Cuts("medium modules", {{{"forward_wall_hits","ring"}, 5.9, 7.1}});
  Cuts *perip_modules = new Cuts("peripheral modules", {{{"forward_wall_hits","ring"}, 7.9, 10.1}});

  qa_manager->AddH2({"module X, mm", {"forward_wall_hits", "x"}, {100, -1000.0, 1000.0}},
                    {"module Y, mm", {"forward_wall_hits", "y"}, {100, -1000.0, 1000.0}}, inner_modules);
  qa_manager->AddH2({"module X, mm", {"forward_wall_hits", "x"}, {100, -1000.0, 1000.0}},
                    {"module Y, mm", {"forward_wall_hits", "y"}, {100, -1000.0, 1000.0}}, medium_modules);
  qa_manager->AddH2({"module X, mm", {"forward_wall_hits", "x"}, {100, -1000.0, 1000.0}},
                    {"module Y, mm", {"forward_wall_hits", "y"}, {100, -1000.0, 1000.0}}, perip_modules);
}

void AddSimDataQA(QA::Task* qa_manager) {
  qa_manager->AddH1({"b, fm", {"sim_header", "impact_parameter"}, {110, 0.0, 11.0}});
  qa_manager->AddH1({"#Psi_{RP}, rad", {"sim_header", "reaction_plane"}, {500, 0.0, 6.29}});

  qa_manager->AddH1({"mass, [#frac{GeV}{c}", {"sim_tracks", "mass"}, {500, 0.0, 10.0}});


  Cuts *protons = new Cuts("protons",
                           {{{"sim_tracks", "geant_pid"}, 14. - 0.5, 14. + 0.5},
                            {{"sim_tracks", "is_primary"}, 0. - 0.5, 0. + 0.5}});

  Variable y_cm("y_{cm}", {{"sim_tracks", "rapidity"}},
                [](const std::vector<double> &vars){
                  return vars.at(0)-0.74;
                });

  qa_manager->AddH2({"y_{cm}", y_cm, {250, -1.0, 1.0}},
                    {"pt_{p}, #frac{GeV}{c}", {"sim_tracks", "pT"}, {200, 0.0, 2.0}}, protons);
}

}

#endif // QUALITY_ASSURANCE_SRC_BRANCHES_QA_H_
