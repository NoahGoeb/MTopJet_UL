#include <UHH2/MTopJet_UL/include/GenSelections.h>



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

