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
#include <UHH2/MTopJet_UL/include/GenHists.h>
#include <UHH2/MTopJet_UL/include/GenSelections.h>

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
  enum lepton { muon, elec };
  lepton channel_;

  Event::Handle<bool> h_passed_gensel;

  //Selections
  unique_ptr<uhh2::Selection> pt400_2gensel;
  unique_ptr<uhh2::Selection> pt10lep_2gensel;
  unique_ptr<uhh2::Selection> mass_2gensel;
  unique_ptr<uhh2::Selection> subjet_quality_2gensel;
  unique_ptr<uhh2::Selection> lepton_sel_gen;

  unique_ptr<uhh2::Selection> pt400_3gensel;
  unique_ptr<uhh2::Selection> pt10lep_3gensel;
  unique_ptr<uhh2::Selection> mass_3gensel;
  unique_ptr<uhh2::Selection> subjet_quality_3gensel;

  //Define Histograms
  unique_ptr<Hists> h_GEN_XCone2;
  unique_ptr<Hists> h_GEN_XCone3;

  //Object construction
  std::unique_ptr<uhh2::AnalysisModule> ttgenprod, jetprod2_gen, jetprod3_gen;

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

  h_GEN_XCone2.reset(new GenHists(ctx, "gen_XCone_2", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone3.reset(new GenHists(ctx, "gen_XCone_3", "GEN_XCone_3_had_Combined"));

}

void MTopJetPostSelection::init_hists(uhh2::Context& ctx){

}

MTopJetPostSelection::MTopJetPostSelection(uhh2::Context& ctx){

  // Set variables
  debug = string2bool(ctx.get("Debug","false")); // look for Debug, expect false if not found

  if(debug) cout << "--- Start Module - CTX ---" << endl;

  // channel
  const std::string& channel = ctx.get("channel", ""); //define Channel
  if     (channel == "muon") channel_ = muon;
  else if(channel == "elec") channel_ = elec;

  // Construction
  const std::string ttbar_gen_label("ttbargen");
  ttgenprod.reset(new TTbarGenProducer(ctx, ttbar_gen_label, false));

  jetprod2_gen.reset(new CombineXCone2_gen(ctx, true, "GEN_XCone_2_had_Combined", "GEN_XCone_2_lep_Combined"));
  jetprod3_gen.reset(new CombineXCone3_gen(ctx, true, "GEN_XCone_3_had_Combined", "GEN_XCone_3_lep_Combined"));

  // Define Selections
  if(channel_ == muon) {
    lepton_sel_gen.reset(new GenMuonSel(ctx, 60.0));
  } else {
    lepton_sel_gen.reset(new GenElecSel(ctx, 60.0));
  }
  pt400_2gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_2_had_Combined", 400));
  pt10lep_2gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_2_lep_Combined", 10));
  mass_2gensel.reset(new MassCut2_gen(ctx, "GEN_XCone_2_had_Combined", "GEN_XCone_2_lep_Combined"));
  subjet_quality_2gensel.reset(new SubjetQuality_gen(ctx, "GEN_XCone_2_had_Combined", 30, 2.5));
  
  pt400_3gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_3_had_Combined", 400));
  pt10lep_3gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_3_lep_Combined", 10));
  mass_3gensel.reset(new MassCut3_gen(ctx, "GEN_XCone_3_had_Combined", "GEN_XCone_3_lep_Combined", 1.2));
  subjet_quality_3gensel.reset(new SubjetQuality_gen(ctx, "GEN_XCone_3_had_Combined", 30, 2.5));

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
  jetprod3_gen->process(event);

  if(debug) cout << "\t--- get passed gensel" << endl;

  bool passed_gensel = event.get(h_passed_gensel);

  // Run selection for single events
  if(debug) cout << "\t--- Run Selection" << endl;

  bool pass_measurement2_gen = false;
  bool pass_measurement3_gen = false;

  pass_measurement2_gen = passed_gensel && pt400_2gensel->passes(event) && pt10lep_2gensel->passes(event) && mass_2gensel->passes(event) && subjet_quality_2gensel->passes(event) && lepton_sel_gen->passes(event);
  pass_measurement3_gen = passed_gensel && pt400_3gensel->passes(event) && pt10lep_3gensel->passes(event) && mass_3gensel->passes(event) && subjet_quality_3gensel->passes(event) && lepton_sel_gen->passes(event);

  // fill Hists
  if(pass_measurement2_gen) h_GEN_XCone2->fill(event);
  if(pass_measurement3_gen) h_GEN_XCone3->fill(event);

  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(MTopJetPostSelection)
