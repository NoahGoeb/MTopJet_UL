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
#include <UHH2/common/include/Utils.h>

#include <UHH2/MTopJet_UL/include/MTopJetUtils.h>

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

  ////////////////////////////////////////////////////////////////

  class TwoDCut1 : public Selection {

  public:
    explicit TwoDCut1(float min_deltaR, float min_pTrel): min_deltaR_(min_deltaR), min_pTrel_(min_pTrel) {}
    virtual bool passes(const Event&) override;

  private:
    float min_deltaR_, min_pTrel_;
  };

  ////////////////////////////////////////////////////////////////

  class BadHCALSelection: public uhh2::Selection {
  public:
    BadHCALSelection(uhh2::Context &ctx, long int seed = 123456789);
    virtual bool passes(const uhh2::Event &event) override;

  private:
    TRandom *m_rng;
    long int m_seed;
    Year year;
    int m_runnumber = 319077;
    double m_lumi_ratio = 0.64844705699; // (Run 319077(17.370008 pb-1) + Run C + Run D) / all 2018

    double m_interval_eta = -1.3;
    double m_interval_phi_low = -1.57;
    double m_interval_phi_high = -0.87;

  };

  ////////////////////////////////////////////////////////////////

}
