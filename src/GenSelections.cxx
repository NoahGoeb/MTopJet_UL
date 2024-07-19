#include <UHH2/MTopJet_UL/include/GenSelections.h>

#include "TLorentzVector.h"

uhh2::TTbarSemilep::TTbarSemilep(uhh2::Context& ctx):
h_ttbargen(ctx.get_handle<TTbarGen>("ttbargen")) {}

bool uhh2::TTbarSemilep::passes(const uhh2::Event& event){

  const auto & ttbargen = event.get(h_ttbargen);
  bool semilep = false;

  if(ttbargen.DecayChannel() == TTbarGen::e_muhad || ttbargen.DecayChannel() == TTbarGen::e_ehad) semilep = true;
  return semilep;
}

////////////////////////////////////////////////////////

uhh2::GenMuonSel::GenMuonSel(uhh2::Context& ctx, double ptmin_):
ptmin(ptmin_), h_ttbargen(ctx.get_handle<TTbarGen>("ttbargen")) {}

bool uhh2::GenMuonSel::passes(const uhh2::Event& event){
  const auto & ttbargen = event.get(h_ttbargen);
  bool pass = false;
  GenParticle lepton;
  if(ttbargen.IsSemiLeptonicDecay()){
    lepton = ttbargen.ChargedLepton();
    if((abs(lepton.pdgId()) == 13) && (lepton.pt() > ptmin)) pass = true;
  }
  return pass;
}

////////////////////////////////////////////////////////

uhh2::GenElecSel::GenElecSel(uhh2::Context& ctx, double ptmin_):
ptmin(ptmin_), h_ttbargen(ctx.get_handle<TTbarGen>("ttbargen")) {}

bool uhh2::GenElecSel::passes(const uhh2::Event& event){
  const auto & ttbargen = event.get(h_ttbargen);
  bool pass = false;
  GenParticle lepton;
  if(ttbargen.IsSemiLeptonicDecay()){
    lepton = ttbargen.ChargedLepton();
    if((abs(lepton.pdgId()) == 11) && (lepton.pt() > ptmin)) pass = true;
  }
  return pass;
}

////////////////////////////////////////////////////////

uhh2::LeadingJetPT_gen::LeadingJetPT_gen(uhh2::Context& ctx, const std::string & name, float ptcut):
h_jets(ctx.get_handle<std::vector<GenTopJet>>(name)),
ptcut_(ptcut) {}

bool uhh2::LeadingJetPT_gen::passes(const uhh2::Event& event){
  bool pass_jetpt = false;
  std::vector<GenTopJet> jets = event.get(h_jets);
  GenTopJet jet1;
  if(jets.size()>0){
    jet1 = jets.at(0);
    float pt = jet1.pt();
    if(pt > ptcut_) pass_jetpt = true;
  }
  return pass_jetpt;
}

////////////////////////////////////////////////////////

uhh2::LeadingJetPTRange_gen::LeadingJetPTRange_gen(uhh2::Context& ctx, const std::string & name, float ptmin, float ptmax):
h_jets(ctx.get_handle<std::vector<GenTopJet>>(name)),
ptmin_(ptmin),
ptmax_(ptmax) {}

bool uhh2::LeadingJetPTRange_gen::passes(const uhh2::Event& event){
  bool pass_jetptrange = false;
  std::vector<GenTopJet> jets = event.get(h_jets);
  GenTopJet jet1;
  if(jets.size()>0){
    jet1 = jets.at(0);
    float pt = jet1.pt();
    if(pt >= ptmin_ && pt < ptmax_) pass_jetptrange = true;
  }
  return pass_jetptrange;
}

////////////////////////////////////////////////////////

uhh2::JetPTCombined_gen::JetPTCombined_gen(uhh2::Context& ctx, const std::string & name, float pt):
h_jets(ctx.get_handle<std::vector<GenTopJet>>(name)),
pt_(pt){}

