#include <UHH2/MTopJet_UL/include/RecoSelections.h>

uhh2::METCut::METCut(float min_met, float max_met):
min_met_(min_met), max_met_(max_met) {}

bool uhh2::METCut::passes(const uhh2::Event& event){

  assert(event.met);

  float MET = event.met->pt();
  return (MET > min_met_) && (MET < max_met_);
}

////////////////////////////////////////////////////////

uhh2::ElectronEtaVeto::ElectronEtaVeto(double lower_, double upper_):
lower(lower_),
upper(upper_) {}

bool uhh2::ElectronEtaVeto::passes(const uhh2::Event& event){
  bool pass_veto = false;
  if(event.electrons->size() != 0){
    double eta = fabs(event.electrons->at(0).eta());
    if(eta < lower || eta > upper) pass_veto = true;
  }
  return pass_veto;
}

////////////////////////////////////////////////////////

bool uhh2::TwoDCut1::passes(const uhh2::Event& event){

  if(event.muons->size() != 0 || event.electrons->size() != 0){
    assert(event.muons && event.electrons && event.jets);

    const Particle* lepton = leading_lepton(event);

    float drmin, ptrel;
    std::tie(drmin, ptrel) = drmin_pTrel(*lepton, *event.jets);

    return ((drmin > min_deltaR_) || (ptrel > min_pTrel_));
  }
  else return true;
}

////////////////////////////////////////////////////////
