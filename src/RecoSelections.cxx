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
