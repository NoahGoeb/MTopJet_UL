#pragma once
#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/Utils.h"
#include "UHH2/core/include/PFParticle.h"
#include "UHH2/common/include/TTbarGen.h"

#include <iostream>
#include <math.h>
#include <vector>

#include "TH1F.h"
#include "TH2F.h"

using namespace std;

class GenHists: public uhh2::Hists {
public:
  // use the same constructor arguments as Hists for forwarding:
  GenHists(uhh2::Context & ctx, const std::string & dirname, const std::string & jetname);

  virtual void fill(const uhh2::Event & ev) override;

protected:
    TH1F *GenJetMass;
    TH1F *GenJetNumber;

    TH1F *GenJetTau1, *GenJetTau2, *GenJetTau3, *GenJetTau4;

    TH1F *GenJetTau2Tau1, *GenJetTau3Tau2, *GenJetTau3Tau1, *GenJetTau4Tau3, *GenJetTau4Tau2, *GenJetTau4Tau1;

    uhh2::Event::Handle<std::vector<GenTopJet>>h_jets;

    bool debug;
};
