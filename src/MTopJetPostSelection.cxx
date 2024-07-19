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

  Event::Handle<bool> h_passed_gensel2;
  Event::Handle<bool> h_passed_gensel3;
  Event::Handle<bool> h_passed_genselSubPT;

  Event::Handle<bool> h_measure_gen;

  //Selections
  unique_ptr<uhh2::Selection> pt330_2gensel;
  unique_ptr<uhh2::Selection> pt400_2gensel;
  unique_ptr<uhh2::Selection> pt10lep_2gensel;
  unique_ptr<uhh2::Selection> mass_2gensel;
  unique_ptr<uhh2::Selection> subjet_quality_2gensel;
  unique_ptr<uhh2::Selection> lepton_gensel;
  unique_ptr<uhh2::Selection> top_2genmatch;
  unique_ptr<uhh2::Selection> gluon_2genmatch;

  unique_ptr<uhh2::Selection> pt400_3gensel;
  unique_ptr<uhh2::Selection> pt10lep_3gensel;
  unique_ptr<uhh2::Selection> mass_3gensel;
  unique_ptr<uhh2::Selection> subjet_quality_3gensel;
  unique_ptr<uhh2::Selection> no_near_jet_3gensel;
  unique_ptr<uhh2::Selection> top_3genmatch;
  unique_ptr<uhh2::Selection> tauCut32_3gen;
  unique_ptr<uhh2::Selection> tauCut42_3gen;
  unique_ptr<uhh2::Selection> tauCut42_2gen;
  unique_ptr<uhh2::Selection> groomedTauCut32_3gen;
  unique_ptr<uhh2::Selection> groomedTauCut42_3gen;
  unique_ptr<uhh2::Selection> pt400Combined_3gen;
  unique_ptr<uhh2::Selection> fullyMergedLeading_gen;
  unique_ptr<uhh2::Selection> fullyMergedSubleading_gen;

  unique_ptr<uhh2::Selection> pt400_SubPTgensel;
  unique_ptr<uhh2::Selection> pt10lep_SubPTgensel;
  unique_ptr<uhh2::Selection> mass_SubPTgensel;
  unique_ptr<uhh2::Selection> subjet_quality_SubPTgensel;
  unique_ptr<uhh2::Selection> top_SubPTgenmatch;


  unique_ptr<uhh2::Selection> pt500_2gensel;
  unique_ptr<uhh2::Selection> pt500_3gensel;
  unique_ptr<uhh2::Selection> pt500_SubPTgensel;
  unique_ptr<uhh2::Selection> pt600_2gensel;
  unique_ptr<uhh2::Selection> pt600_3gensel;
  unique_ptr<uhh2::Selection> pt600_SubPTgensel;
  unique_ptr<uhh2::Selection> pt700_2gensel;
  unique_ptr<uhh2::Selection> pt700_3gensel;
  unique_ptr<uhh2::Selection> pt700_SubPTgensel;
  unique_ptr<uhh2::Selection> pt800_2gensel;
  unique_ptr<uhh2::Selection> pt800_3gensel;
  unique_ptr<uhh2::Selection> pt800_SubPTgensel;
  unique_ptr<uhh2::Selection> pt900_2gensel;
  unique_ptr<uhh2::Selection> pt900_3gensel;
  unique_ptr<uhh2::Selection> pt900_SubPTgensel;

  //Define Histograms
  unique_ptr<Hists> h_GEN_XCone2;
  unique_ptr<Hists> h_GEN_XCone2_TopMatched;
  unique_ptr<Hists> h_GEN_XCone2_GluonMatched;
  unique_ptr<Hists> h_GEN_XCone2_GluonPartMatched;
  unique_ptr<Hists> h_GEN_XCone2_NotTauCut42;

  unique_ptr<Hists> h_GEN_XCone3;
  unique_ptr<Hists> h_GEN_XCone3_TopMatched;
  unique_ptr<Hists> h_GEN_XCone3_GluonMatched;
  unique_ptr<Hists> h_GEN_XCone3_TauCut32;
  unique_ptr<Hists> h_GEN_XCone3_TauCut42;
  unique_ptr<Hists> h_GEN_XCone3_NotTauCut32;
  unique_ptr<Hists> h_GEN_XCone3_NotTauCut42;
  unique_ptr<Hists> h_GEN_XCone3_FullyMergedLeading;
  unique_ptr<Hists> h_GEN_XCone3_FullyMergedSubleading;
  unique_ptr<Hists> h_GEN_XCone3_NoCutsFullyMergedLeading;
  unique_ptr<Hists> h_GEN_XCone3_NoCutsFullyMergedSubleading;

  unique_ptr<Hists> h_GEN_XCone3_Near;
  unique_ptr<Hists> h_GEN_XCone3_All;

  unique_ptr<Hists> h_GEN_XConeSubPT;
  unique_ptr<Hists> h_GEN_XConeSubPT_TopMatched;
  unique_ptr<Hists> h_GEN_XConeSubPT_GluonMatched;

  unique_ptr<Hists> h_GEN_XCone2_pt500;
  unique_ptr<Hists> h_GEN_XCone2_pt500_TopMatched;
  unique_ptr<Hists> h_GEN_XCone2_pt500_GluonMatched;
  unique_ptr<Hists> h_GEN_XCone3_pt500;
  unique_ptr<Hists> h_GEN_XCone3_pt500_TopMatched;
  unique_ptr<Hists> h_GEN_XCone3_pt500_GluonMatched;
  unique_ptr<Hists> h_GEN_XCone3_pt500_TauCut32;
  unique_ptr<Hists> h_GEN_XCone3_pt500_TauCut42;
  unique_ptr<Hists> h_GEN_XConeSubPT_pt500;

  unique_ptr<Hists> h_GEN_XCone2_pt600;
  unique_ptr<Hists> h_GEN_XCone2_pt600_TopMatched;
  unique_ptr<Hists> h_GEN_XCone2_pt600_GluonMatched;
  unique_ptr<Hists> h_GEN_XCone3_pt600;
  unique_ptr<Hists> h_GEN_XCone3_pt600_TopMatched;
  unique_ptr<Hists> h_GEN_XCone3_pt600_GluonMatched;
  unique_ptr<Hists> h_GEN_XCone3_pt600_TauCut32;
  unique_ptr<Hists> h_GEN_XCone3_pt600_TauCut42;
  unique_ptr<Hists> h_GEN_XConeSubPT_pt600;

  unique_ptr<Hists> h_GEN_XCone2_pt700;
  unique_ptr<Hists> h_GEN_XCone2_pt700_TopMatched;
  unique_ptr<Hists> h_GEN_XCone2_pt700_GluonMatched;
  unique_ptr<Hists> h_GEN_XCone3_pt700;
  unique_ptr<Hists> h_GEN_XCone3_pt700_TopMatched;
  unique_ptr<Hists> h_GEN_XCone3_pt700_GluonMatched;
  unique_ptr<Hists> h_GEN_XCone3_pt700_TauCut32;
  unique_ptr<Hists> h_GEN_XCone3_pt700_TauCut42;
  unique_ptr<Hists> h_GEN_XConeSubPT_pt700;

  unique_ptr<Hists> h_GEN_XCone2_pt800;
  unique_ptr<Hists> h_GEN_XCone2_pt800_TopMatched;
  unique_ptr<Hists> h_GEN_XCone2_pt800_GluonMatched;
  unique_ptr<Hists> h_GEN_XCone3_pt800;
  unique_ptr<Hists> h_GEN_XCone3_pt800_TopMatched;
  unique_ptr<Hists> h_GEN_XCone3_pt800_GluonMatched;
  unique_ptr<Hists> h_GEN_XCone3_pt800_TauCut32;
  unique_ptr<Hists> h_GEN_XCone3_pt800_TauCut42;
  unique_ptr<Hists> h_GEN_XConeSubPT_pt800;

  unique_ptr<Hists> h_GEN_XCone2_pt900;
  unique_ptr<Hists> h_GEN_XCone2_pt900_TopMatched;
  unique_ptr<Hists> h_GEN_XCone2_pt900_GluonMatched;
  unique_ptr<Hists> h_GEN_XCone3_pt900;
  unique_ptr<Hists> h_GEN_XCone3_pt900_TopMatched;
  unique_ptr<Hists> h_GEN_XCone3_pt900_GluonMatched;
  unique_ptr<Hists> h_GEN_XCone3_pt900_TauCut32;
  unique_ptr<Hists> h_GEN_XCone3_pt900_TauCut42;
  unique_ptr<Hists> h_GEN_XConeSubPT_pt900;

  unique_ptr<Hists> h_GEN_XCone2_sel;
  unique_ptr<Hists> h_GEN_XCone2_sel1;
  unique_ptr<Hists> h_GEN_XCone2_sel2;
  unique_ptr<Hists> h_GEN_XCone2_sel3;
  unique_ptr<Hists> h_GEN_XCone2_sel4;


  //Object construction
  std::unique_ptr<uhh2::AnalysisModule> ttgenprod, jetprod2_gen, jetprod3_gen, jetprodSubPT_gen;

  //global variables for class
  bool debug;

};