bool uhh2::JetPTCombined_gen::passes(const uhh2::Event& event){
  bool pass_jetptrange = false;
  std::vector<GenTopJet> jets = event.get(h_jets);
  TLorentzVector jet1_v4, jet2_v4, jet_v4_combined;
  GenTopJet jet1;
  float ptJet;
  if(jets.size()>1 && deltaR(jets.at(0), jets.at(1))<1.2) {
    jet1_v4.SetPxPyPzE(jets.at(0).v4().Px(), jets.at(0).v4().Py(), jets.at(0).v4().Pz(), jets.at(0).v4().E());
    jet2_v4.SetPxPyPzE(jets.at(1).v4().Px(), jets.at(1).v4().Py(), jets.at(1).v4().Pz(), jets.at(1).v4().E());

    jet_v4_combined = jet1_v4 + jet2_v4;
    
    if(jet_v4_combined.Pt() > pt_) pass_jetptrange = true;
  } else {
    jet1 = jets.at(0);
    ptJet = jet1.pt();
    if(ptJet >= pt_) pass_jetptrange = true;
  }
  return pass_jetptrange;
}

////////////////////////////////////////////////////////

uhh2::MassCut2_gen::MassCut2_gen(uhh2::Context& ctx, const std::string & hadname, const std::string & lepname):
h_hadjets(ctx.get_handle<std::vector<GenTopJet>>(hadname)),
h_lepjets(ctx.get_handle<std::vector<GenTopJet>>(lepname)),
h_ttbargen(ctx.get_handle<TTbarGen>("ttbargen")) {}

bool uhh2::MassCut2_gen::passes(const uhh2::Event& event){
  std::vector<GenTopJet> hadjets = event.get(h_hadjets);
  std::vector<GenTopJet> lepjets = event.get(h_lepjets);
  const auto & ttbargen = event.get(h_ttbargen);

  GenParticle lepton = ttbargen.ChargedLepton();
  bool is_semilep = ttbargen.IsSemiLeptonicDecay();

  LorentzVector jet1_v4, jet2_v4;
  bool pass_masscut = false;
  if(hadjets.size()>0 && lepjets.size()>0){
    jet1_v4 = hadjets.at(0).v4();
    if(is_semilep) jet2_v4 = lepjets.at(0).v4() + lepton.v4();
    else           jet2_v4 = lepjets.at(0).v4();
    if(jet1_v4.M() > jet2_v4.M()) pass_masscut = true;
  }
  return pass_masscut;
}

////////////////////////////////////////////////////////

uhh2::MassCut3_gen::MassCut3_gen(uhh2::Context& ctx, const std::string & hadname, const std::string & lepname, float dR):
h_hadjets(ctx.get_handle<std::vector<GenTopJet>>(hadname)),
h_lepjets(ctx.get_handle<std::vector<GenTopJet>>(lepname)),
h_ttbargen(ctx.get_handle<TTbarGen>("ttbargen")),
dR_(dR) {}

bool uhh2::MassCut3_gen::passes(const uhh2::Event& event) {
  std::vector<GenTopJet> hadjets = event.get(h_hadjets);
  std::vector<GenTopJet> lepjets = event.get(h_lepjets);
  const auto & ttbargen = event.get(h_ttbargen);

  GenParticle lepton = ttbargen.ChargedLepton();
  bool is_semilep = ttbargen.IsSemiLeptonicDecay();

  LorentzVector jet1_v4, jet2_v4;
  bool pass_masscut = false;
  if(hadjets.size()>0) jet1_v4 = hadjets.at(0).v4();
  if(hadjets.size()>1 && deltaR(hadjets.at(0), hadjets.at(1))<dR_) jet1_v4 = hadjets.at(0).v4() + hadjets.at(1).v4();
  if(hadjets.size()>0 && lepjets.size()>0) {
    if(is_semilep) jet2_v4 = lepjets.at(0).v4() + lepton.v4();
    else           jet2_v4 = lepjets.at(0).v4();
    if(jet1_v4.M() > jet2_v4.M()) pass_masscut = true;
  }
  return pass_masscut;
}

