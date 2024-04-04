#pragma once
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/TTbarGen.h"
#include "UHH2/core/include/GenTopJet.h"

#include <iostream>

using namespace std;
using namespace uhh2;

class RemoveLepton: public uhh2::AnalysisModule{

 public:
   RemoveLepton(uhh2::Context & ctx, const std::string & name_jet);
   virtual bool process(uhh2::Event & ) override;

 private:
   uhh2::Event::Handle<std::vector<TopJet>>h_topjets;
};


class RemoveLeptonGen: public uhh2::AnalysisModule{

 public:
   RemoveLeptonGen(uhh2::Context & ctx, const std::string & name_jet);
   virtual bool process(uhh2::Event & ) override;

 private:
   uhh2::Event::Handle<std::vector<GenTopJet>>h_topjets;
   uhh2::Event::Handle<TTbarGen> h_ttbargen;
};
