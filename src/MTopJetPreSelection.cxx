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
#include <UHH2/MTopJet_UL/include/RecoSelections.h>
#include <UHH2/MTopJet_UL/include/GenSelections.h>

using namespace std;

class MTopJetPreSelection : public ModuleBASE {

public:
  explicit MTopJetPreSelection(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;

protected:

  // selections
  std::unique_ptr<uhh2::Selection> lumi_sel;

  std::unique_ptr<uhh2::Selection> genmttbar_sel;
  std::unique_ptr<uhh2::Selection> met_sel;
  std::unique_ptr<uhh2::Selection> muon_sel;
  std::unique_ptr<uhh2::Selection> elec_sel;
  std::unique_ptr<uhh2::Selection> SemiLepDecay;
  std::unique_ptr<uhh2::Selection> GenMuonPT;
  std::unique_ptr<uhh2::Selection> GenElecPT;

  std::unique_ptr<uhh2::AnalysisModule> ttgenprod;

  // handles for output
  Event::Handle<bool>h_recsel;
  Event::Handle<bool>h_gensel;
  Event::Handle<std::vector<TopJet>>h_fatjets;

  // bools
  bool isMC;
  bool isTTbar;
  bool debug;
  
};

/*
███    ███  ██████  ██████  ██    ██ ██      ███████
████  ████ ██    ██ ██   ██ ██    ██ ██      ██
██ ████ ██ ██    ██ ██   ██ ██    ██ ██      █████
██  ██  ██ ██    ██ ██   ██ ██    ██ ██      ██
██      ██  ██████  ██████   ██████  ███████ ███████
*/

MTopJetPreSelection::MTopJetPreSelection(uhh2::Context& ctx){

  debug = string2bool(ctx.get("Debug","false")); // look for Debug, expect false if not found

  //// CONFIGURATION
  if(debug) cout << "Configuration" << endl;

  isMC = (ctx.get("dataset_type") == "MC"); 

  TString dataset_version = (TString) ctx.get("dataset_version");
  if(dataset_version.Contains("TTbar") || dataset_version.Contains("TTTo")) isTTbar = true;
  else  isTTbar = false;

  //// HANDLES
  if(debug) cout << "Output and Handles" << endl;

  h_recsel = ctx.declare_event_output<bool>("passed_recsel");
  h_gensel = ctx.declare_event_output<bool>("passed_gensel");

  h_fatjets = ctx.get_handle<std::vector<TopJet>>("xconeCHS");

  //// COMMON MODULES
  
  if(debug) cout << "Common Modules" << endl;

  if(!isMC) lumi_sel.reset(new LumiSelection(ctx));

  /* GEN M-ttbar selection [TTbar MC "0.<M^{gen}_{ttbar}(GeV)<700.] */
  if(debug) cout << "TTbarGenProducer" << endl;

  const std::string ttbar_gen_label("ttbargen");

  ttgenprod.reset(new TTbarGenProducer(ctx, ttbar_gen_label, false));

  TString samplename = ctx.get("dataset_version");
  if( samplename.Contains("Mtt0000to0700") ){
    genmttbar_sel.reset(new MttbarGenSelection(0., 700.));
  }
  else{
    genmttbar_sel.reset(new uhh2::AndSelection(ctx));
  }

  //// EVENT SELECTION REC
  met_sel.reset(new METCut(40, uhh2::infinity));
  muon_sel.reset(new NMuonSelection(1, -1, MuonId(PtEtaCut(50, 2.4 ))));
  elec_sel.reset(new NElectronSelection(1, -1, ElectronId(PtEtaCut(50, 2.4))));

  //// EVENTS SELECTION GEN
  SemiLepDecay.reset(new TTbarSemilep(ctx));
  if(isMC){
    GenMuonPT.reset(new GenMuonSel(ctx, 55.));
    GenElecPT.reset(new GenElecSel(ctx, 55.));
  }

}

/*
██████  ██████   ██████   ██████ ███████ ███████ ███████
██   ██ ██   ██ ██    ██ ██      ██      ██      ██
██████  ██████  ██    ██ ██      █████   ███████ ███████
██      ██   ██ ██    ██ ██      ██           ██      ██
██      ██   ██  ██████   ██████ ███████ ███████ ███████
*/

bool MTopJetPreSelection::process(uhh2::Event& event){

  if(debug) cout << "Start Module - Process" << endl;

  /* CMS-certified luminosity sections */
  if(event.isRealData){
    if(!lumi_sel->passes(event)) return false;
  }

  if(!event.isRealData){
    /* GEN M-ttbar selection */
    ttgenprod->process(event);
    if(!genmttbar_sel->passes(event)) return false;
  }

  //// EVENT SELECTION REC
  bool passed_recsel;

  bool pass_lep_number = ((event.muons->size() >= 1) || (event.electrons->size() >= 1));
  bool pass_lepsel = (muon_sel->passes(event) || elec_sel->passes(event));
  bool pass_met = met_sel->passes(event);

  // cut on fatjet pt
  bool passed_fatpt=false;
  std::vector<TopJet> jets = event.get(h_fatjets);
  double ptcut = 200;
  for(auto jet: jets){
    if(jet.pt() > ptcut) passed_fatpt = true;
  }

  if(pass_lep_number && pass_met && pass_lepsel && passed_fatpt) passed_recsel = true;
  else passed_recsel = false;

  //// EVNET SELECTION GEN
  bool passed_gensel;

  bool pass_semilep;
  if(isMC) pass_semilep = SemiLepDecay->passes(event);
  else pass_semilep=false;

  bool pass_genlepton = false;
  bool pass_genmuon = false;
  bool pass_genelec = false;

  if(isMC){
    pass_genmuon = GenMuonPT->passes(event);
    pass_genelec = GenElecPT->passes(event);
  }

  if(pass_genmuon || pass_genelec) pass_genlepton = true;

  if(pass_semilep && pass_genlepton) passed_gensel = true;
  else passed_gensel = false;

  if(!passed_recsel && !passed_gensel) return false;

  event.set(h_recsel, passed_recsel);
  event.set(h_gensel, passed_gensel);

  return true;

}

UHH2_REGISTER_ANALYSIS_MODULE(MTopJetPreSelection)
