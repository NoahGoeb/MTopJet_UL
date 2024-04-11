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

  Event::Handle<bool> h_measure_gen;

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
  unique_ptr<uhh2::Selection> no_near_jet_3gensel;

  unique_ptr<uhh2::Selection> pt500_2gensel;
  unique_ptr<uhh2::Selection> pt500_3gensel;
  unique_ptr<uhh2::Selection> pt600_2gensel;
  unique_ptr<uhh2::Selection> pt600_3gensel;
  unique_ptr<uhh2::Selection> pt700_2gensel;
  unique_ptr<uhh2::Selection> pt700_3gensel;
  unique_ptr<uhh2::Selection> pt800_2gensel;
  unique_ptr<uhh2::Selection> pt800_3gensel;
  unique_ptr<uhh2::Selection> pt900_2gensel;
  unique_ptr<uhh2::Selection> pt900_3gensel;

  //Define Histograms
  unique_ptr<Hists> h_GEN_XCone2;
  unique_ptr<Hists> h_GEN_XCone3;

  unique_ptr<Hists> h_GEN_XCone2_pt500;
  unique_ptr<Hists> h_GEN_XCone3_pt500;
  unique_ptr<Hists> h_GEN_XCone2_pt600;
  unique_ptr<Hists> h_GEN_XCone3_pt600;
  unique_ptr<Hists> h_GEN_XCone2_pt700;
  unique_ptr<Hists> h_GEN_XCone3_pt700;
  unique_ptr<Hists> h_GEN_XCone2_pt800;
  unique_ptr<Hists> h_GEN_XCone3_pt800;
  unique_ptr<Hists> h_GEN_XCone2_pt900;
  unique_ptr<Hists> h_GEN_XCone3_pt900;

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

  h_measure_gen = ctx.declare_event_output<bool>("passed_measurement_gen");

}

void MTopJetPostSelection::init_MC_hists(uhh2::Context& ctx){

  h_GEN_XCone2.reset(new GenHists(ctx, "gen_XCone_2", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone3.reset(new GenHists(ctx, "gen_XCone_3", "GEN_XCone_3_had_Combined"));

  h_GEN_XCone2_pt500.reset(new GenHists(ctx, "gen_XCone_2_pt500", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone3_pt500.reset(new GenHists(ctx, "gen_XCone_3_pt500", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone2_pt600.reset(new GenHists(ctx, "gen_XCone_2_pt600", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone3_pt600.reset(new GenHists(ctx, "gen_XCone_3_pt600", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone2_pt700.reset(new GenHists(ctx, "gen_XCone_2_pt700", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone3_pt700.reset(new GenHists(ctx, "gen_XCone_3_pt700", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone2_pt800.reset(new GenHists(ctx, "gen_XCone_2_pt800", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone3_pt800.reset(new GenHists(ctx, "gen_XCone_3_pt800", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone2_pt900.reset(new GenHists(ctx, "gen_XCone_2_pt900", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone3_pt900.reset(new GenHists(ctx, "gen_XCone_3_pt900", "GEN_XCone_3_had_Combined"));

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
  no_near_jet_3gensel.reset(new NoNearJet_gen(ctx, "GEN_XCone_3_had_Combined", 1.2));

  pt500_2gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_2_had_Combined", 500));
  pt500_3gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_3_had_Combined", 500));
  pt600_2gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_2_had_Combined", 600));
  pt600_3gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_3_had_Combined", 600));
  pt700_2gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_2_had_Combined", 700));
  pt700_3gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_3_had_Combined", 700));
  pt800_2gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_2_had_Combined", 800));
  pt800_3gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_3_had_Combined", 800));
  pt900_2gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_2_had_Combined", 900));
  pt900_3gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_3_had_Combined", 900));

  // Initiate input and output
  if(debug) cout << "\t--- Initiate input and output" << endl;
  init_handels(ctx);
  init_MC_hists(ctx);

  ctx.undeclare_all_event_output(); // Delete everything to save space
  declare_output(ctx); // Declare new output

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

  bool pass_measurement2_gen_pt500 = false;
  bool pass_measurement3_gen_pt500 = false;
  bool pass_measurement2_gen_pt600 = false;
  bool pass_measurement3_gen_pt600 = false;
  bool pass_measurement2_gen_pt700 = false;
  bool pass_measurement3_gen_pt700 = false;
  bool pass_measurement2_gen_pt800 = false;
  bool pass_measurement3_gen_pt800 = false;
  bool pass_measurement2_gen_pt900 = false;
  bool pass_measurement3_gen_pt900 = false;

  //pass_measurement_gen = passed_gensel33 && pt_gensel->passes(event) && pt2_gensel->passes(event) && mass_gensel->passes(event) && subjet_quality_gen->passes(event) && lepton_sel_gen->passes(event);
  pass_measurement2_gen = passed_gensel && pt400_2gensel->passes(event) && pt10lep_2gensel->passes(event) && mass_2gensel->passes(event) && subjet_quality_2gensel->passes(event) && lepton_sel_gen->passes(event);
  pass_measurement3_gen = passed_gensel && pt400_3gensel->passes(event) && pt10lep_3gensel->passes(event) && mass_3gensel->passes(event) && subjet_quality_3gensel->passes(event) && lepton_sel_gen->passes(event) && no_near_jet_3gensel->passes(event);

  pass_measurement2_gen_pt500 = pass_measurement2_gen && pt500_2gensel->passes(event);
  pass_measurement3_gen_pt500 = pass_measurement3_gen && pt500_3gensel->passes(event);
  pass_measurement2_gen_pt600 = pass_measurement2_gen && pt600_2gensel->passes(event);
  pass_measurement3_gen_pt600 = pass_measurement3_gen && pt600_3gensel->passes(event);
  pass_measurement2_gen_pt700 = pass_measurement2_gen && pt700_2gensel->passes(event);
  pass_measurement3_gen_pt700 = pass_measurement3_gen && pt700_3gensel->passes(event);
  pass_measurement2_gen_pt800 = pass_measurement2_gen && pt800_2gensel->passes(event);
  pass_measurement3_gen_pt800 = pass_measurement3_gen && pt800_3gensel->passes(event);
  pass_measurement2_gen_pt900 = pass_measurement2_gen && pt900_2gensel->passes(event);
  pass_measurement3_gen_pt900 = pass_measurement3_gen && pt900_3gensel->passes(event);

  // fill Hists
  if(pass_measurement2_gen) h_GEN_XCone2->fill(event);
  if(pass_measurement3_gen) h_GEN_XCone3->fill(event);

  if(pass_measurement2_gen_pt500) h_GEN_XCone2_pt500->fill(event);
  if(pass_measurement3_gen_pt500) h_GEN_XCone3_pt500->fill(event);
  if(pass_measurement2_gen_pt600) h_GEN_XCone2_pt600->fill(event);
  if(pass_measurement3_gen_pt600) h_GEN_XCone3_pt600->fill(event);
  if(pass_measurement2_gen_pt700) h_GEN_XCone2_pt700->fill(event);
  if(pass_measurement3_gen_pt700) h_GEN_XCone3_pt700->fill(event);
  if(pass_measurement2_gen_pt800) h_GEN_XCone2_pt800->fill(event);
  if(pass_measurement3_gen_pt800) h_GEN_XCone3_pt800->fill(event);
  if(pass_measurement2_gen_pt900) h_GEN_XCone2_pt900->fill(event);
  if(pass_measurement3_gen_pt900) h_GEN_XCone3_pt900->fill(event);

  event.set(h_measure_gen, pass_measurement2_gen || pass_measurement3_gen);

  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(MTopJetPostSelection)
