//
// Created by mikhail on 8/11/20.
//

#ifndef QUALITY_ASSURANCE_SRC_BRANCHES_QA_H_
#define QUALITY_ASSURANCE_SRC_BRANCHES_QA_H_

#include "AnalysisTreeQA/Manager.hpp"
#include "AnalysisTreeQA/Task.hpp"
#include "AnalysisTree/Variable.hpp"
#include <AnalysisTree/Cuts.hpp>

namespace AnalysisTree{

void AddEventHeaderQA(QA::Task* qa_manager, bool is_mc=false);

void AddMdcVtxTracksQA(QA::Task* qa_manager, double beam_y=1.48);

void AddMetaHitsQA(QA::Task* qa_manager);

void AddParticleQA(QA::Task*var, int pdg_code, double beam_y=1.48);

void AddForwardWallHitsQA(QA::Task* qa_manager, bool is_ms=false);

void AddReconstructedForwardWallHitsQA(QA::Task* qa_manager);

void AddSimDataQA(QA::Task* qa_manager, double beam_y=1.48);

void AddSimParticlesQA(QA::Task* qa_manager, int pdg_code, double beam_y=1.48);

}

#endif // QUALITY_ASSURANCE_SRC_BRANCHES_QA_H_
