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

    uhh2::Event::Handle<std::vector<GenTopJet>>h_jets;

    bool debug;
};