////////////////////////////////////////////////////////

uhh2::SubjetQuality_gen::SubjetQuality_gen(uhh2::Context& ctx, const std::string & name, float ptmin_, float etamax_):
h_jets(ctx.get_handle<std::vector<GenTopJet>>(name)),
ptmin(ptmin_),
etamax(etamax_){}

bool uhh2::SubjetQuality_gen::passes(const uhh2::Event& event){
  bool pass = true;
  std::vector<GenTopJet> jets = event.get(h_jets);
  if(jets.size() == 0) return false;
  auto subjets = jets.at(0).subjets();
  if(subjets.size() != 3) pass = false;
  for(auto subjet: subjets){
    if(subjet.pt() < ptmin) pass = false;
    if(fabs(subjet.eta()) > etamax) pass = false;
  }
  return pass;
}

////////////////////////////////////////////////////////

uhh2::NoNearJet_gen::NoNearJet_gen(uhh2::Context& ctx, const std::string & name, float dR_):
h_jets(ctx.get_handle<std::vector<GenTopJet>>(name)),
dR(dR_){}

bool uhh2::NoNearJet_gen::passes(const uhh2::Event& event){
  bool pass = true;
  std::vector<GenTopJet> jets = event.get(h_jets);
  if(jets.size() > 1) {
    if(deltaR(jets.at(0), jets.at(1)) < dR) {
      pass = false;
    }
  }
  return pass;
}

////////////////////////////////////////////////////////

uhh2::TopMatched_gen::TopMatched_gen(uhh2::Context& ctx, const std::string & name, float dR_):
h_jets(ctx.get_handle<std::vector<GenTopJet>>(name)),
h_ttbargen(ctx.get_handle<TTbarGen>("ttbargen")),
dR(dR_){}

bool uhh2::TopMatched_gen::passes(const uhh2::Event& event){
  bool pass = false;
  std::vector<GenTopJet> jets = event.get(h_jets);
  const auto & ttbargen = event.get(h_ttbargen);
  GenParticle top;
  if(ttbargen.IsTopHadronicDecay()) {
    top = ttbargen.Top();
  } else if(ttbargen.IsAntiTopHadronicDecay()) {
    top = ttbargen.Antitop();
  }
  if(jets.size() > 0) {
    if(deltaR(jets.at(0), top) < dR) {
      pass = true;
    }
  }
  return pass;
}

////////////////////////////////////////////////////////

uhh2::GluonMatched_gen::GluonMatched_gen(uhh2::Context& ctx, const std::string & name, float dR_):
h_jets(ctx.get_handle<std::vector<GenTopJet>>(name)),
dR(dR_){}

bool uhh2::GluonMatched_gen::passes(const uhh2::Event& event){
  bool pass = false;
  std::vector<GenTopJet> jets = event.get(h_jets);
  std::vector<GenParticle> gluons = outgoingGluons(event);
  if(jets.size() > 0 && gluons.size() > 0) {
    if(deltaR(jets.at(0), gluons.at(0)) < dR) {
      pass = true;
    }
  }
  return pass;
}

////////////////////////////////////////////////////////

uhh2::Tau32Cut_gen::Tau32Cut_gen(uhh2::Context& ctx, const std::string & name, float cut_):
h_jets(ctx.get_handle<std::vector<GenTopJet>>(name)),
cut(cut_){}

bool uhh2::Tau32Cut_gen::passes(const uhh2::Event& event){
  bool pass = false;
  std::vector<GenTopJet> jets = event.get(h_jets);
  if(jets.size() > 0 && jets.at(0).tau2() != 0) {
    if(jets.at(0).tau3()/jets.at(0).tau2() < cut) {
      pass = true;
    }
  }
  return pass;
}

