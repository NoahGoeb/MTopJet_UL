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
#include <UHH2/MTopJet_UL/include/CombineXCone.h>

#include <vector>

using namespace std;

class MTopJetPostSelection : public ModuleBASE {

public:
  explicit MTopJetPostSelection(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;
  void declare_output(uhh2::Context& ctx);
  void init_handels(uhh2::Context& ctx);
  void init_hists(uhh2::Context& ctx);
  void init_MC_hists(uhh2::Context& ctx);

protected:

  //Object construction
  std::unique_ptr<uhh2::AnalysisModule> ttgenprod, jetprod33_gen;

  //global variables for class
  bool debug;

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

  // Set variables
  debug = string2bool(ctx.get("Debug","false")); // look for Debug, expect false if not found

  if(debug) cout << "--- Start Module - CTX ---" << endl;

  //construction
  const std::string ttbar_gen_label("ttbargen");
  ttgenprod.reset(new TTbarGenProducer(ctx, ttbar_gen_label, false));

  jetprod33_gen.reset(new CombineXCone33_gen(ctx, true, "GEN_XCone33_had_Combined", "GEN_XCone33_lep_Combined"));

}

bool MTopJetPostSelection::process(uhh2::Event& event){

  // Construct objects
  if(debug) cout << "\t--- Construct Obects" << endl;

  ttgenprod->process(event);
  jetprod33_gen->process(event);

  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(MTopJetPostSelection)
