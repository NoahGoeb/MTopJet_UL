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

