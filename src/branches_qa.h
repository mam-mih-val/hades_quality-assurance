//
// Created by mikhail on 8/11/20.
//

#ifndef QUALITY_ASSURANCE_SRC_BRANCHES_QA_H_
#define QUALITY_ASSURANCE_SRC_BRANCHES_QA_H_

#include <Manager.hpp>
#include <Task.hpp>
#include "AnalysisTree/Variable.hpp"
#include <AnalysisTree/Cuts.hpp>

namespace AnalysisTree{

void AddEventHeaderQA(QA::Task* qa_manager);

void AddMdcVtxTracksQA(QA::Task* qa_manager, double beam_y=1.48);

void AddMetaHitsQA(QA::Task* qa_manager);

void AddParticleQA(QA::Task* qa_manager, int pdg_code, double beam_y=1.48);

void AddForwardWallHitsQA(QA::Task* qa_manager);

void AddSimDataQA(QA::Task* qa_manager, double beam_y=1.48);

}

#endif // QUALITY_ASSURANCE_SRC_BRANCHES_QA_H_
