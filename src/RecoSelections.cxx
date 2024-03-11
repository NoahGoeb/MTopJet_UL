#include <UHH2/MTopJet_UL/include/RecoSelections.h>

uhh2::METCut::METCut(float min_met, float max_met):
min_met_(min_met), max_met_(max_met) {}

bool uhh2::METCut::passes(const uhh2::Event& event){

  assert(event.met);

  float MET = event.met->pt();
  return (MET > min_met_) && (MET < max_met_);
}
////////////////////////////////////////////////////////
