//
// Created by mikhail on 5/29/20.
//

#ifndef QUALITY_ASSURANCE_SRC_META_HITS_H_
#define QUALITY_ASSURANCE_SRC_META_HITS_H_
#include <Manager.h>

namespace AnalysisTree {
class MetaHits {
public:
  static void Add(QA::Task* qa_manager) {
    qa_manager->AddEntry({"META match radius, mm", "meta_hits", "match_radius"},
                        {100, 0.0, 40.0});
    Cuts *protons = new Cuts("protons");
    protons->AddCut({{"mdc_vtx_tracks","geant_pid"}, 14. - 0.5, 14. + 0.5});

    Cuts *pions_plus = new Cuts("pions_plus");
    pions_plus->AddCut({{"mdc_vtx_tracks","geant_pid"}, 8. - 0.5, 8. + 0.5});

    Cuts *pions_minus = new Cuts("pions_minus");
    pions_minus->AddCut({{"mdc_vtx_tracks","geant_pid"}, 9. - 0.5, 9. + 0.5});

    Cuts *kaons_plus = new Cuts("kaons_plus");
    kaons_plus->AddCut({{"mdc_vtx_tracks","geant_pid"}, 11. - 0.5, 11. + 0.5});

    Cuts *kaons_minus = new Cuts("kaons_minus");
    kaons_minus->AddCut({{"mdc_vtx_tracks","geant_pid"}, 12. - 0.5, 12. + 0.5});

    Variable charged_p(
        "p #times z, [z #times #frac{GeV}{c}]", "mdc_vtx_tracks", {"charge", "p"},
        [](std::vector<double> &var) { return var.at(0) * var.at(1); });

    Variable sqrt_m2("mass META, [#frac{GeV}{c}^{2}]", "meta_hits", {"mass2"},
                     [](std::vector<double> &var) { return sqrtf(var.at(0)); });
    Variable charged_mass(
        "m*z META, [z*#frac{GeV}{c}^{2}]", "meta_hits", {"mass2", "charge"},
        [](std::vector<double> &var) { return sqrtf(var.at(0)) * var.at(1); });

    // momentum vs energy loss
    qa_manager->AddEntry2D({charged_p, {"#frac{dE}{dx} META", "meta_hits", "dEdx"}},
                          {{200, -2.0, 5.0}, {200, 0.0, 20.0}});
    qa_manager->AddEntry2D({charged_p, {"#frac{dE}{dx} META", "meta_hits", "dEdx"}},
                          {{200, -2.0, 5.0}, {200, 0.0, 20.0}}, protons);
    qa_manager->AddEntry2D({charged_p, {"#frac{dE}{dx} META", "meta_hits", "dEdx"}},
                          {{200, -2.0, 5.0}, {200, 0.0, 20.0}}, pions_plus);
    qa_manager->AddEntry2D({charged_p, {"#frac{dE}{dx} META", "meta_hits", "dEdx"}},
                          {{200, -2.0, 5.0}, {200, 0.0, 20.0}}, pions_minus);
    qa_manager->AddEntry2D({charged_p, {"#frac{dE}{dx} META", "meta_hits", "dEdx"}},
                          {{200, -2.0, 5.0}, {200, 0.0, 20.0}}, kaons_plus);
    qa_manager->AddEntry2D({charged_p, {"#frac{dE}{dx} META", "meta_hits", "dEdx"}},
                          {{200, -2.0, 5.0}, {200, 0.0, 20.0}}, kaons_minus);

    qa_manager->AddEntry2D(
        {charged_mass, {"pt, [#frac{GeV}{c}]", "mdc_vtx_tracks", "pT"}},
        {{200, -1.0, 10.0}, {250, 0.0, 2.5}});
    qa_manager->AddEntry2D(
        {charged_mass, {"pt, [#frac{GeV}{c}]", "mdc_vtx_tracks", "pT"}},
        {{200, -1.0, 10.0}, {250, 0.0, 2.5}}, protons);
    qa_manager->AddEntry2D(
        {charged_mass, {"pt, [#frac{GeV}{c}]", "mdc_vtx_tracks", "pT"}},
        {{200, -1.0, 10.0}, {250, 0.0, 2.5}}, kaons_plus);
    qa_manager->AddEntry2D(
        {charged_mass, {"pt, [#frac{GeV}{c}]", "mdc_vtx_tracks", "pT"}},
        {{200, -1.0, 10.0}, {250, 0.0, 2.5}}, kaons_minus);
    qa_manager->AddEntry2D(
        {charged_mass, {"pt, [#frac{GeV}{c}]", "mdc_vtx_tracks", "pT"}},
        {{200, -1.0, 10.0}, {250, 0.0, 2.5}}, pions_plus);
    qa_manager->AddEntry2D(
        {charged_mass, {"pt, [#frac{GeV}{c}]", "mdc_vtx_tracks", "pT"}},
        {{200, -1.0, 10.0}, {250, 0.0, 2.5}}, pions_minus);
  }
};
} // namespace AnalysisTree
#endif // QUALITY_ASSURANCE_SRC_META_HITS_H_
