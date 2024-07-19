#include <UHH2/MTopJet_UL/include/MTopJetUtils.h>
#include <UHH2/core/include/LorentzVector.h>
#include <UHH2/common/include/JetCorrections.h>
#include <UHH2/common/include/Utils.h>
#include <UHH2/core/include/Utils.h>

#include <string>


////

const Particle* leading_lepton(const uhh2::Event& event){

  const Particle* lep(0);

  float ptL_max(0.);
  if(event.muons)    { for(const auto& mu : *event.muons)    { if(mu.pt() > ptL_max){ ptL_max = mu.pt(); lep = &mu; } } }
  if(event.electrons){ for(const auto& el : *event.electrons){ if(el.pt() > ptL_max){ ptL_max = el.pt(); lep = &el; } } }

  if(!lep) throw std::runtime_error("leading_lepton -- pt-leading lepton not found");

  return lep;
}

////

std::vector<GenParticle> outgoingGluons(const uhh2::Event & event) {
  std::vector<GenParticle> *genparticles = event.genparticles;
  int nparts = genparticles->size();
  
  std::vector<GenParticle> gluons;
  //look for outgoing gluons in jet
  for(int i=0; i<nparts; ++i) {
    GenParticle* p = &(genparticles->at(i));

    auto mother1 = p->mother(genparticles,1);
    auto mother2 = p->mother(genparticles,2);

    if(mother1 != nullptr && mother2 != nullptr) {
      if(abs(p->pdgId()) != 6 && mother1->status() == 21 && mother2->status() == 21) {
        if(p->pt() > 20) gluons.push_back(*p);
      }
    }
  }

  return gluons;
}

////