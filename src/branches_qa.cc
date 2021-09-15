//
// Created by mikhail on 9/21/20.
//

#include "branches_qa.h"

namespace AnalysisTree{
void AddEventHeaderQA(QA::Task* qa_manager, bool is_mc) {
  qa_manager->AddH1({"VTX_{z}, mm", {"event_header", "vtx_z"}, {500, -100.0, 20.0}});
  qa_manager->AddH1({"VTX_{x}, mm", {"event_header", "vtx_x"}, {500, -10.0, 10.0}});
  qa_manager->AddH1({"VTX_{y}, mm", {"event_header", "vtx_y"}, {500, -10.0, 10.0}});

  auto pt3_cut = new Cuts("PT3", {SimpleCut({"event_header", "good_trigger"}, 0.5, 1.5)});
  auto pt2_cut = new Cuts("PT2", {SimpleCut({"event_header", "physical_trigger_2"}, 0.5, 1.5)});

  qa_manager->AddH1({"selected META hits", {"event_header", "selected_tof_rpc_hits"}, {250, 0.0, 250.0}});
  qa_manager->AddH1({"Centrality selected META hits", {"event_header", "selected_tof_rpc_hits_centrality"}, {20, 0.0, 100.0}});
  qa_manager->AddH1({"Centrality selected tracks", {"event_header", "selected_mdc_tracks_centrality"}, {20, 0.0, 100.0}});
  qa_manager->AddH1({"Selected tracks", {"event_header", "selected_mdc_tracks"}, {100, 0.0, 100.0}});
  qa_manager->AddH1({"Selected tracks", {"event_header", "selected_mdc_tracks"}, {100, 0.0, 100.0}},
                    pt3_cut);
  qa_manager->AddH1({"Selected tracks", {"event_header", "selected_mdc_tracks"}, {100, 0.0, 100.0}},
                    pt2_cut);
  qa_manager->AddH1({"selected META hits", {"event_header", "tof_rpc_hits"}, {300, 0.0, 300.0}},
                    pt3_cut);
  qa_manager->AddH1({"selected META hits", {"event_header", "selected_tof_rpc_hits"}, {250, 0.0, 250.0}},
                    pt2_cut);

  qa_manager->AddH1({"BK-EP Plain ", {"event_header", "fw_angle_plain"}, {100, -3.5, 3.5}});

  qa_manager->AddH2({"VTX_{x}, mm", {"event_header", "vtx_x"}, {250, -10.0, 10.0}},
                    {"VTX_{y}, mm", {"event_header", "vtx_y"}, {250, -10.0, 10.0}});

  qa_manager->AddH2({"selected META hits", {"event_header", "selected_tof_rpc_hits"}, {250, 0.0, 250.0}},
                    {"selected MDC tracks", {"event_header", "selected_mdc_tracks"}, {100, 0.0, 100.0}});

  qa_manager->AddH2({"selected TOF hits", {"event_header", "selected_tof_hits"}, {100, 0.0, 100.0}},
                    {"selected RPC hits", {"event_header", "selected_rpc_hits"}, {150, 0.0, 150.0}});
  qa_manager->AddH2({"selected TOF hits", {"event_header", "selected_tof_hits"}, {100, 0.0, 100.0}},
                    {"selected MDC tracks", {"event_header", "selected_mdc_tracks"}, {100, 0.0, 100.0}});
  qa_manager->AddH2({"selected RPC hits", {"event_header", "selected_rpc_hits"}, {150, 0.0, 150.0}},
                    {"selected MDC tracks", {"event_header", "selected_mdc_tracks"}, {100, 0.0, 100.0}});

  if( !is_mc ) {
    qa_manager->AddH2({"selected META hits",
                       {"event_header", "selected_tof_rpc_hits"},
                       {250, 0.0, 250.0}},
                      {"FW ", {"event_header", "fw_adc"}, {250, 0.0, 10000.0}});
    qa_manager->AddH2({"selected MDC tracks",
                       {"event_header", "selected_mdc_tracks"},
                       {100, 0.0, 100.0}},
                      {"FW ", {"event_header", "fw_adc"}, {250, 0.0, 10000.0}});
  }
  if( is_mc ){
    qa_manager->AddH2({"selected META hits",
                       {"event_header", "selected_tof_rpc_hits"},
                       {250, 0.0, 250.0}},
                      {"FW ", {"event_header", "fw_adc"}, {200, 0.0, 200.0}});
    qa_manager->AddH2({"selected MDC tracks",
                       {"event_header", "selected_mdc_tracks"},
                       {100, 0.0, 100.0}},
                      {"FW ", {"event_header", "fw_adc"}, {200, 0.0, 200.0}});
  }
}

void AddMdcVtxTracksQA(QA::Task* qa_manager, double beam_y) {
  Variable theta( "theta", {{"mdc_vtx_tracks", "eta"}},
                  []( const std::vector<double>& vars ){
                    auto eta = vars.at(0);
                    return 2*atan( exp( -eta ) );
                  } );
  qa_manager->AddH1({"Vertex tracks p_{T}, #frac{GeV}{c}", {"mdc_vtx_tracks", "pT"}, {500, 0.0, 2.5}});
  qa_manager->AddH1({"#chi^{2}_{RK}", {"mdc_vtx_tracks", "chi2"}, {300, 0.0, 150.0}});
  qa_manager->AddH1({"DCA_{xy}", {"mdc_vtx_tracks", "dca_xy"}, {500, -15.0, 15.0}});
  qa_manager->AddH1({"DCA_{z}", {"mdc_vtx_tracks", "dca_z"}, {500, -20.0, 20.0}});
  qa_manager->AddH1({"#phi, [rad]", {"mdc_vtx_tracks", "phi"}, {500, -4.0, 4.0}});
  qa_manager->AddH1({"geant pid", {"mdc_vtx_tracks", "geant_pid"}, {50, 0.0, 50.0}});
  qa_manager->AddH1({"#eta", {"mdc_vtx_tracks", "eta"}, {440, 0.0, 2.2}});
  qa_manager->AddH1({"#theta", theta, {180, 0.0, 1.7}});

//  qa_manager->AddH1({"n hits all layers", {"mdc_vtx_tracks", "layers_total"}, {25, 0.0, 25.0}});
//  Variable fired_layers("fired_layers_in_stations",{{"mdc_vtx_tracks", "layers_0"},
//                                                    {"mdc_vtx_tracks", "layers_1"},
//                                                    {"mdc_vtx_tracks", "layers_2"},
//                                                    {"mdc_vtx_tracks", "layers_3"}}, [](const std::vector<double>& layers){
//    return layers.at(0)*1e3+layers.at(1)*1e2+layers.at(2)*1e1+layers.at(3)*1e0;
//  });
//  qa_manager->AddH1({"n hits 0 station", {"mdc_vtx_tracks", "layers_0"}, {7, 0.0, 7.0}});
//  qa_manager->AddH1({"n hits 1 station", {"mdc_vtx_tracks", "layers_1"}, {7, 0.0, 7.0}});
//  qa_manager->AddH1({"n hits 2 station", {"mdc_vtx_tracks", "layers_2"}, {7, 0.0, 7.0}});
//  qa_manager->AddH1({"n hits 3 station", {"mdc_vtx_tracks", "layers_3"}, {7, 0.0, 7.0}});
//  qa_manager->AddH1({"fired layers", fired_layers, {6667, 0.0, 6667}});

  Variable charged_p(
      "p_divide_z", {
          {"mdc_vtx_tracks", "charge"},
          {"mdc_vtx_tracks","p" }},
      [](std::vector<double> &var) { return var.at(1)/var.at(0); });

  Variable y_cm("y_cm", {{"mdc_vtx_tracks", "rapidity"}},
                [beam_y](const std::vector<double> &vars){
                  return vars.at(0)-beam_y;
                });
  Variable charged_m2(
      "m2_times_z", {{"mdc_vtx_tracks","charge"}, {"meta_hits","mass2"}},
      [](std::vector<double> &var) { return var.at(1)*var.at(0); });
  Variable charged_beta(
      "beta_times_z", {{"mdc_vtx_tracks","charge"}, {"meta_hits","beta"}},
      [](std::vector<double> &var) { return var.at(1)*var.at(0); });
  qa_manager->AddH2({"#beta", charged_beta, {250, -1.25, 1.25}},
                    {"#frac{dE}{dx} MDC", {"mdc_vtx_tracks", "dEdx"}, {200, 0.0, 20.0}});
  qa_manager->AddH2({"#beta", charged_beta, {250, -1.25, 1.25}},
                    {"#frac{dE}{dx} META", {"meta_hits", "dEdx"}, {200, 0.0, 20.0}});
  qa_manager->AddH2({"#frac{dE}{dx} MDC", {"mdc_vtx_tracks", "dEdx"}, {200, 0.0, 20.0}},
                    {"m^{2}z, [#frac{GeV}{c}]", charged_m2, {550, -1.0, 10.0}});
  qa_manager->AddH2({"#frac{dE}{dx} META", {"meta_hits", "dEdx"}, {200, 0.0, 20.0}},
                    {"m^{2}z, [#frac{GeV}{c}]", charged_m2, {550, -1.0, 10.0}});
  Variable z( "DCA_z_VTX_z", {{"mdc_vtx_tracks", "dca_z"}, {"event_header", "vtx_z"}}, [](const std::vector<double>& vars){
    return vars.at(0)+vars.at(1);
  } );
  qa_manager->AddH2({"DCA_{z}+VTX_{z}", z, {500, -100.0, 20.0}},
                    {"DCA_{xy}", {"mdc_vtx_tracks", "dca_xy"}, {200, -15.0, 15.0}});
  qa_manager->AddH2({"#phi, [rad]", {"mdc_vtx_tracks", "phi"}, {315, -3.15, 3.15}},
                    {"DCA_{xy}", {"mdc_vtx_tracks", "dca_xy"}, {200, -15.0, 15.0}});
  qa_manager->AddH1({"DCA_{z}+VTX_{z}", z, {500, -100.0, 20.0}});
  Cuts *protons_pions = new Cuts("pions_protons",
                                 {SimpleCut({{"mdc_vtx_tracks", "pid"}}, [](std::vector<double> pid){
                                   return
                                       fabs(pid.at(0) - 2212) < 0.1 ||
                                       fabs(pid.at(0) - 211) < 0.1 ||
                                       fabs(pid.at(0) + 211) < 0.1;})});
  Cuts *light_nuclei = new Cuts("light_nuclei",
                                 {SimpleCut({{"mdc_vtx_tracks", "geant_pid"}}, [](std::vector<double> pid){
                                   return
                                       fabs(pid.at(0) - 45) < 0.1 ||
                                       fabs(pid.at(0) - 46) < 0.1 ||
                                       fabs(pid.at(0) - 47) < 0.1 ||
                                       fabs(pid.at(0) - 49) < 0.1;})});
  Variable protonidity(
      "protonidity", {{"mdc_vtx_tracks","p"}, {"mdc_vtx_tracks","pz"}},
      [](std::vector<double> &var) {
        auto E = sqrt( var.at(0)*var.at(0) + 0.938*0.938 );
        auto y = 0.5*( log( E + var.at(1) ) - log( E - var.at(1) ) ) - 0.74;
        return y; });

  qa_manager->AddH2({"y-y_{cm}", y_cm, {200, -1.0, 1.0}},
                    {"pt, #frac{GeV}{c}", {"mdc_vtx_tracks", "pT"}, {200, 0.0, 2.5}});
  qa_manager->AddH2({"y{p}", protonidity, {200, -1.0, 1.0}},
                    {"pt, #frac{GeV}{c}", {"mdc_vtx_tracks", "pT"}, {200, 0.0, 2.5}});
  qa_manager->AddH2({"y-y_{cm}", y_cm, {200, -1.0, 1.0}},
                    {"pt, #frac{GeV}{c}", {"mdc_vtx_tracks", "pT"}, {200, 0.0, 2.5}}, protons_pions);
  qa_manager->AddH2({"y-y_{cm}", y_cm, {200, -1.0, 1.0}},
                    {"pt, #frac{GeV}{c}", {"mdc_vtx_tracks", "pT"}, {200, 0.0, 2.5}}, light_nuclei);
  qa_manager->AddH2({"#eta", {"mdc_vtx_tracks", "eta"}, {250, 0.0, 2.5}},
                    {"pt, #frac{GeV}{c}", {"mdc_vtx_tracks", "pT"}, {200, 0.0, 2.0}});
  qa_manager->AddH2({"#eta", {"mdc_vtx_tracks", "eta"}, {250, 0.0, 2.5}},
                    {"p, #frac{GeV}{c}", {"mdc_vtx_tracks", "p"}, {250, 0.0, 5.0}});
  qa_manager->AddH2({"p, #frac{GeV}{c}", {"mdc_vtx_tracks", "p"}, {250, 0.0, 5.0}},
                    {"#phi, [rad]", {"mdc_vtx_tracks", "phi"}, {315, -3.15, 3.15}});
  qa_manager->AddH2({"p, #frac{GeV}{c}", {"mdc_vtx_tracks", "p"}, {250, 0.0, 5.0}},
                    {"#eta", {"mdc_vtx_tracks", "eta"}, {250, 0.0, 2.5}},
                    light_nuclei);
  qa_manager->AddH2({"p, #frac{GeV}{c}", {"mdc_vtx_tracks", "p"}, {250, 0.0, 5.0}},
                    {"#eta", {"mdc_vtx_tracks", "eta"}, {250, 0.0, 2.5}},
                    protons_pions);
//  qa_manager->AddH2({"#eta", {"mdc_vtx_tracks", "eta"}, {275, 0.0, 5.5}},
//                    {"pt, #frac{GeV}{c}", {"mdc_vtx_tracks", "pT"}, {250, 0.0, 2.5}},
//                    protons_qvector);
  qa_manager->AddH2({"p/z, [#frac{GeV}{c^{2}}]", charged_p, {250, -2.0, 5.0}},
                    {"#frac{dE}{dx} MDC", {"mdc_vtx_tracks", "dEdx"}, {200, 0.0, 20.0}});


  qa_manager->AddH2({"#phi, [rad]", {"mdc_vtx_tracks", "phi"}, {315, -3.15, 3.15}},
                    {"#theta [rad]", theta, {170, 0.0, 1.7}});
  qa_manager->AddH2({"#phi_{out}, [rad]", {"mdc_vtx_tracks", "phi_out"}, {315, -3.15, 3.15}},
                    {"#theta_{out} [rad]", {"mdc_vtx_tracks", "theta_out"}, {170, 0.0, 1.7}});
}

void AddMetaHitsQA(QA::Task* qa_manager) {
  qa_manager->AddH1({"META match radius, [mm]", {"meta_hits", "match_radius"}, {400, 0.0, 40.0}});
  qa_manager->AddH1({"META match quality", {"meta_hits", "match_quality"}, {500, -10.0, 10.0}});
  qa_manager->AddH1({"beta, [#frac{1}{c}]", {"meta_hits", "beta"}, {500, 0.0, 1.5}});
  qa_manager->AddH1({"time, [ns]", {"meta_hits", "time_of_flight"}, {500, 0.0, 50.0}});
  qa_manager->AddH1({"m^{2} META, #frac{GeV^{2}}{c^{4}}", {"meta_hits", "mass2"}, {550, -1.0, 10.0}});
  qa_manager->AddH1({"distance, mm", {"meta_hits", "path_length"}, {500, 2000.0, 3000.0}});

  Variable charged_p(
      "p_divide_z", {{"mdc_vtx_tracks","charge"}, {"mdc_vtx_tracks","p"}},
      [](std::vector<double> &var) { return var.at(1)/var.at(0); });
  Variable charged_pT(
      "pT_divide_z", {{"mdc_vtx_tracks","charge"}, {"mdc_vtx_tracks","pT"}},
      [](std::vector<double> &var) { return var.at(1)/var.at(0); });

  qa_manager->AddH2({"p/z, [#frac{GeV}{c}]", charged_p, {250, -2.5, 5.0}},
                    {"#frac{dE}{dx} META", {"meta_hits", "dEdx"}, {200, 0.0, 20.0}});

  qa_manager->AddH2({"p/z, [#frac{GeV}{c}]", charged_p, {250, -2.5, 5.0}},
                    {"#beta", {"meta_hits", "beta"}, {250, 0.0, 1.25}});

  qa_manager->AddH2({"p/z, [#frac{GeV}{c}]", charged_p, {250, -2.5, 5.0}},
                    {"m^{2} META, [#frac{GeV^{2}}{c}^{4}]", {"meta_hits", "mass2"}, {550, -1.0, 10.0}});
}

void AddParticleQA(QA::Task* qa_manager, int pdg_code, double beam_y){

  struct axis{
    int n_bins;
    double hi;
    double lo;
  };
  Cuts *analysis_ycm = new Cuts("analysis_ycm_"+std::to_string(pdg_code),
                                {SimpleCut({{"mdc_vtx_tracks", "rapidity"},
                                            {"mdc_vtx_tracks", "pid"}},
                                           [pdg_code](std::vector<double> var){
                                  return  -0.75 < var.at(0)-0.74 &&
                                                   var.at(0)-0.74 < 0.75
                                                 && fabs(var.at(1)-pdg_code)<0.1;})});
  std::map<int, axis> m2_axes_map{
      {2212, {200, 0.5, 1.5}},
      {211, {300, -0.05, 0.1}},
      {-211, {300, -0.05, 0.1}},
      {11, {300, -0.05, 0.1}},
      {-11, {300, -0.05, 0.1}},
      {321, {200, 0.0, 1.0}},
      {-321, {200, 0.0, 1.0}},
  };
  Variable theta( "theta", {{"mdc_vtx_tracks", "eta"}},
                  []( const std::vector<double>& vars ){
                    auto eta = vars.at(0);
                    return 2*atan( exp( -eta ) );
                  } );
  Cuts *particle = new Cuts(std::to_string(pdg_code), {SimpleCut({"mdc_vtx_tracks", "pid"}, pdg_code)});
  Cuts *central_events_particle = new Cuts(std::to_string(pdg_code)+"_central",
                                           {SimpleCut({"mdc_vtx_tracks", "pid"}, pdg_code),
                                            SimpleCut({"event_header", "selected_tof_rpc_hits_centrality"}, 0.0, 15.0)});
  Cuts *peripheral_events_particle = new Cuts(std::to_string(pdg_code)+"_peripheral",
                                           {SimpleCut({"mdc_vtx_tracks", "pid"}, pdg_code),
                                            SimpleCut({"event_header", "selected_tof_rpc_hits_centrality"}, 25.0, 40.0)});

  Variable z( "DCA_z_VTX_z", {{"mdc_vtx_tracks", "dca_z"}, {"event_header", "vtx_z"}}, [](const std::vector<double>& vars){
    return vars.at(0)+vars.at(1);
  } );
  qa_manager->AddH2({"#phi, [rad]", {"mdc_vtx_tracks", "phi"}, {315, -3.15, 3.15}},
                    {"DCA_{xy}", {"mdc_vtx_tracks", "dca_xy"}, {200, -15.0, 15.0}}, particle);
  qa_manager->AddH2({"DCA_{z}+VTX_{z}", z, {500, -100.0, 20.0}},
                    {"DCA_{xy}", {"mdc_vtx_tracks", "dca_xy"}, {200, -15.0, 15.0}}, particle);
  qa_manager->AddH1({"DCA_{z}+VTX_{z}", z, {500, -100.0, 20.0}}, particle);
  qa_manager->AddH1({"#eta", {"mdc_vtx_tracks", "eta"}, {440, 0.0, 2.2}}, analysis_ycm);
  qa_manager->AddH1({"#theta", theta, {180, 0.0, 90.0}}, analysis_ycm);

  Variable charged_p(
      "p_divide_z", {
          {"mdc_vtx_tracks", "charge"},
          {"mdc_vtx_tracks","p" }},
      [](std::vector<double> &var) { return var.at(1)/var.at(0); });
  Variable mT_pT(
      "mT_divide_pT", {
          {"mdc_vtx_tracks", "pT"},
          {"mdc_vtx_tracks","mass"}},
      [](std::vector<double> &var) { return sqrt(var.at(0)*var.at(0)+var.at(1)*var.at(1))/var.at(0); });

  Variable phi_in_phi_out(
      "phi_in_phi_out", {
          {"mdc_vtx_tracks", "phi"},
          {"mdc_vtx_tracks","phi_out"}},
      [](std::vector<double> &var) { return var.at(0)-var.at(1); });
  Variable charged_pT(
      "pT_divide_z", {{"mdc_vtx_tracks","charge"}, {"mdc_vtx_tracks","pT"}},
      [](std::vector<double> &var) { return var.at(1)/var.at(0); });
  Variable charged_m2(
      "m2_times_z", {{"mdc_vtx_tracks","charge"}, {"meta_hits","mass2"}},
      [](std::vector<double> &var) { return var.at(1)*var.at(0); });
  Variable charged_beta(
      "beta_times_z", {{"mdc_vtx_tracks","charge"}, {"meta_hits","beta"}},
      [](std::vector<double> &var) { return var.at(1)*var.at(0); });

  Variable protonidity(
      "protonidity", {{"mdc_vtx_tracks","p"}, {"mdc_vtx_tracks","pz"}},
      [](std::vector<double> &var) {
        auto E = sqrt( var.at(0)*var.at(0) + 0.938*0.938 );
        auto y = 0.5*( log( E + var.at(1) ) - log( E - var.at(1) ) ) - 0.74;
        return y; });

  Variable y_cm("y_cm", {{"mdc_vtx_tracks", "rapidity"}},
                [beam_y](const std::vector<double> &vars){
                  return vars.at(0)-beam_y;
                });
//  qa_manager->AddH1({"n hits all layers", {"mdc_vtx_tracks", "layers_total"}, {25, 0.0, 25.0}},
//                    particle);
//  Variable fired_layers("fired_layers_in_stations",{{"mdc_vtx_tracks", "layers_0"},
//                                                    {"mdc_vtx_tracks", "layers_1"},
//                                                    {"mdc_vtx_tracks", "layers_2"},
//                                                    {"mdc_vtx_tracks", "layers_3"}}, [](const std::vector<double>& layers){
//    return layers.at(0)*1e3+layers.at(1)*1e2+layers.at(2)*1e1+layers.at(3)*1e0;
//  });
//  qa_manager->AddH1({"n hits 0 station", {"mdc_vtx_tracks", "layers_0"}, {7, 0.0, 7.0}}, particle);
//  qa_manager->AddH1({"n hits 1 station", {"mdc_vtx_tracks", "layers_1"}, {7, 0.0, 7.0}}, particle);
//  qa_manager->AddH1({"n hits 2 station", {"mdc_vtx_tracks", "layers_2"}, {7, 0.0, 7.0}}, particle);
//  qa_manager->AddH1({"n hits 3 station", {"mdc_vtx_tracks", "layers_3"}, {7, 0.0, 7.0}}, particle);
//  qa_manager->AddH1({"fired layers", fired_layers, {6667, 0.0, 6667}}, particle);

  qa_manager->AddH1({"#chi^{2}_{TRK}", {"mdc_vtx_tracks", "chi2"}, {300, 0.0, 150.0}},particle);
  qa_manager->AddH1({"#chi^{2}_{IN}", {"mdc_vtx_tracks", "chi2_in"}, {300, 0.0, 15.0}},particle);
  qa_manager->AddH1({"#chi^{2}_{OUT}", {"mdc_vtx_tracks", "chi2_out"}, {300, 0.0, 15.0}},particle);
  qa_manager->AddH1({"p_{T}, #frac{GeV}{c}", {"mdc_vtx_tracks", "pT"}, {500, 0.0, 2.5}}, particle);
  qa_manager->AddH1({"#phi, rad", {"mdc_vtx_tracks", "phi"}, {350, -3.5, 3.5}}, particle);
  qa_manager->AddH1({"#phi_{out}, rad", {"mdc_vtx_tracks", "phi_out"}, {350, -3.5, 3.5}}, particle);
  qa_manager->AddH1({"#theta_{out}, rad", {"mdc_vtx_tracks", "theta_out"}, {350, -3.5, 3.5}}, particle);
  qa_manager->AddH1({"#phi_{in}-#phi_{out}, rad", phi_in_phi_out, {200, -0.5, 0.5}}, particle);
  qa_manager->AddH1({"m_{T}/p_{T}", mT_pT, {500, 0.0, 2.5}}, particle);
  qa_manager->AddH1({"p, #frac{GeV}{c}", {"mdc_vtx_tracks", "p"}, {500, 0.0, 5.0}}, particle);
  qa_manager->AddH1({"#beta, #frac{v}{c}", {"meta_hits", "beta"}, {500, 0.0, 1.25}}, particle);
  qa_manager->AddH1({"distance, mm", {"meta_hits", "path_length"}, {500, 2000.0, 3000.0}}, particle);
  qa_manager->AddH1({"time, ns", {"meta_hits", "time_of_flight"}, {500, 0, 50.0}}, particle);
  qa_manager->AddH1({"m^{2} META, #frac{GeV^{2}}{c^{4}}", {"meta_hits", "mass2"}, {550, -1.0, 10.0}}, particle);

  qa_manager->AddH2({"y-y_{cm}", y_cm, {200, -1.0, 1.0}},
                    {"#chi^{2}_{TRK}", {"mdc_vtx_tracks", "chi2"}, {100, 0.0, 50.0}},
                    particle);
  qa_manager->AddH2({"pt, #frac{GeV}{c}", {"mdc_vtx_tracks", "pT"}, {200, 0.0, 2.5}},
                    {"#chi^{2}_{TRK}", {"mdc_vtx_tracks", "chi2"}, {100, 0.0, 50.0}},
                    particle);
  qa_manager->AddH2({"#chi^{2}_{TRK}", {"mdc_vtx_tracks", "chi2"}, {300, 0.0, 150.0}},
  {"#chi^{2}_{IN}", {"mdc_vtx_tracks", "chi2_in"}, {300, 0.0, 15.0}},
                    particle);
  qa_manager->AddH2({"#chi^{2}_{TRK}", {"mdc_vtx_tracks", "chi2"}, {300, 0.0, 150.0}},
  {"#chi^{2}_{OUT}", {"mdc_vtx_tracks", "chi2_out"}, {300, 0.0, 15.0}},
                    particle);
  qa_manager->AddH2({"#chi^{2}_{IN}", {"mdc_vtx_tracks", "chi2_in"}, {300, 0.0, 15.0}},
  {"#chi^{2}_{OUT}", {"mdc_vtx_tracks", "chi2_out"}, {300, 0.0, 15.0}},
                    particle);
  qa_manager->AddH2({"y-y_{cm}", y_cm, {200, -1.0, 1.0}},
                    {"pt, #frac{GeV}{c}", {"mdc_vtx_tracks", "pT"}, {200, 0.0, 2.5}},
                    particle);
  qa_manager->AddH2({"pt, #frac{GeV}{c}", {"mdc_vtx_tracks", "pT"}, {200, 0.0, 2.5}},
                    {"#phi_{in}-#phi_{out}, rad", phi_in_phi_out, {200, -0.5, 0.5}},
                    particle);
  qa_manager->AddH2({"y-y_{cm}", y_cm, {200, -1.0, 1.0}},
                    {"#phi_{in}-#phi_{out}, rad", phi_in_phi_out, {200, -0.5, 0.5}},
                    particle);
  qa_manager->AddH2({"p, GeV/c", {"mdc_vtx_tracks", "p"}, {200, 0.0, 3.5}},
                    {"pt, GeV/c", {"mdc_vtx_tracks", "pT"}, {200, 0.0, 2.5}},
                    particle);
  qa_manager->AddH2({"#theta [rad]", theta, {170, 0.0, 1.7}},
                    {"p, GeV/c", {"mdc_vtx_tracks", "p"}, {200, 0.0, 3.5}},
                    particle);
  qa_manager->AddH2({"p, #frac{GeV}{c}", {"mdc_vtx_tracks", "p"}, {250, 0.0, 5.0}},
                    {"#eta", {"mdc_vtx_tracks", "eta"}, {250, 0.0, 2.5}},
                    particle);
  qa_manager->AddH2({"#eta", {"mdc_vtx_tracks", "eta"}, {250, 0.0, 2.5}},
                    {"pt, #frac{GeV}{c}", {"mdc_vtx_tracks", "pT"}, {250, 0.0, 2.5}},
                    particle);
  qa_manager->AddH2({"y-y_{cm}", y_cm, {200, -1.0, 1.0}},
                    {"#phi, [rad]", {"mdc_vtx_tracks", "phi"}, {350, -3.5, 3.5}},
                    particle);
  qa_manager->AddH2({"#phi, [rad]", {"mdc_vtx_tracks", "phi"}, {315, -3.15, 3.15}},
                    {"#theta [rad]", theta, {170, 0.0, 1.7}},
                    particle);
  qa_manager->AddH2({"p/z, [#frac{GeV}{c}]", charged_p, {250, -2.5, 5.0}},
                    {"#frac{dE}{dx} MDC", {"mdc_vtx_tracks", "dEdx"}, {200, 0.0, 20.0}},
                    particle);
  qa_manager->AddH2({"#beta", charged_beta, {250, -1.25, 1.25}},
                    {"#frac{dE}{dx} MDC", {"mdc_vtx_tracks", "dEdx"}, {200, 0.0, 20.0}},
                    particle);
  qa_manager->AddH2({"#beta", charged_beta, {250, -1.25, 1.25}},
                    {"#frac{dE}{dx} META", {"meta_hits", "dEdx"}, {200, 0.0, 20.0}},
                    particle);
  qa_manager->AddH2({"#frac{dE}{dx} MDC", {"mdc_vtx_tracks", "dEdx"}, {200, 0.0, 20.0}},
                    {"m^{2}z, [#frac{GeV}{c}]", charged_m2, {550, -1.0, 10.0}},
                    particle);
  qa_manager->AddH2({"#frac{dE}{dx} META", {"meta_hits", "dEdx"}, {200, 0.0, 20.0}},
                    {"m^{2}z, [#frac{GeV}{c}]", charged_m2, {550, -1.0, 10.0}},
                    particle);
  qa_manager->AddH2({"p/z, [#frac{GeV}{c}]", charged_p, {250, -2.5, 5.0}},
                    {"#frac{dE}{dx} META", {"meta_hits", "dEdx"}, {200, 0.0, 20.0}},
                    particle);
  qa_manager->AddH2({"p/z, [#frac{GeV}{c}]", charged_p, {250, -2.5, 5.0}},
                    {"#beta", {"meta_hits", "beta"}, {250, 0.0, 1.25}},
                    particle);
  qa_manager->AddH2({"p/z, [#frac{GeV}{c}]", charged_p, {250, -2.5, 5.0}},
                    {"m^{2} META, [#frac{GeV^{2}}{c}^{4}]", {"meta_hits", "mass2"},
                     {m2_axes_map.at(pdg_code).n_bins, m2_axes_map.at(pdg_code).lo, m2_axes_map.at(pdg_code).hi }},
                    particle);
  qa_manager->AddH2({"p/z, [#frac{GeV}{c}]", charged_p, {250, -2.5, 5.0}},
                    {"#theta [rad]", theta, {170, 0.0, 1.7}},
                    particle);
  qa_manager->AddH2({"p/z, [#frac{GeV}{c}]", charged_p, {250, -2.5, 5.0}},
                    {"#theta_{OUT} [rad]", {"mdc_vtx_tracks", "theta_out"}, {170, 0.0, 1.7}},
                    particle);
  qa_manager->AddH2({"p, #frac{GeV}{c}", {"mdc_vtx_tracks", "p"}, {250, 0.0, 5.0}},
                    {"#phi, [rad]", {"mdc_vtx_tracks", "phi"}, {315, -3.15, 3.15}}, particle);
}

void AddForwardWallHitsQA(QA::Task* qa_manager, bool is_mc) {
  Variable module_id("forward_wall_hits", "module_id");

  if( !is_mc ) {
    qa_manager->AddH1({"Wall Hit Charge",
                       {"forward_wall_hits", "signal"},
                       {500, 0.0, 1000.0}});
    qa_manager->AddH2({"Wall Hit Charge",
                       {"forward_wall_hits", "signal"},
                       {250, 0.0, 1000.0}},
                      {"Wall Channel", module_id, {304, 0.0, 304.0}});
  }
  if( is_mc ){
    qa_manager->AddH1({"Wall Hit Charge",
                       {"forward_wall_hits", "signal"},
                       {500, 0.0, 30.0}});
    qa_manager->AddH2({"Wall Hit Charge",
                       {"forward_wall_hits", "signal"},
                       {250, 0.0, 30.0}},
                      {"Wall Channel", module_id, {304, 0.0, 304.0}});
  }
  qa_manager->AddH2({"#beta", {"forward_wall_hits", "beta"}, {240, 0.0, 1.2}},
                    {"Wall Channel", module_id, {304, 0.0, 304.0}});
  qa_manager->AddH2({"time, [ns]", {"forward_wall_hits", "time"}, {300, 20.0, 50.0}},
                    {"Wall Channel", module_id, {304, 0.0, 304.0}});

  qa_manager->AddH2({"module X, mm", {"forward_wall_hits", "x"}, {100, -1000.0, 1000.0}},
                    {"module Y, mm", {"forward_wall_hits", "y"}, {100, -1000.0, 1000.0}});

  Variable hit_distance( "hit_distance", {{"forward_wall_hits", "time"},
                                          {"forward_wall_hits", "beta"}},
                         [](const std::vector<double>& vars){
                           return vars.at(0)*vars.at(1) * 299'792'458e-9;
                         });
  Variable eta( "eta", {{"forward_wall_hits", "x"},
                        {"forward_wall_hits", "y"},
                        {"forward_wall_hits", "z"}},
                [](const std::vector<double>& vars){
                  auto rT =  sqrt(vars.at(0)*vars.at(0)+vars.at(1)*vars.at(1));
                  auto theta = atan2( rT, vars.at(2));
                  auto eta = -log( tan(theta/2) );
                  return eta;
                });
  qa_manager->AddH2({"distance, [m]", hit_distance, {500, 6.7, 7.0}},
                    {"Wall Channel", module_id, {304, 0.0, 304.0}});
  Cuts *inner_modules = new Cuts("inner modules", {{{"forward_wall_hits","ring"}, 0.9, 5.1}});
  Cuts *medium_modules = new Cuts("medium modules", {{{"forward_wall_hits","ring"}, 5.9, 7.1}});
  Cuts *perip_modules = new Cuts("peripheral modules", {{{"forward_wall_hits","ring"}, 7.9, 10.1}});

  qa_manager->AddH2({"#eta", eta, {325, 0, 5.90}},
                    {"Wall Channel", module_id, {304, 0.0, 304.0}});
  qa_manager->AddH2({"#eta", eta, {325, 2.65, 5.90}},
                    {"Wall Channel", module_id, {304, 0.0, 304.0}}, inner_modules);
  qa_manager->AddH2({"#eta", eta, {325, 2.65, 5.90}},
                    {"Wall Channel", module_id, {304, 0.0, 304.0}}, medium_modules);
  qa_manager->AddH2({"#eta", eta, {325, 2.65, 5.90}},
                    {"Wall Channel", module_id, {304, 0.0, 304.0}}, perip_modules);
  qa_manager->AddH2({"module X, mm", {"forward_wall_hits", "x"}, {100, -1000.0, 1000.0}},
                    {"module Y, mm", {"forward_wall_hits", "y"}, {100, -1000.0, 1000.0}}, inner_modules);
  qa_manager->AddH2({"module X, mm", {"forward_wall_hits", "x"}, {100, -1000.0, 1000.0}},
                    {"module Y, mm", {"forward_wall_hits", "y"}, {100, -1000.0, 1000.0}}, medium_modules);
  qa_manager->AddH2({"module X, mm", {"forward_wall_hits", "x"}, {100, -1000.0, 1000.0}},
                    {"module Y, mm", {"forward_wall_hits", "y"}, {100, -1000.0, 1000.0}}, perip_modules);

  if( !is_mc ) {
    qa_manager->AddH2(
        {"selected META hits",
         {"event_header", "selected_tof_rpc_hits"},
         {250, 0.0, 250.0}},
        {"Module signal", {"forward_wall_hits", "signal"}, {250, 0.0, 1000.0}},
        inner_modules);
    qa_manager->AddH2(
        {"selected MDC tracks",
         {"event_header", "selected_mdc_tracks"},
         {100, 0.0, 100.0}},
        {"Module signal", {"forward_wall_hits", "signal"}, {250, 0.0, 1000.0}},
        inner_modules);

    qa_manager->AddH2(
        {"selected META hits",
         {"event_header", "selected_tof_rpc_hits"},
         {250, 0.0, 250.0}},
        {"Module signal", {"forward_wall_hits", "signal"}, {250, 0.0, 1000.0}},
        medium_modules);
    qa_manager->AddH2(
        {"selected MDC tracks",
         {"event_header", "selected_mdc_tracks"},
         {100, 0.0, 100.0}},
        {"Module signal", {"forward_wall_hits", "signal"}, {250, 0.0, 1000.0}},
        medium_modules);

    qa_manager->AddH2(
        {"selected META hits",
         {"event_header", "selected_tof_rpc_hits"},
         {250, 0.0, 250.0}},
        {"Module signal", {"forward_wall_hits", "signal"}, {250, 0.0, 1000.0}},
        perip_modules);
    qa_manager->AddH2(
        {"selected MDC tracks",
         {"event_header", "selected_mdc_tracks"},
         {100, 0.0, 100.0}},
        {"Module signal", {"forward_wall_hits", "signal"}, {250, 0.0, 1000.0}},
        perip_modules);
  }
  if( is_mc ){
    qa_manager->AddH2(
        {"selected META hits",
         {"event_header", "selected_tof_rpc_hits"},
         {250, 0.0, 250.0}},
        {"Module signal", {"forward_wall_hits", "signal"}, {250, 0.0, 30.0}},
        inner_modules);
    qa_manager->AddH2(
        {"selected MDC tracks",
         {"event_header", "selected_mdc_tracks"},
         {100, 0.0, 100.0}},
        {"Module signal", {"forward_wall_hits", "signal"}, {250, 0.0, 30.0}},
        inner_modules);

    qa_manager->AddH2(
        {"selected META hits",
         {"event_header", "selected_tof_rpc_hits"},
         {250, 0.0, 250.0}},
        {"Module signal", {"forward_wall_hits", "signal"}, {250, 0.0, 30.0}},
        medium_modules);
    qa_manager->AddH2(
        {"selected MDC tracks",
         {"event_header", "selected_mdc_tracks"},
         {100, 0.0, 100.0}},
        {"Module signal", {"forward_wall_hits", "signal"}, {250, 0.0, 30.0}},
        medium_modules);

    qa_manager->AddH2(
        {"selected META hits",
         {"event_header", "selected_tof_rpc_hits"},
         {250, 0.0, 250.0}},
        {"Module signal", {"forward_wall_hits", "signal"}, {250, 0.0, 30.0}},
        perip_modules);
    qa_manager->AddH2(
        {"selected MDC tracks",
         {"event_header", "selected_mdc_tracks"},
         {100, 0.0, 100.0}},
        {"Module signal", {"forward_wall_hits", "signal"}, {250, 0.0, 30.0}},
        perip_modules);
  }
}

void AddReconstructedForwardWallHitsQA(QA::Task* qa_manager) {
  Variable module_id("reconstructed_forward_wall_hits", "module_id");

  qa_manager->AddH1({"Wall Hit Charge",
                     {"reconstructed_forward_wall_hits", "signal"},
                     {500, 0.0, 1000.0}});
  qa_manager->AddH2({"Wall Hit Charge",
                     {"reconstructed_forward_wall_hits", "signal"},
                     {250, 0.0, 1000.0}},
                    {"Wall Channel", module_id, {304, 0.0, 304.0}});

  qa_manager->AddH2({"#beta", {"reconstructed_forward_wall_hits", "beta"}, {240, 0.0, 1.2}},
                    {"Wall Channel", module_id, {304, 0.0, 304.0}});
  qa_manager->AddH2({"time, [ns]", {"reconstructed_forward_wall_hits", "time"}, {300, 20.0, 50.0}},
                    {"Wall Channel", module_id, {304, 0.0, 304.0}});

  qa_manager->AddH2({"module X, mm", {"reconstructed_forward_wall_hits", "x"}, {100, -1000.0, 1000.0}},
                    {"module Y, mm", {"reconstructed_forward_wall_hits", "y"}, {100, -1000.0, 1000.0}});

  Variable hit_distance( "hit_distance", {{"reconstructed_forward_wall_hits", "time"},
                                          {"reconstructed_forward_wall_hits", "beta"}},
                         [](const std::vector<double>& vars){
                           return vars.at(0)*vars.at(1) * 299'792'458e-9;
                         });
  Variable eta( "eta", {{"reconstructed_forward_wall_hits", "x"},
                        {"reconstructed_forward_wall_hits", "y"},
                        {"reconstructed_forward_wall_hits", "z"}},
                [](const std::vector<double>& vars){
                  auto rT =  sqrt(vars.at(0)*vars.at(0)+vars.at(1)*vars.at(1));
                  auto theta = atan2( rT, vars.at(2));
                  auto eta = -log( tan(theta/2) );
                  return eta;
                });
  qa_manager->AddH2({"distance, [m]", hit_distance, {500, 5.05, 5.15}},
                    {"Wall Channel", module_id, {304, 0.0, 304.0}});
  Cuts *inner_modules = new Cuts("inner modules", {{{"reconstructed_forward_wall_hits","ring"}, 0.9, 5.1}});
  Cuts *medium_modules = new Cuts("medium modules", {{{"reconstructed_forward_wall_hits","ring"}, 5.9, 7.1}});
  Cuts *perip_modules = new Cuts("peripheral modules", {{{"reconstructed_forward_wall_hits","ring"}, 7.9, 10.1}});

  qa_manager->AddH2({"#eta", eta, {325, 0, 5.90}},
                    {"Wall Channel", module_id, {304, 0.0, 304.0}});
  qa_manager->AddH2({"#eta", eta, {325, 2.65, 5.90}},
                    {"Wall Channel", module_id, {304, 0.0, 304.0}}, inner_modules);
  qa_manager->AddH2({"#eta", eta, {325, 2.65, 5.90}},
                    {"Wall Channel", module_id, {304, 0.0, 304.0}}, medium_modules);
  qa_manager->AddH2({"#eta", eta, {325, 2.65, 5.90}},
                    {"Wall Channel", module_id, {304, 0.0, 304.0}}, perip_modules);
  qa_manager->AddH2({"module X, mm", {"reconstructed_forward_wall_hits", "x"}, {100, -1000.0, 1000.0}},
                    {"module Y, mm", {"reconstructed_forward_wall_hits", "y"}, {100, -1000.0, 1000.0}}, inner_modules);
  qa_manager->AddH2({"module X, mm", {"reconstructed_forward_wall_hits", "x"}, {100, -1000.0, 1000.0}},
                    {"module Y, mm", {"reconstructed_forward_wall_hits", "y"}, {100, -1000.0, 1000.0}}, medium_modules);
  qa_manager->AddH2({"module X, mm", {"reconstructed_forward_wall_hits", "x"}, {100, -1000.0, 1000.0}},
                    {"module Y, mm", {"reconstructed_forward_wall_hits", "y"}, {100, -1000.0, 1000.0}}, perip_modules);
}

void AddSimDataQA(QA::Task* qa_manager, double beam_y) {
  qa_manager->AddH1({"b, fm", {"sim_header", "impact_parameter"}, {110, 0.0, 11.0}});
  qa_manager->AddProfile({"TOF-RPC hits centrality (%)", {"event_header", "selected_tof_rpc_hits_centrality"}, {20, 0.0, 100.0}},
                         {"b, fm", {"sim_header", "impact_parameter"}, {110, 0.0, 11.0}});
  qa_manager->AddH1({"#Psi_{RP}, rad", {"sim_header", "reaction_plane"}, {500, 0.0, 6.29}});

  qa_manager->AddH1({"mass, [#frac{GeV}{c}", {"sim_tracks", "mass"}, {500, 0.0, 10.0}});


  Variable y_cm("y_cm", {{"sim_tracks", "rapidity"}},
                [beam_y](const std::vector<double> &vars){
                  return vars.at(0)-beam_y;
                });
  Variable theta( "theta", {{"sim_tracks", "eta"}},
                  []( const std::vector<double>& vars ){
                    auto eta = vars.at(0);
                    return 2*atan( exp( -eta ) );
                  } );

  Cuts *protons = new Cuts("protons",
                           {{{"sim_tracks", "pid"}, 2212. - 0.5, 2212. + 0.5},
                            {{"sim_tracks", "is_primary"}, 1. - 0.5, 1. + 0.5}});

  Variable gen_y_cm("gen_y_{cm}", {{"sim_tracks", "rapidity"}},
                    [beam_y](const std::vector<double> &vars){
                      return vars.at(0)-beam_y;
                    });
  Variable reco_y_cm("y_{cm}", {{"mdc_vtx_tracks", "rapidity"}},
                     [beam_y](const std::vector<double> &vars){
                       return vars.at(0)-beam_y;
                     });
  Variable rapidity_error("rapidity_error", {{"sim_tracks", "rapidity"},
                                             {"mdc_vtx_tracks", "rapidity"}},
                          [](const std::vector<double> &vars){
                            return vars.at(1)-vars.at(0);
                          });

  Variable momentum_resolution( "p_resolution", {{"sim_tracks", "p"}, {"mdc_vtx_tracks", "p"}},
                                [](const std::vector<double> &vars){
                                  return (vars.at(0)-vars.at(1))/vars.at(0)*100.0;
                                });
  Cuts *fw_protons = new Cuts("fw_protons",
                                       {{{"sim_tracks", "pid"}, 2212. - 0.5, 2212. + 0.5},
                                        {{"sim_tracks", "is_primary"}, 1. - 0.5, 1. + 0.5},
                                        {{"sim_tracks", "eta"},  2.68, 5.38}});
  double pt_axis[] = {0, 0.29375, 0.35625, 0.41875, 0.48125, 0.54375, 0.61875, 0.70625, 0.81875, 1.01875, 2.0};

  qa_manager->AddH1({"#phi, rad", {"sim_tracks", "phi"}, {350, -3.5, 3.5}});
  qa_manager->AddH2({"y_{cm}", gen_y_cm, {200, -1.0, 1.0}},
                    {"pt_{p}, #frac{GeV}{c}", {"sim_tracks", "pT"}, {200, 0.0, 2.0}});

  qa_manager->AddH2({"y_{cm}", gen_y_cm, {23, -0.75, 1.55}},
      {"pt_{p}, #frac{GeV}{c}", {"sim_tracks", "pT"}, {10, pt_axis}}, fw_protons);

  qa_manager->AddH2({"GEN y_{cm}", gen_y_cm, {200, -1.0, 1.0}},
                    {"RECO y_{cm}", reco_y_cm, {200, -1.0, 1.0}}, protons);

  qa_manager->AddH2({"GEN p [GeV/c]", {"sim_tracks", "p"}, {300, 0.0, 3.0}},
                    {"RECO p [GeV/c]", {"mdc_vtx_tracks", "p"}, {300, 0.0, 3.0}}, protons);

  qa_manager->AddH2({"GEN p_{T} [GeV/c]", {"sim_tracks", "pT"}, {200, 0.0, 2.0}},
                    {"RECO p_{T} [GeV/c]", {"mdc_vtx_tracks", "pT"}, {200, 0.0, 2.0}}, protons);

  qa_manager->AddH2({"GEN #varphi [GeV/c]", {"sim_tracks", "phi"}, {315, -3.15, 3.15}},
                    {"RECO #varphi [GeV/c]", {"mdc_vtx_tracks", "phi"}, {315, -3.15, 3.15}},protons);

  qa_manager->AddProfile({"GEN p, [GeV/c]", {"sim_tracks", "p"}, {150, 0.0, 3.0}},
                         {"#frac{|p_{g}-p_{r}|}{p_{g}}, (%)", momentum_resolution, {100, 0.0, 100.5}}, protons);

  Variable protonidity(
      "protonidity", {{"sim_tracks","p"}, {"sim_tracks","pz"}},
      [](std::vector<double> &var) {
        auto E = sqrt( var.at(0)*var.at(0) + 0.938*0.938 );
        auto y = 0.5*( log( E + var.at(1) ) - log( E - var.at(1) ) ) - 0.74;
        return y; });

  qa_manager->AddH2({"y-y_{cm}", y_cm, {200, -1.0, 1.0}},
                    {"pt, #frac{GeV}{c}", {"sim_tracks", "pT"}, {200, 0.0, 2.5}});
  qa_manager->AddH2({"y{p}", protonidity, {200, -1.0, 1.0}},
                    {"pt, #frac{GeV}{c}", {"sim_tracks", "pT"}, {200, 0.0, 2.5}});
  qa_manager->AddH2({"p, #frac{GeV}{c}", {"sim_tracks", "p"}, {250, 0.0, 5.0}},
                    {"#eta", {"sim_tracks", "eta"}, {250, 0.0, 2.5}});
  qa_manager->AddH2({"#eta", {"sim_tracks", "eta"}, {250, 0.0, 2.5}},
                    {"pt, #frac{GeV}{c}", {"sim_tracks", "pT"}, {250, 0.0, 2.5}});
  qa_manager->AddH2({"y-y_{cm}", y_cm, {200, -1.0, 1.0}},
                    {"#phi, [rad]", {"sim_tracks", "phi"}, {350, -3.5, 3.5}});
  qa_manager->AddH2({"#phi, [rad]", {"sim_tracks", "phi"}, {315, -3.15, 3.15}},
                    {"#theta [rad]", theta, {170, 0.0, 1.7}});
  qa_manager->AddH2({"p, #frac{GeV}{c}", {"mdc_vtx_tracks", "p"}, {250, 0.0, 5.0}},
                    {"#phi, [rad]", {"mdc_vtx_tracks", "phi"}, {315, -3.15, 3.15}});
}

void AddSimParticlesQA(QA::Task* qa_manager, int pdg_code, double beam_y){
  Cuts *particle = new Cuts(std::to_string(pdg_code), {SimpleCut({"sim_tracks", "pid"}, pdg_code)});

  qa_manager->AddH1({"p_{T}, #frac{GeV}{c}", {"sim_tracks", "pT"}, {500, 0.0, 2.5}}, particle);
  qa_manager->AddH1({"#phi, rad", {"sim_tracks", "phi"}, {350, -3.5, 3.5}}, particle);

  Variable y_cm("y_cm", {{"sim_tracks", "rapidity"}},
                [beam_y](const std::vector<double> &vars){
                  return vars.at(0)-beam_y;
                });
  Variable theta( "theta", {{"sim_tracks", "eta"}},
                  []( const std::vector<double>& vars ){
                    auto eta = vars.at(0);
                    return 2*atan( exp( -eta ) );
                  } );

  Variable protonidity(
      "protonidity", {{"sim_tracks","p"}, {"sim_tracks","pz"}},
      [](std::vector<double> &var) {
        auto E = sqrt( var.at(0)*var.at(0) + 0.938*0.938 );
        auto y = 0.5*( log( E + var.at(1) ) - log( E - var.at(1) ) ) - 0.74;
        return y; });

  qa_manager->AddH2({"y-y_{cm}", y_cm, {200, -1.0, 1.0}},
                    {"pt, #frac{GeV}{c}", {"sim_tracks", "pT"}, {200, 0.0, 2.5}},
                    particle);
  qa_manager->AddH2({"y{p}", protonidity, {200, -1.0, 1.0}},
                    {"pt, #frac{GeV}{c}", {"sim_tracks", "pT"}, {200, 0.0, 2.5}},
                    particle);
  qa_manager->AddH2({"p, #frac{GeV}{c}", {"sim_tracks", "p"}, {250, 0.0, 5.0}},
                    {"#eta", {"sim_tracks", "eta"}, {250, 0.0, 2.5}},
                    particle);
  qa_manager->AddH2({"#eta", {"sim_tracks", "eta"}, {250, 0.0, 2.5}},
                    {"pt, #frac{GeV}{c}", {"sim_tracks", "pT"}, {250, 0.0, 2.5}},
                    particle);
  qa_manager->AddH2({"y-y_{cm}", y_cm, {200, -1.0, 1.0}},
                    {"#phi, [rad]", {"sim_tracks", "phi"}, {350, -3.5, 3.5}},
                    particle);
  qa_manager->AddH2({"#phi_{TRUE}, [rad]", {"sim_tracks", "phi"}, {350, -3.5, 3.5}},
                    {"#phi_{REC}, [rad]", {"mdc_vtx_tracks", "phi"}, {350, -3.5, 3.5}},
                    particle);
  qa_manager->AddH2({"p{T} TRUE [GeV/c]", {"sim_tracks", "pT"}, {250, 0.0, 2.5}},
                    {"p{T} REC [GeV/c]", {"mdc_vtx_tracks", "pT"}, {250, 0.0, 2.5}},
                    particle);
  qa_manager->AddH2({"y TRUE", {"sim_tracks", "rapidity"}, {100, 0.0, 2.0}},
                    {"y REC", {"mdc_vtx_tracks", "rapidity"}, {100, 0.0, 2.0}},
                    particle);
  qa_manager->AddH2({"#phi_{TRUE}, [rad]", {"sim_tracks", "phi"}, {350, -3.5, 3.5}},
                    {"#phi_{OUT}, [rad]", {"mdc_vtx_tracks", "phi_out"}, {350, -3.5, 3.5}},
                    particle);
  qa_manager->AddH2({"#phi, [rad]", {"sim_tracks", "phi"}, {315, -3.15, 3.15}},
                    {"#theta [rad]", theta, {315, 0.0, 3.15}},
                    particle);
  qa_manager->AddH2({"p, #frac{GeV}{c}", {"sim_tracks", "p"}, {250, 0.0, 5.0}},
                    {"#phi, [rad]", {"sim_tracks", "phi"}, {315, -3.15, 3.15}}, particle);
}

}
