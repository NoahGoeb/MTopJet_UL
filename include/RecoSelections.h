#pragma once

#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Selection.h>
#include <UHH2/core/include/Utils.h>
#include <UHH2/core/include/LorentzVector.h>

#include <UHH2/common/include/NSelections.h>
#include <UHH2/common/include/ReconstructionHypothesis.h>
#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>
#include <UHH2/common/include/ObjectIdUtils.h>
#include <UHH2/common/include/TopJetIds.h>
#include <UHH2/common/include/TTbarGen.h>

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <TRandom.h>
#include <TRandomGen.h>


namespace uhh2 {

  class METCut : public Selection {

  public:
    explicit METCut(float, float max_met=infinity);
    virtual bool passes(const Event&) override;

  private:
    float min_met_, max_met_;
  };

  ////////////////////////////////////////////////////////////////
  
  class ElectronEtaVeto : public Selection {

  public:
    explicit ElectronEtaVeto(double, double);
    virtual bool passes(const Event&) override;

  private:
    double lower, upper;
  };

}
