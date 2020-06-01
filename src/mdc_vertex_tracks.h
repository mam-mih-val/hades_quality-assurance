//
// Created by mikhail on 5/28/20.
//

#ifndef QUALITY_ASSURANCE_SRC_CMAKE_BUILD_DEBUG_MDC_VERTEX_TRACKS_H_
#define QUALITY_ASSURANCE_SRC_CMAKE_BUILD_DEBUG_MDC_VERTEX_TRACKS_H_
#include <Manager.h>

class MdcVertexTracks {
public:
  MdcVertexTracks() = delete;
  static void Add(QA::Manager& qa_manager){
    qa_manager.AddEntry( {"Vertex tracks p_{T}, GeV/c","mdc_vtx_tracks", "pT"}, {250, 0.0, 2.5} );
    qa_manager.AddEntry( {"#chi^{2}_{RK}", "mdc_vtx_tracks", "chi2"}, {100, 0.0, 250} );
    qa_manager.AddEntry( {"DCA_{XY}", "mdc_vtx_tracks", "dca_xy"}, {300, 0.0, 3} );
    qa_manager.AddEntry( {"DCA_{Z}", "mdc_vtx_tracks", "dca_z"}, {100, -150., 50} );

    Cuts* protons = new Cuts("protons", "mdc_vtx_tracks");
    protons->AddCut({"geant_pid", 14.-0.5, 14.+0.5});

    Cuts* pions_plus = new Cuts("pions_plus", "mdc_vtx_tracks");
    pions_plus->AddCut({"geant_pid", 8.-0.5, 8.+0.5});

    Cuts* pions_minus = new Cuts("pions_minus", "mdc_vtx_tracks");
    pions_minus->AddCut({"geant_pid", 9.-0.5, 9.+0.5});

    Cuts* kaons_plus = new Cuts("kaons_plus", "mdc_vtx_tracks");
    kaons_plus->AddCut({"geant_pid", 11.-0.5, 11.+0.5});

    Cuts* kaons_minus = new Cuts("kaons_minus", "mdc_vtx_tracks");
    kaons_minus->AddCut({"geant_pid", 12.-0.5, 12.+0.5});


    Variable charge_p("p #times z, [z #times Gev/c]", "mdc_vtx_tracks", {"charge", "p"},
                      []( std::vector<double>& var ){
                        return var.at(0)*var.at(1);
                      });

    qa_manager.AddEntry2D({{"pt_{p}, GeV/c", "mdc_vtx_tracks", "pT"},
                           {"y_{p}", "mdc_vtx_tracks", "rapidity"}}, {
                              {250, 0.0, 2.5}, {200, 0.0, 2.0}}, protons );
    qa_manager.AddEntry2D({{"pt_{#pi+}, GeV/c", "mdc_vtx_tracks", "pT"},
                           {"y_{#pi+}", "mdc_vtx_tracks", "rapidity"}}, {
                              {250, 0.0, 2.5}, {200, 0.0, 2.0}}, pions_plus );
    qa_manager.AddEntry2D({{"pt_{#pi-}, GeV/c", "mdc_vtx_tracks", "pT"},
                           {"y_{#pi-}", "mdc_vtx_tracks", "rapidity"}}, {
                              {250, 0.0, 2.5}, {200, 0.0, 2.0}}, pions_minus );

    qa_manager.AddEntry2D({charge_p,
                           {"dE/dE MDC", "mdc_vtx_tracks", "dEdx"}}, {
                              {200, -2.0, 5.0}, {200, 0.0, 20.0}});
    qa_manager.AddEntry2D({charge_p,
                           {"dE/dE MDC", "mdc_vtx_tracks", "dEdx"}}, {
                              {200, -2.0, 5.0}, {200, 0.0, 20.0}}, protons);
    qa_manager.AddEntry2D({charge_p,
                           {"dE/dE MDC", "mdc_vtx_tracks", "dEdx"}}, {
                              {200, -2.0, 5.0}, {200, 0.0, 20.0}}, pions_plus);
    qa_manager.AddEntry2D({charge_p,
                           {"dE/dE MDC", "mdc_vtx_tracks", "dEdx"}}, {
                              {200, -2.0, 5.0}, {200, 0.0, 20.0}}, pions_minus);
    qa_manager.AddEntry2D({charge_p,
                           {"dE/dE MDC", "mdc_vtx_tracks", "dEdx"}}, {
                              {200, -2.0, 5.0}, {200, 0.0, 20.0}}, kaons_plus);
    qa_manager.AddEntry2D({charge_p,
                           {"dE/dE MDC", "mdc_vtx_tracks", "dEdx"}}, {
                              {200, -2.0, 5.0}, {200, 0.0, 20.0}}, kaons_minus);
  }
};

#endif // QUALITY_ASSURANCE_SRC_CMAKE_BUILD_DEBUG_MDC_VERTEX_TRACKS_H_
