#include <UHH2/MTopJet_UL/include/CombineXCone.h>

#include "TLorentzVector.h"

GenTopJet CombineXCone::CreateTopJetFromSubjets_gen(vector<GenJet> subjets, double ptmin, double etamax){
  double px=0, py=0, pz=0, E=0;
  TLorentzVector jet_v4;
  GenTopJet jet;
  for(auto sj: subjets) jet.add_subjet(sj);
  
  for(unsigned int i=0; i < subjets.size(); ++i){
    px += subjets.at(i).v4().Px();
    py += subjets.at(i).v4().Py();
    pz += subjets.at(i).v4().Pz();
    E += subjets.at(i).v4().E();
  }
  
  jet_v4.SetPxPyPzE(px, py, pz, E);
  jet.set_pt(jet_v4.Pt());
  jet.set_eta(jet_v4.Eta());
  jet.set_phi(jet_v4.Phi());
  jet.set_energy(jet_v4.E());

  return jet;
}

/*
.██████  ███████ ███    ██
██       ██      ████   ██
██   ███ █████   ██ ██  ██
██    ██ ██      ██  ██ ██
.██████  ███████ ██   ████
*/


// Get final Jets from 3+3 Method on Gen level
CombineXCone2_gen::CombineXCone2_gen(uhh2::Context & ctx, bool isTTbar, const std::string & name_had, const std::string & name_lep):
h_GENxcone2hadjets(ctx.declare_event_output<std::vector<GenTopJet>>(name_had)),
h_GENxcone2lepjets(ctx.declare_event_output<std::vector<GenTopJet>>(name_lep)),
h_GENfatjets(ctx.get_handle<std::vector<GenTopJet>>("genXCone33TopJets")),
h_ttbargen(ctx.get_handle<TTbarGen>("ttbargen")),
isTTbar_ (isTTbar) {}

bool CombineXCone2_gen::process(uhh2::Event & event){
  //---------------------------------------------------------------------------------------
  //--------------------------------- get subjets and lepton ------------------------------
  //---------------------------------------------------------------------------------------
  GenParticle lepton;
  std::vector<GenTopJet> jets = event.get(h_GENfatjets);
  if(jets.size() < 2) return false;
  CombineXCone* combine = new CombineXCone();
  //---------------------------------------------------------------------------------------
  //------------- define had and lep jet (deltaR) -----------------------------------------
  //---------------------------------------------------------------------------------------
  GenTopJet fathadjet, fatlepjet;
  if(isTTbar_) {
    TTbarGen ttbargen = event.get(h_ttbargen);
    if(ttbargen.IsSemiLeptonicDecay()){
      lepton = ttbargen.ChargedLepton();
      float dR1 = deltaR(lepton, jets.at(0));
      float dR2 = deltaR(lepton, jets.at(1));
      if(dR1 < dR2){
        fatlepjet = jets.at(0);
        fathadjet = jets.at(1);
      }
      else{
        fatlepjet = jets.at(1);
        fathadjet = jets.at(0);
      }
    }
    else{
      fatlepjet = jets.at(1);
      fathadjet = jets.at(0);
    }
  }
  else{
    fatlepjet = jets.at(1);
    fathadjet = jets.at(0);
  }
  //---------------------------------------------------------------------------------------
  //-------- set Lorentz Vectors of subjets and combine them ------------------------------
  //---------------------------------------------------------------------------------------
  std::vector<GenJet> subjets_lep = fatlepjet.subjets();
  std::vector<GenJet> subjets_had = fathadjet.subjets();
  GenTopJet lepjet = combine->CreateTopJetFromSubjets_gen(subjets_lep, 0, 2.5);
  GenTopJet hadjet = combine->CreateTopJetFromSubjets_gen(subjets_had, 0, 2.5);
  vector<GenTopJet> hadjets;
  vector<GenTopJet> lepjets;
  hadjets.push_back(hadjet);
  lepjets.push_back(lepjet);

  //---------------------------------------------------------------------------------------
  //--------------------------------- Write Jets ------------------------------------------
  //---------------------------------------------------------------------------------------
  event.set(h_GENxcone2hadjets, hadjets);
  event.set(h_GENxcone2lepjets, lepjets);

  // delete combine;
  return true;
}