////////////////////////////////////////////////////////

uhh2::Tau42Cut_gen::Tau42Cut_gen(uhh2::Context& ctx, const std::string & name, float cut_):
h_jets(ctx.get_handle<std::vector<GenTopJet>>(name)),
cut(cut_){}

bool uhh2::Tau42Cut_gen::passes(const uhh2::Event& event){
  bool pass = false;
  std::vector<GenTopJet> jets = event.get(h_jets);
  if(jets.size() > 0 && jets.at(0).tau2() != 0) {
    if(jets.at(0).tau4()/jets.at(0).tau2() < cut) {
      pass = true;
    }
  }
  return pass;
}

////////////////////////////////////////////////////////

uhh2::GroomedTau32Cut_gen::GroomedTau32Cut_gen(uhh2::Context& ctx, const std::string & name, float cut_):
h_jets(ctx.get_handle<std::vector<GenTopJet>>(name)),
cut(cut_){}

bool uhh2::GroomedTau32Cut_gen::passes(const uhh2::Event& event){
  bool pass = false;
  std::vector<GenTopJet> jets = event.get(h_jets);
  if(jets.size() > 0 && jets.at(0).tau2_groomed() != 0) {
    if(jets.at(0).tau3_groomed()/jets.at(0).tau2_groomed() < cut) {
      pass = true;
    }
  }
  return pass;
}

////////////////////////////////////////////////////////

uhh2::GroomedTau42Cut_gen::GroomedTau42Cut_gen(uhh2::Context& ctx, const std::string & name, float cut_):
h_jets(ctx.get_handle<std::vector<GenTopJet>>(name)),
cut(cut_){}

bool uhh2::GroomedTau42Cut_gen::passes(const uhh2::Event& event){
  bool pass = false;
  std::vector<GenTopJet> jets = event.get(h_jets);
  if(jets.size() > 0 && jets.at(0).tau2_groomed() != 0) {
    if(jets.at(0).tau4_groomed()/jets.at(0).tau2_groomed() < cut) {
      pass = true;
    }
  }
  return pass;
}

////////////////////////////////////////////////////////

uhh2::FullyMerged_Matched::FullyMerged_Matched(uhh2::Context& ctx, const std::string & name, unsigned int index_):
h_jets(ctx.get_handle<std::vector<GenTopJet>>(name)),
h_ttbargen(ctx.get_handle<TTbarGen>("ttbargen")),
index(index_) {}

bool uhh2::FullyMerged_Matched::passes(const uhh2::Event& event){
  
  bool matched = true;
  std::vector<GenTopJet> jets = event.get(h_jets);
  std::vector<GenJet> subjets;
  if (jets.size() > index) subjets = jets.at(index).subjets();
  else return false;
  const auto & ttbargen = event.get(h_ttbargen);

  GenParticle bot, q1, q2;
  if(ttbargen.IsTopHadronicDecay()) {
    bot = ttbargen.bTop();
    q1 = ttbargen.Wdecay1();
    q2 = ttbargen.Wdecay2();
  }
  else if(ttbargen.IsAntiTopHadronicDecay()) {
    bot = ttbargen.bAntitop();
    q1 = ttbargen.WMinusdecay1();
    q2 = ttbargen.WMinusdecay2();
  }

  std::vector<GenParticle> quarks = {bot, q1, q2};

  if(subjets.size() == 3) {
    for(unsigned int i=0; i<quarks.size(); i++) {
      double minR = 100;
      for(unsigned int j=0; j<subjets.size(); j++) {
        double tmpR = deltaR(quarks.at(i), subjets.at(j));
        if(tmpR < minR) {
          minR = tmpR;
        }
      }
      if(minR > 0.4) {
        matched = false;
      }
    }
  } else {
    matched = false;
  }
  return matched;
}

////////////////////////////////////////////////////////