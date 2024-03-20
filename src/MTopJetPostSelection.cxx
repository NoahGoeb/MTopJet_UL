#include <iostream>
#include <fstream>
#include <memory>

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/Selection.h>

#include <UHH2/common/include/AdditionalSelections.h>
#include <UHH2/common/include/CommonModules.h>
#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/Utils.h>
#include <UHH2/common/include/MCWeight.h>

#include <UHH2/MTopJet_UL/include/ModuleBASE.h>

#include <vector>

class MTopJetPostSelection : public ModuleBASE {

public:
  explicit MTopJetPostSelection(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;
  void declare_output(uhh2::Context& ctx);
  void init_handels(uhh2::Context& ctx);
  void init_hists(uhh2::Context& ctx);
  void init_MC_hists(uhh2::Context& ctx);

};

void MTopJetPostSelection::init_handels(uhh2::Context& ctx){

}

void MTopJetPostSelection::declare_output(uhh2::Context& ctx){

}

void MTopJetPostSelection::init_MC_hists(uhh2::Context& ctx){

}

void MTopJetPostSelection::init_hists(uhh2::Context& ctx){

}

MTopJetPostSelection::MTopJetPostSelection(uhh2::Context& ctx){

}

bool MTopJetPostSelection::process(uhh2::Event& event){
  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(MTopJetPostSelection)
