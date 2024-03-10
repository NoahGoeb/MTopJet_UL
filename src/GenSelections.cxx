#include <UHH2/MTopJet_UL/include/GenSelections.h>
#include <iostream>



uhh2::TTbarSemilep::TTbarSemilep(uhh2::Context& ctx):
h_ttbargen(ctx.get_handle<TTbarGen>("ttbargen")) {}

bool uhh2::TTbarSemilep::passes(const uhh2::Event& event){

  const auto & ttbargen = event.get(h_ttbargen);
  bool semilep = false;

  if(ttbargen.DecayChannel() == TTbarGen::e_muhad || ttbargen.DecayChannel() == TTbarGen::e_ehad) semilep = true;
  return semilep;
}

////////////////////////////////////////////////////////

uhh2::TTbarSemilep_herwig::TTbarSemilep_herwig(uhh2::Context& ctx){}

bool uhh2::TTbarSemilep_herwig::passes(const uhh2::Event& event){

  bool semilep = false;
  int lep_counter = 0;
  std::vector<GenParticle>* genparts = event.genparticles;
  for (unsigned int i=0; i<(genparts->size()); ++i){
    GenParticle p = genparts->at(i);
    if(abs(p.pdgId()) == 11 || abs(p.pdgId()) == 13 ) ++lep_counter;
  }
  if(lep_counter == 1) semilep = true;
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
