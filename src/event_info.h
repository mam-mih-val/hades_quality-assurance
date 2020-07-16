//
// Created by mikhail on 6/1/20.
//

#ifndef QUALITY_ASSURANCE_SRC_EVENT_INFO_H_
#define QUALITY_ASSURANCE_SRC_EVENT_INFO_H_
#include <Manager.h>

namespace AnalysisTree {
class EventInfo {
public:
  static void Add(QA::Task* qa_manager) {
    Cuts *pt3 = new Cuts("PT3");
    pt3->AddCut({{"event_header","physical_trigger_3"}, 1. - 0.5, 1. + 0.5});
    qa_manager->AddEntry({"VTX_{Z}, mm", "event_header", "vtx_z"},
                        {100, -80.0, 20.0});

    qa_manager->AddEntry({"selected META hits", "event_header",
                         "selected_tof_rpc_hits"},
                        {250, 0.0, 250.0});

    qa_manager->AddEntry2D({{"VTX_{X}, mm", "event_header", "vtx_x"},
                           {"VTX_{Y}, mm", "event_header", "vtx_y"}},
                          {{100, -5.0, 5.0}, {100, -5.0, 5.0}});

    qa_manager->AddEntry2D(
        {{"N hits META", "event_header", "selected_tof_rpc_hits"},
         {"N hits MDC", "event_header", "selected_mdc_tracks"}},
        {{250, 0.0, 250.0}, {100, 0.0, 100.0}});

    qa_manager->AddEntry2D(
        {{"N hits META", "event_header", "selected_tof_rpc_hits"},
         {"FW signal", "event_header", "fw_adc"}},
        {{250, 0.0, 250.0}, {200, 0.0, 100.0}});

    qa_manager->AddEntry2D(
        {{"N hits MDC", "event_header", "selected_mdc_tracks"},
         {"FW signal", "event_header", "fw_adc"}},
        {{100, 0.0, 100.0}, {200, 0.0, 100.0}});
  }
};
} // namespace AnalysisTree
#endif // QUALITY_ASSURANCE_SRC_EVENT_INFO_H_
