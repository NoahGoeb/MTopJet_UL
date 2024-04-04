#pragma once
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/TTbarGen.h"

#include "UHH2/common/include/Utils.h"
#include "UHH2/core/include/Jet.h"
#include "UHH2/core/include/TopJet.h"
#include "UHH2/core/include/GenJet.h"
#include "UHH2/core/include/GenParticle.h"
#include "UHH2/core/include/PFParticle.h"
#include "UHH2/core/include/AnalysisModule.h"

#include <vector>
#include <iostream>
#include <math.h>

using namespace std;
using namespace uhh2;


class CombineXCone{

 public:

  GenTopJet CreateTopJetFromSubjets_gen(vector<GenJet> subjets, double ptmin, double etamax);

};

class CombineXCone2_gen: public uhh2::AnalysisModule{
public:

  explicit CombineXCone2_gen(uhh2::Context &, bool, const std::string &, const std::string &);
  virtual bool process(uhh2::Event & ) override;

private:

  uhh2::Event::Handle<std::vector<GenTopJet>>h_GENxcone2hadjets;
  uhh2::Event::Handle<std::vector<GenTopJet>>h_GENxcone2lepjets;
  uhh2::Event::Handle<std::vector<GenTopJet>>h_GENfatjets;
  uhh2::Event::Handle<TTbarGen> h_ttbargen;
  bool isTTbar_;

};

class CombineXCone3_gen: public uhh2::AnalysisModule{
public:

  explicit CombineXCone3_gen(uhh2::Context &, bool, const std::string &, const std::string &);
  virtual bool process(uhh2::Event & ) override;

private:

  uhh2::Event::Handle<std::vector<GenTopJet>>h_GENxcone3hadjets;
  uhh2::Event::Handle<std::vector<GenTopJet>>h_GENxcone3lepjets;
  uhh2::Event::Handle<std::vector<GenTopJet>>h_GENfatjets;
  uhh2::Event::Handle<TTbarGen> h_ttbargen;
  bool isTTbar_;

};