void MTopJetPostSelection::init_handels(uhh2::Context& ctx){

  if(debug) cout << "--- Start Module - init handles ---" << endl;

  h_passed_gensel2 = ctx.get_handle<bool>("passed_gensel2");
  h_passed_gensel3 = ctx.get_handle<bool>("passed_gensel3");
  h_passed_genselSubPT = ctx.get_handle<bool>("passed_gensel2SubPT");

}

void MTopJetPostSelection::declare_output(uhh2::Context& ctx){

  h_measure_gen = ctx.declare_event_output<bool>("passed_measurement_gen");

}

void MTopJetPostSelection::init_MC_hists(uhh2::Context& ctx){

  h_GEN_XCone2.reset(new GenHists(ctx, "gen_XCone_2", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone2_TopMatched.reset(new GenHists(ctx, "gen_XCone_2_TopMatched", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone2_GluonMatched.reset(new GenHists(ctx, "gen_XCone_2_GluonMatched", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone2_GluonPartMatched.reset(new GenHists(ctx, "gen_XCone_2_GluonPartMatched", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone2_NotTauCut42.reset(new GenHists(ctx, "gen_XCone_2_NotTauCut42", "GEN_XCone_2_had_Combined"));

  h_GEN_XCone3.reset(new GenHists(ctx, "gen_XCone_3", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_TopMatched.reset(new GenHists(ctx, "gen_XCone_3_TopMatched", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_GluonMatched.reset(new GenHists(ctx, "gen_XCone_3_GluonMatched", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_TauCut32.reset(new GenHists(ctx, "gen_XCone_3_TauCut32", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_TauCut42.reset(new GenHists(ctx, "gen_XCone_3_TauCut42", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_NotTauCut32.reset(new GenHists(ctx, "gen_XCone_3_NotTauCut32", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_NotTauCut42.reset(new GenHists(ctx, "gen_XCone_3_NotTauCut42", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_FullyMergedLeading.reset(new GenHists(ctx, "gen_XCone_3_FullyMergedLeading", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_FullyMergedSubleading.reset(new GenHists(ctx, "gen_XCone_3_FullyMergedSubleading", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_NoCutsFullyMergedLeading.reset(new GenHists(ctx, "gen_XCone_3_NoCutsFullyMergedLeading", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_NoCutsFullyMergedSubleading.reset(new GenHists(ctx, "gen_XCone_3_NoCutsFullyMergedSubleading", "GEN_XCone_3_had_Combined"));

  h_GEN_XCone3_Near.reset(new GenHists(ctx, "gen_XCone_3_Near", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_All.reset(new GenHists(ctx, "gen_XCone_3_All", "GEN_XCone_3_had_Combined"));

  h_GEN_XConeSubPT.reset(new GenHists(ctx, "gen_XCone_SubPT", "GEN_XCone_SubPT_had_Combined"));
  h_GEN_XConeSubPT_TopMatched.reset(new GenHists(ctx, "gen_XCone_SubPT_TopMatched", "GEN_XCone_SubPT_had_Combined"));
  h_GEN_XConeSubPT_GluonMatched.reset(new GenHists(ctx, "gen_XCone_SubPT_GluonMatched", "GEN_XCone_SubPT_had_Combined"));

  h_GEN_XCone2_pt500.reset(new GenHists(ctx, "gen_XCone_2_pt500", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone2_pt500_TopMatched.reset(new GenHists(ctx, "gen_XCone_2_pt500_TopMatched", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone2_pt500_GluonMatched.reset(new GenHists(ctx, "gen_XCone_2_pt500_GluonMatched", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone3_pt500.reset(new GenHists(ctx, "gen_XCone_3_pt500", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_pt500_TopMatched.reset(new GenHists(ctx, "gen_XCone_3_pt500_TopMatched", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_pt500_GluonMatched.reset(new GenHists(ctx, "gen_XCone_3_pt500_GluonMatched", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_pt500_TauCut32.reset(new GenHists(ctx, "gen_XCone_3_pt500_TauCut32", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_pt500_TauCut42.reset(new GenHists(ctx, "gen_XCone_3_pt500_TauCut42", "GEN_XCone_3_had_Combined"));
  h_GEN_XConeSubPT_pt500.reset(new GenHists(ctx, "gen_XCone_SubPT_pt500", "GEN_XCone_SubPT_had_Combined"));

  h_GEN_XCone2_pt600.reset(new GenHists(ctx, "gen_XCone_2_pt600", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone2_pt600_TopMatched.reset(new GenHists(ctx, "gen_XCone_2_pt600_TopMatched", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone2_pt600_GluonMatched.reset(new GenHists(ctx, "gen_XCone_2_pt600_GluonMatched", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone3_pt600.reset(new GenHists(ctx, "gen_XCone_3_pt600", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_pt600_TopMatched.reset(new GenHists(ctx, "gen_XCone_3_pt600_TopMatched", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_pt600_GluonMatched.reset(new GenHists(ctx, "gen_XCone_3_pt600_GluonMatched", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_pt600_TauCut32.reset(new GenHists(ctx, "gen_XCone_3_pt600_TauCut32", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_pt600_TauCut42.reset(new GenHists(ctx, "gen_XCone_3_pt600_TauCut42", "GEN_XCone_3_had_Combined"));
  h_GEN_XConeSubPT_pt600.reset(new GenHists(ctx, "gen_XCone_SubPT_pt600", "GEN_XCone_SubPT_had_Combined"));

  h_GEN_XCone2_pt700.reset(new GenHists(ctx, "gen_XCone_2_pt700", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone2_pt700_TopMatched.reset(new GenHists(ctx, "gen_XCone_2_pt700_TopMatched", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone2_pt700_GluonMatched.reset(new GenHists(ctx, "gen_XCone_2_pt700_GluonMatched", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone3_pt700.reset(new GenHists(ctx, "gen_XCone_3_pt700", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_pt700_TopMatched.reset(new GenHists(ctx, "gen_XCone_3_pt700_TopMatched", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_pt700_GluonMatched.reset(new GenHists(ctx, "gen_XCone_3_pt700_GluonMatched", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_pt700_TauCut32.reset(new GenHists(ctx, "gen_XCone_3_pt700_TauCut32", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_pt700_TauCut42.reset(new GenHists(ctx, "gen_XCone_3_pt700_TauCut42", "GEN_XCone_3_had_Combined"));
  h_GEN_XConeSubPT_pt700.reset(new GenHists(ctx, "gen_XCone_SubPT_pt700", "GEN_XCone_SubPT_had_Combined"));

  h_GEN_XCone2_pt800.reset(new GenHists(ctx, "gen_XCone_2_pt800", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone2_pt800_TopMatched.reset(new GenHists(ctx, "gen_XCone_2_pt800_TopMatched", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone2_pt800_GluonMatched.reset(new GenHists(ctx, "gen_XCone_2_pt800_GluonMatched", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone3_pt800.reset(new GenHists(ctx, "gen_XCone_3_pt800", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_pt800_TopMatched.reset(new GenHists(ctx, "gen_XCone_3_pt800_TopMatched", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_pt800_GluonMatched.reset(new GenHists(ctx, "gen_XCone_3_pt800_GluonMatched", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_pt800_TauCut32.reset(new GenHists(ctx, "gen_XCone_3_pt800_TauCut32", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_pt800_TauCut42.reset(new GenHists(ctx, "gen_XCone_3_pt800_TauCut42", "GEN_XCone_3_had_Combined"));
  h_GEN_XConeSubPT_pt800.reset(new GenHists(ctx, "gen_XCone_SubPT_pt800", "GEN_XCone_SubPT_had_Combined"));

  h_GEN_XCone2_pt900.reset(new GenHists(ctx, "gen_XCone_2_pt900", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone2_pt900_TopMatched.reset(new GenHists(ctx, "gen_XCone_2_pt900_TopMatched", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone2_pt900_GluonMatched.reset(new GenHists(ctx, "gen_XCone_2_pt900_GluonMatched", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone3_pt900.reset(new GenHists(ctx, "gen_XCone_3_pt900", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_pt900_TopMatched.reset(new GenHists(ctx, "gen_XCone_3_pt900_TopMatched", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_pt900_GluonMatched.reset(new GenHists(ctx, "gen_XCone_3_pt900_GluonMatched", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_pt900_TauCut32.reset(new GenHists(ctx, "gen_XCone_3_pt900_TauCut32", "GEN_XCone_3_had_Combined"));
  h_GEN_XCone3_pt900_TauCut42.reset(new GenHists(ctx, "gen_XCone_3_pt900_TauCut42", "GEN_XCone_3_had_Combined"));
  h_GEN_XConeSubPT_pt900.reset(new GenHists(ctx, "gen_XCone_SubPT_pt900", "GEN_XCone_SubPT_had_Combined"));

  h_GEN_XCone2_sel.reset(new GenHists(ctx, "gen_XCone_2_sel", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone2_sel1.reset(new GenHists(ctx, "gen_XCone_2_sel1", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone2_sel2.reset(new GenHists(ctx, "gen_XCone_2_sel2", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone2_sel3.reset(new GenHists(ctx, "gen_XCone_2_sel3", "GEN_XCone_2_had_Combined"));
  h_GEN_XCone2_sel4.reset(new GenHists(ctx, "gen_XCone_2_sel4", "GEN_XCone_2_had_Combined"));

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
  jetprodSubPT_gen.reset(new CombineXConeSubPT_gen(ctx, true, "GEN_XCone_SubPT_had_Combined", "GEN_XCone_SubPT_lep_Combined"));

  // Define Selections
  if(channel_ == muon) {
    lepton_gensel.reset(new GenMuonSel(ctx, 60.0));
  } else {
    lepton_gensel.reset(new GenElecSel(ctx, 60.0));
  }
  pt330_2gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_2_had_Combined", 330));
  pt400_2gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_2_had_Combined", 400));
  pt10lep_2gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_2_lep_Combined", 10));
  mass_2gensel.reset(new MassCut2_gen(ctx, "GEN_XCone_2_had_Combined", "GEN_XCone_2_lep_Combined"));
  subjet_quality_2gensel.reset(new SubjetQuality_gen(ctx, "GEN_XCone_2_had_Combined", 30, 2.5));
  top_2genmatch.reset(new TopMatched_gen(ctx, "GEN_XCone_2_had_Combined", 1.2));
  gluon_2genmatch.reset(new GluonMatched_gen(ctx, "GEN_XCone_2_had_Combined", 1.2));
  
  pt400_3gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_3_had_Combined", 400));
  pt10lep_3gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_3_lep_Combined", 10));
  mass_3gensel.reset(new MassCut3_gen(ctx, "GEN_XCone_3_had_Combined", "GEN_XCone_3_lep_Combined", 1.2));
  subjet_quality_3gensel.reset(new SubjetQuality_gen(ctx, "GEN_XCone_3_had_Combined", 30, 2.5));
  no_near_jet_3gensel.reset(new NoNearJet_gen(ctx, "GEN_XCone_3_had_Combined", 1.2));
  top_3genmatch.reset(new TopMatched_gen(ctx, "GEN_XCone_3_had_Combined", 1.2));
  tauCut32_3gen.reset(new Tau32Cut_gen(ctx, "GEN_XCone_3_had_Combined", 0.58));
  tauCut42_3gen.reset(new Tau42Cut_gen(ctx, "GEN_XCone_3_had_Combined", 0.46));
  tauCut42_2gen.reset(new Tau42Cut_gen(ctx, "GEN_XCone_2_had_Combined", 0.46));
  groomedTauCut32_3gen.reset(new GroomedTau32Cut_gen(ctx, "GEN_XCone_3_had_Combined", 0.58));
  groomedTauCut42_3gen.reset(new GroomedTau42Cut_gen(ctx, "GEN_XCone_3_had_Combined", 0.46));
  pt400Combined_3gen.reset(new JetPTCombined_gen(ctx, "GEN_XCone_3_had_Combined", 400));
  fullyMergedLeading_gen.reset(new FullyMerged_Matched(ctx, "GEN_XCone_3_had_Combined", 0));
  fullyMergedSubleading_gen.reset(new FullyMerged_Matched(ctx, "GEN_XCone_3_had_Combined", 1));

  pt400_SubPTgensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_SubPT_had_Combined", 400));
  pt10lep_SubPTgensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_SubPT_lep_Combined", 10));
  mass_SubPTgensel.reset(new MassCut2_gen(ctx, "GEN_XCone_SubPT_had_Combined", "GEN_XCone_SubPT_lep_Combined"));
  subjet_quality_SubPTgensel.reset(new SubjetQuality_gen(ctx, "GEN_XCone_SubPT_had_Combined", 30, 2.5));
  top_SubPTgenmatch.reset(new TopMatched_gen(ctx, "GEN_XCone_SubPT_had_Combined", 1.2));

  pt500_2gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_2_had_Combined", 500));
  pt500_3gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_3_had_Combined", 500));
  pt500_SubPTgensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_SubPT_had_Combined", 500));
  pt600_2gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_2_had_Combined", 600));
  pt600_3gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_3_had_Combined", 600));
  pt600_SubPTgensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_SubPT_had_Combined", 600));
  pt700_2gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_2_had_Combined", 700));
  pt700_3gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_3_had_Combined", 700));
  pt700_SubPTgensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_SubPT_had_Combined", 700));
  pt800_2gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_2_had_Combined", 800));
  pt800_3gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_3_had_Combined", 800));
  pt800_SubPTgensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_SubPT_had_Combined", 800));
  pt900_2gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_2_had_Combined", 900));
  pt900_3gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_3_had_Combined", 900));
  pt900_SubPTgensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone_SubPT_had_Combined", 900));

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
  jetprodSubPT_gen->process(event);

  if(debug) cout << "\t--- get passed gensel" << endl;

  bool passed_gensel2 = event.get(h_passed_gensel2);
  bool passed_gensel3 = event.get(h_passed_gensel3);
  bool passed_genselSubPT = event.get(h_passed_genselSubPT);

  // Run selection for single events
  if(debug) cout << "\t--- Run Selection" << endl;

  bool pass_measurement2_gen = false;
  bool pass_measurement3_gen = false;
  bool pass_measurementSubPT_gen = false;

  bool pass_measurement3_gen_near = false;
  bool pass_measurement3_gen_all = false;

  bool pass_measurement2_gen_pt500 = false;
  bool pass_measurement3_gen_pt500 = false;
  bool pass_measurementSubPT_gen_pt500 = false;
  bool pass_measurement2_gen_pt600 = false;
  bool pass_measurement3_gen_pt600 = false;
  bool pass_measurementSubPT_gen_pt600 = false;
  bool pass_measurement2_gen_pt700 = false;
  bool pass_measurement3_gen_pt700 = false;
  bool pass_measurementSubPT_gen_pt700 = false;
  bool pass_measurement2_gen_pt800 = false;
  bool pass_measurement3_gen_pt800 = false;
  bool pass_measurementSubPT_gen_pt800 = false;
  bool pass_measurement2_gen_pt900 = false;
  bool pass_measurement3_gen_pt900 = false;
  bool pass_measurementSubPT_gen_pt900 = false;

  //pass_measurement_gen = passed_gensel33 && pt_gensel->passes(event) && pt2_gensel->passes(event) && mass_gensel->passes(event) && subjet_quality_gen->passes(event) && lepton_gensel->passes(event);
  pass_measurement2_gen = passed_gensel2 && pt400_2gensel->passes(event) && pt10lep_2gensel->passes(event) && mass_2gensel->passes(event) && subjet_quality_2gensel->passes(event) && lepton_gensel->passes(event);
  pass_measurement3_gen = passed_gensel3 && pt400Combined_3gen->passes(event) && pt10lep_3gensel->passes(event) && mass_3gensel->passes(event) && subjet_quality_3gensel->passes(event) && lepton_gensel->passes(event) && no_near_jet_3gensel->passes(event);
  pass_measurementSubPT_gen = passed_genselSubPT && pt400_SubPTgensel->passes(event) && pt10lep_SubPTgensel->passes(event) && mass_SubPTgensel->passes(event) && subjet_quality_SubPTgensel->passes(event) && lepton_gensel->passes(event);

  pass_measurement3_gen_near = passed_gensel3 && pt400Combined_3gen->passes(event) && pt10lep_3gensel->passes(event) && mass_3gensel->passes(event) && subjet_quality_3gensel->passes(event) && lepton_gensel->passes(event) && !no_near_jet_3gensel->passes(event);
  pass_measurement3_gen_all = passed_gensel3 && pt400Combined_3gen->passes(event) && pt10lep_3gensel->passes(event) && mass_3gensel->passes(event) && subjet_quality_3gensel->passes(event) && lepton_gensel->passes(event);

  pass_measurement2_gen_pt500 = pass_measurement2_gen && pt500_2gensel->passes(event);
  pass_measurement2_gen_pt600 = pass_measurement2_gen && pt600_2gensel->passes(event);
  pass_measurement2_gen_pt700 = pass_measurement2_gen && pt700_2gensel->passes(event);
  pass_measurement2_gen_pt800 = pass_measurement2_gen && pt800_2gensel->passes(event);
  pass_measurement2_gen_pt900 = pass_measurement2_gen && pt900_2gensel->passes(event);

  pass_measurement3_gen_pt500 = pass_measurement3_gen && pt500_3gensel->passes(event);
  pass_measurement3_gen_pt600 = pass_measurement3_gen && pt600_3gensel->passes(event);
  pass_measurement3_gen_pt700 = pass_measurement3_gen && pt700_3gensel->passes(event);
  pass_measurement3_gen_pt800 = pass_measurement3_gen && pt800_3gensel->passes(event);
  pass_measurement3_gen_pt900 = pass_measurement3_gen && pt900_3gensel->passes(event);

  pass_measurementSubPT_gen_pt500 = pass_measurementSubPT_gen && pt500_SubPTgensel->passes(event);
  pass_measurementSubPT_gen_pt600 = pass_measurementSubPT_gen && pt600_SubPTgensel->passes(event);
  pass_measurementSubPT_gen_pt700 = pass_measurementSubPT_gen && pt700_SubPTgensel->passes(event);
  pass_measurementSubPT_gen_pt800 = pass_measurementSubPT_gen && pt800_SubPTgensel->passes(event);
  pass_measurementSubPT_gen_pt900 = pass_measurementSubPT_gen && pt900_SubPTgensel->passes(event);

  // fill Hists
  if(pass_measurement2_gen) {
    h_GEN_XCone2->fill(event);
    if(top_2genmatch->passes(event)) h_GEN_XCone2_TopMatched->fill(event);
    else {
      h_GEN_XCone2_GluonMatched->fill(event);
      if(gluon_2genmatch->passes(event)) h_GEN_XCone2_GluonPartMatched->fill(event);
    }
    if(!tauCut42_2gen->passes(event)) h_GEN_XCone2_NotTauCut42->fill(event);
  }

  if(pass_measurement3_gen) {
    h_GEN_XCone3->fill(event);
    if(top_3genmatch->passes(event)) h_GEN_XCone3_TopMatched->fill(event);
    else h_GEN_XCone3_GluonMatched->fill(event);
    if(tauCut32_3gen->passes(event)) h_GEN_XCone3_TauCut32->fill(event);
    else h_GEN_XCone3_NotTauCut32->fill(event);
    if(tauCut42_3gen->passes(event)) h_GEN_XCone3_TauCut42->fill(event);
    else h_GEN_XCone3_NotTauCut42->fill(event);

    if(fullyMergedLeading_gen->passes(event)) h_GEN_XCone3_FullyMergedLeading->fill(event);
    if(fullyMergedSubleading_gen->passes(event)) h_GEN_XCone3_FullyMergedSubleading->fill(event);
  }

  if(passed_gensel3) {
    if(fullyMergedLeading_gen->passes(event)) h_GEN_XCone3_NoCutsFullyMergedLeading->fill(event);
    if(fullyMergedSubleading_gen->passes(event)) h_GEN_XCone3_NoCutsFullyMergedSubleading->fill(event);
  }

  if(pass_measurement3_gen_near) {
    h_GEN_XCone3_Near->fill(event);
  }

  if(pass_measurement3_gen_all) {
    h_GEN_XCone3_All->fill(event);
  }

  if(pass_measurementSubPT_gen) {
    h_GEN_XConeSubPT->fill(event);
    if(top_SubPTgenmatch->passes(event)) h_GEN_XConeSubPT_TopMatched->fill(event);
    else h_GEN_XConeSubPT_GluonMatched->fill(event);
  }

  if(pass_measurement2_gen_pt500) {
    h_GEN_XCone2_pt500->fill(event);
    if(top_2genmatch->passes(event)) h_GEN_XCone2_pt500_TopMatched->fill(event);
    else h_GEN_XCone2_pt500_GluonMatched->fill(event);
  }
  if(pass_measurement2_gen_pt600) {
    h_GEN_XCone2_pt600->fill(event);
    if(top_2genmatch->passes(event)) h_GEN_XCone2_pt600_TopMatched->fill(event);
    else h_GEN_XCone2_pt600_GluonMatched->fill(event);
  }
  if(pass_measurement2_gen_pt700) {
    h_GEN_XCone2_pt700->fill(event);
    if(top_2genmatch->passes(event)) h_GEN_XCone2_pt700_TopMatched->fill(event);
    else h_GEN_XCone2_pt700_GluonMatched->fill(event);
  }
  if(pass_measurement2_gen_pt800) {
    h_GEN_XCone2_pt800->fill(event);
    if(top_2genmatch->passes(event)) h_GEN_XCone2_pt800_TopMatched->fill(event);
    else h_GEN_XCone2_pt800_GluonMatched->fill(event);
  }
  if(pass_measurement2_gen_pt900) {
    h_GEN_XCone2_pt900->fill(event);
    if(top_2genmatch->passes(event)) h_GEN_XCone2_pt900_TopMatched->fill(event);
    else h_GEN_XCone2_pt900_GluonMatched->fill(event);
  }

  if(pass_measurement3_gen_pt500) {
    h_GEN_XCone3_pt500->fill(event);
    if(top_3genmatch->passes(event)) h_GEN_XCone3_pt500_TopMatched->fill(event);
    else h_GEN_XCone3_pt500_GluonMatched->fill(event);
    if(tauCut32_3gen->passes(event)) h_GEN_XCone3_pt500_TauCut32->fill(event);
    if(tauCut42_3gen->passes(event)) h_GEN_XCone3_pt500_TauCut42->fill(event);
  }
  if(pass_measurement3_gen_pt600) {
    h_GEN_XCone3_pt600->fill(event);
    if(top_3genmatch->passes(event)) h_GEN_XCone3_pt600_TopMatched->fill(event);
    else h_GEN_XCone3_pt600_GluonMatched->fill(event);
    if(tauCut32_3gen->passes(event)) h_GEN_XCone3_pt600_TauCut32->fill(event);
    if(tauCut42_3gen->passes(event)) h_GEN_XCone3_pt600_TauCut42->fill(event);
  }
  if(pass_measurement3_gen_pt700) {
    h_GEN_XCone3_pt700->fill(event);
    if(top_3genmatch->passes(event)) h_GEN_XCone3_pt700_TopMatched->fill(event);
    else h_GEN_XCone3_pt700_GluonMatched->fill(event);
    if(tauCut32_3gen->passes(event)) h_GEN_XCone3_pt700_TauCut32->fill(event);
    if(tauCut42_3gen->passes(event)) h_GEN_XCone3_pt700_TauCut42->fill(event);
  }
  if(pass_measurement3_gen_pt800) {
    h_GEN_XCone3_pt800->fill(event);
    if(top_3genmatch->passes(event)) h_GEN_XCone3_pt800_TopMatched->fill(event);
    else h_GEN_XCone3_pt800_GluonMatched->fill(event);
    if(tauCut32_3gen->passes(event)) h_GEN_XCone3_pt800_TauCut32->fill(event);
    if(tauCut42_3gen->passes(event)) h_GEN_XCone3_pt800_TauCut42->fill(event);
  }
  if(pass_measurement3_gen_pt900) {
    h_GEN_XCone3_pt900->fill(event);
    if(top_3genmatch->passes(event)) h_GEN_XCone3_pt900_TopMatched->fill(event);
    else h_GEN_XCone3_pt900_GluonMatched->fill(event);
    if(tauCut32_3gen->passes(event)) h_GEN_XCone3_pt900_TauCut32->fill(event);
    if(tauCut42_3gen->passes(event)) h_GEN_XCone3_pt900_TauCut42->fill(event);
  }

  if(pass_measurementSubPT_gen_pt500) h_GEN_XConeSubPT_pt500->fill(event);
  if(pass_measurementSubPT_gen_pt600) h_GEN_XConeSubPT_pt600->fill(event);
  if(pass_measurementSubPT_gen_pt700) h_GEN_XConeSubPT_pt700->fill(event);
  if(pass_measurementSubPT_gen_pt800) h_GEN_XConeSubPT_pt800->fill(event);
  if(pass_measurementSubPT_gen_pt900) h_GEN_XConeSubPT_pt900->fill(event);

  if(passed_gensel2 && pt330_2gensel->passes(event)) h_GEN_XCone2_sel->fill(event);
  if(passed_gensel2 && pt400_2gensel->passes(event)) h_GEN_XCone2_sel1->fill(event);
  if(passed_gensel2 && pt400_2gensel->passes(event) && pt10lep_2gensel->passes(event)) h_GEN_XCone2_sel2->fill(event);
  if(passed_gensel2 && pt400_2gensel->passes(event) && pt10lep_2gensel->passes(event) && mass_2gensel->passes(event)) h_GEN_XCone2_sel3->fill(event);
  if(passed_gensel2 && pt400_2gensel->passes(event) && pt10lep_2gensel->passes(event) && mass_2gensel->passes(event) && subjet_quality_2gensel->passes(event)) h_GEN_XCone2_sel4->fill(event);

  event.set(h_measure_gen, pass_measurement2_gen || pass_measurement3_gen);

  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(MTopJetPostSelection)
