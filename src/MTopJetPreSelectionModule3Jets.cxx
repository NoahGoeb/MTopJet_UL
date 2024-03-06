#include <iostream>
#include <memory>

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/Selection.h>

#include <UHH2/common/include/NSelections.h>
#include <UHH2/common/include/LumiSelection.h>
#include <UHH2/common/include/TriggerSelection.h>
#include <UHH2/common/include/JetCorrections.h>
#include <UHH2/common/include/ObjectIdUtils.h>
#include <UHH2/common/include/JetIds.h>
#include <UHH2/common/include/TopJetIds.h>
#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/Utils.h>
#include <UHH2/common/include/AdditionalSelections.h>
#include "UHH2/common/include/YearRunSwitchers.h"

// Hists
#include <UHH2/common/include/ElectronHists.h>
#include <UHH2/common/include/EventHists.h>
#include <UHH2/common/include/MuonHists.h>
#include <UHH2/common/include/JetHists.h>
#include <UHH2/common/include/TTbarGenHists.h>
#include <UHH2/MTopJet_UL/include/MTopJetHists.h>
//
#include <UHH2/MTopJet_UL/include/ModuleBASE.h>

using namespace std;

class MTopJetPreSelectionModule3Jets : public ModuleBASE {

public:
  explicit MTopJetPreSelectionModule3Jets(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;

protected:


  // bools
  bool debug;
  
};

/*
███    ███  ██████  ██████  ██    ██ ██      ███████
████  ████ ██    ██ ██   ██ ██    ██ ██      ██
██ ████ ██ ██    ██ ██   ██ ██    ██ ██      █████
██  ██  ██ ██    ██ ██   ██ ██    ██ ██      ██
██      ██  ██████  ██████   ██████  ███████ ███████
*/

MTopJetPreSelectionModule3Jets::MTopJetPreSelectionModule3Jets(uhh2::Context& ctx){

  debug = string2bool(ctx.get("Debug","false")); // look for Debug, expect false if not found

  //// CONFIGURATION
  bool isherwig;
  if(ctx.get("dataset_version") == "TTbar_powheg-herwig") isherwig = true;
  else isherwig = false;

}

/*
██████  ██████   ██████   ██████ ███████ ███████ ███████
██   ██ ██   ██ ██    ██ ██      ██      ██      ██
██████  ██████  ██    ██ ██      █████   ███████ ███████
██      ██   ██ ██    ██ ██      ██           ██      ██
██      ██   ██  ██████   ██████ ███████ ███████ ███████
*/

bool MTopJetPreSelectionModule3Jets::process(uhh2::Event& event){

}

UHH2_REGISTER_ANALYSIS_MODULE(MTopJetPreSelectionModule3Jets)
