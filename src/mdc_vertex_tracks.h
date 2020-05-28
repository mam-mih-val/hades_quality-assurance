//
// Created by mikhail on 5/28/20.
//

#ifndef QUALITY_ASSURANCE_SRC_CMAKE_BUILD_DEBUG_MDC_VERTEX_TRACKS_H_
#define QUALITY_ASSURANCE_SRC_CMAKE_BUILD_DEBUG_MDC_VERTEX_TRACKS_H_
#include <Manager.h>

class MdcVertexTracks {
public:
  static void AddVertexTrackQa(QA::Manager& qa_manager){
    qa_manager.AddEntry( {"mdc_vtx_tracks", "pz"}, {250, 0.0, 2.5} );
//    qa_manager.AddEntry( {"#chi^{2}_{RK}", "mdc_vtx_tracks", "chi2"}, {250, 0.0, 250} );
//    qa_manager.AddEntry( {"DCA_{XY}", "mdc_vtx_tracks", "dca_xy"}, {300, 0.0, 3} );
//    qa_manager.AddEntry( {"DCA_{Z}", "mdc_vtx_tracks", "dca_z"}, {100, -150., 50} );
//
//    Cuts* protons = new Cuts("protons", "mdc_vtx_tracks");
//    protons->AddCut({"geant_pid", 14.-0.5, 14.+0.5});
//
//    Cuts* pions_plus = new Cuts("pions_plus", "mdc_vtx_tracks");
//    pions_plus->AddCut({"geant_pid", 8.-0.5, 8.+0.5});
//
//    Cuts* pions_minus = new Cuts("pions_minus", "mdc_vtx_tracks");
//    pions_minus->AddCut({"geant_pid", 9.-0.5, 9.+0.5});
//
//    qa_manager.AddEntry2D({{"pt_{p}, GeV/c", "mdc_vtx_tracks", "pT"},
//                           {"y_{p}", "mdc_vtx_tracks", "rapidity"}}, {
//                              {250, 0.0, 2.5}, {200, 0.0, 2.0}}, protons );
//    qa_manager.AddEntry2D({{"pt_{#pi+}, GeV/c", "mdc_vtx_tracks", "pT"},
//                           {"y_{#pi+}", "mdc_vtx_tracks", "rapidity"}}, {
//                              {250, 0.0, 2.5}, {200, 0.0, 2.0}}, pions_plus );
//    qa_manager.AddEntry2D({{"pt_{#pi-}, GeV/c", "mdc_vtx_tracks", "pT"},
//                           {"y_{#pi-}", "mdc_vtx_tracks", "rapidity"}}, {
//                              {250, 0.0, 2.5}, {200, 0.0, 2.0}}, pions_minus );
  }
};

#endif // QUALITY_ASSURANCE_SRC_CMAKE_BUILD_DEBUG_MDC_VERTEX_TRACKS_H_
