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

  Event::Handle<bool> h_passed_gensel;

  //Object construction
  std::unique_ptr<uhh2::AnalysisModule> ttgenprod, jetprod2_gen;

  //global variables for class
  bool debug;

};

void MTopJetPostSelection::init_handels(uhh2::Context& ctx){

  if(debug) cout << "--- Start Module - init handles ---" << endl;

  h_passed_gensel = ctx.get_handle<bool>("passed_gensel");

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

  jetprod2_gen.reset(new CombineXCone2_gen(ctx, true, "GEN_XCone_2_had_Combined", "GEN_XCone_2_lep_Combined"));

  // Initiate input and output
  if(debug) cout << "\t--- Initiate input and output" << endl;
  init_handels(ctx);
  init_MC_hists(ctx);

}

bool MTopJetPostSelection::process(uhh2::Event& event){

  // Construct objects
  if(debug) cout << "\t--- Construct Obects" << endl;

  ttgenprod->process(event);
  jetprod2_gen->process(event);

  if(debug) cout << "\t--- get passed gensel" << endl;

  bool passed_gensel = event.get(h_passed_gensel);

  // Run selection for single events
  if(debug) cout << "\t--- Run Selection" << endl;

  bool pass_measurement2_gen = false;

  pass_measurement2_gen = passed_gensel;

  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(MTopJetPostSelection)
