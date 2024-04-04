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
  //-------- set subjettines variables ----------------------------------------------------
  lepjet.set_tau1(fatlepjet.tau1());
  lepjet.set_tau2(fatlepjet.tau2());
  lepjet.set_tau3(fatlepjet.tau3());
  lepjet.set_tau4(fatlepjet.tau4());
  lepjet.set_tau1_groomed(fatlepjet.tau1_groomed());
  lepjet.set_tau2_groomed(fatlepjet.tau2_groomed());
  lepjet.set_tau3_groomed(fatlepjet.tau3_groomed());
  lepjet.set_tau4_groomed(fatlepjet.tau4_groomed());

  hadjet.set_tau1(fathadjet.tau1());
  hadjet.set_tau2(fathadjet.tau2());
  hadjet.set_tau3(fathadjet.tau3());
  hadjet.set_tau4(fathadjet.tau4());
  hadjet.set_tau1_groomed(fathadjet.tau1_groomed());
  hadjet.set_tau2_groomed(fathadjet.tau2_groomed());
  hadjet.set_tau3_groomed(fathadjet.tau3_groomed());
  hadjet.set_tau4_groomed(fathadjet.tau4_groomed());

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

CombineXCone3_gen::CombineXCone3_gen(uhh2::Context & ctx, bool isTTbar, const std::string & name_had, const std::string & name_lep):
h_GENxcone3hadjets(ctx.declare_event_output<std::vector<GenTopJet>>(name_had)),
h_GENxcone3lepjets(ctx.declare_event_output<std::vector<GenTopJet>>(name_lep)),
h_GENfatjets(ctx.get_handle<std::vector<GenTopJet>>("genXCone3TopJets")),
h_ttbargen(ctx.get_handle<TTbarGen>("ttbargen")),
isTTbar_ (isTTbar) {}

bool CombineXCone3_gen::process(uhh2::Event & event){
  //---------------------------------------------------------------------------------------
  //--------------------------------- get subjets and lepton ------------------------------
  //---------------------------------------------------------------------------------------
  GenParticle lepton;
  std::vector<GenTopJet> jets = event.get(h_GENfatjets);
  CombineXCone* combine = new CombineXCone();
  //---------------------------------------------------------------------------------------
  //-------- set Lorentz Vectors of subjets and combine them ------------------------------
  //---------------------------------------------------------------------------------------
  std::vector<GenTopJet> combinedJets;
  vector<GenTopJet> hadjets;
  vector<GenTopJet> lepjets;
  GenTopJet combinedJet;


  if(isTTbar_) {
    TTbarGen ttbargen = event.get(h_ttbargen);
    if(ttbargen.IsSemiLeptonicDecay()) {
      lepton = ttbargen.ChargedLepton();
      for(uint i=0; i<jets.size(); i++) {
        combinedJet = combine->CreateTopJetFromSubjets_gen(jets.at(i).subjets(), 0, 2.5);

        combinedJet.set_tau1(jets.at(i).tau1());
        combinedJet.set_tau2(jets.at(i).tau2());
        combinedJet.set_tau3(jets.at(i).tau3());
        combinedJet.set_tau4(jets.at(i).tau4());
        combinedJet.set_tau1_groomed(jets.at(i).tau1_groomed());
        combinedJet.set_tau2_groomed(jets.at(i).tau2_groomed());
        combinedJet.set_tau3_groomed(jets.at(i).tau3_groomed());
        combinedJet.set_tau4_groomed(jets.at(i).tau4_groomed());
        
        if(deltaR(lepton, jets.at(i)) > 1.2) {
          hadjets.push_back(combinedJet);
        } else if(deltaR(lepton, jets.at(i)) < 1.2) {
          lepjets.push_back(combinedJet);
        }
      }
    }
  }

  

  //---------------------------------------------------------------------------------------
  //--------------------------------- Write Jets ------------------------------------------
  //---------------------------------------------------------------------------------------
  event.set(h_GENxcone3hadjets, hadjets);
  event.set(h_GENxcone3lepjets, lepjets);

  // delete combine;
  return true;
}
