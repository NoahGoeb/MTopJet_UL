#include <UHH2/MTopJet_UL/include/GenHists.h>

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

#include "TLorentzVector.h"

using namespace uhh2;


const int max_m = 500;
const int min_m = 0;
const int n_massbins = 50;

bool printOut = false;

GenHists::GenHists(uhh2::Context & ctx, const std::string & dirname, const std::string & jetname): Hists(ctx, dirname){
  // book all histograms here
  GenJetMass = book<TH1F>("GenJet_Mass", "M_{jet}", n_massbins, 0, max_m);
  GenJetNumber = book<TH1F>("GenJet_Number", "N_{jets}", 5, 0, 4);


  // handle for clustered jets
  h_jets=ctx.get_handle<std::vector<GenTopJet>>(jetname);

  debug = string2bool(ctx.get("Debug","false"));
}

void GenHists::fill(const Event & event){

  if(debug) cout << "--- fill GenHists ---" << endl;

  //---------------------------------------------------------------------------------------
  //--------------------------------- define needed objects-----------------------------------
  //---------------------------------------------------------------------------------------
  if(debug) cout << "\t--- define needed objects" << endl;

  double genweight = event.weight;

  std::vector<GenTopJet> jets = event.get(h_jets);
  TLorentzVector jeti_v4;
  std::vector<TLorentzVector> jets_v4;

  for(uint i=0; i<jets.size(); i++) {
    jeti_v4.SetPxPyPzE(jets.at(i).v4().Px(), jets.at(i).v4().Py(), jets.at(i).v4().Pz(), jets.at(i).v4().E());
    jets_v4.push_back(jeti_v4);
  }

  //---------------------------------------------------------------------------------------
  //--------------------------------- Fill Hists here -------------------------------------
  //---------------------------------------------------------------------------------------

  if(debug) cout << "\t--- Fill Hists" << endl;

  GenJetNumber->Fill(jets.size(), genweight);

  if(jets.size() > 0) {
    GenJetMass->Fill(jets_v4.at(0).M(), genweight);
  }

  
  //---------------------------------------------------------------------------------------
  //--------------------------------- Clear all used objects ------------------------------
  //---------------------------------------------------------------------------------------
  if(debug) cout << "\t--- Clear all used objects" << endl;
  jeti_v4.Delete();

}
