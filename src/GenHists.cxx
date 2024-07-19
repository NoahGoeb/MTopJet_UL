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

  GenJetTau1 = book<TH1F>("GenJet_Tau1", "Tau1_{jet}", 50, 0, 1);
  GenJetTau2 = book<TH1F>("GenJet_Tau2", "Tau2_{jet}", 50, 0, 1);
  GenJetTau3 = book<TH1F>("GenJet_Tau3", "Tau3_{jet}", 50, 0, 1);
  GenJetTau4 = book<TH1F>("GenJet_Tau4", "Tau4_{jet}", 50, 0, 1);

  GenJetTau2Tau1 = book<TH1F>("GenJet_Tau2Tau1", "(Tau2/Tau1)_{jet}", 50, 0, 1);
  GenJetTau3Tau2 = book<TH1F>("GenJet_Tau3Tau2", "(Tau3/Tau2)_{jet}", 50, 0, 1);
  GenJetTau3Tau1 = book<TH1F>("GenJet_Tau3Tau1", "(Tau3/Tau1)_{jet}", 50, 0, 1);
  GenJetTau4Tau3 = book<TH1F>("GenJet_Tau4Tau3", "(Tau4/Tau3)_{jet}", 50, 0, 1);
  GenJetTau4Tau2 = book<TH1F>("GenJet_Tau4Tau2", "(Tau4/Tau2)_{jet}", 50, 0, 1);
  GenJetTau4Tau1 = book<TH1F>("GenJet_Tau4Tau1", "(Tau4/Tau1)_{jet}", 50, 0, 1);

  GenJetGroomedTau1 = book<TH1F>("GenJetGroomed_Tau1", "Tau1_{jetGroomed}", 50, 0, 1);
  GenJetGroomedTau2 = book<TH1F>("GenJetGroomed_Tau2", "Tau2_{jetGroomed}", 50, 0, 1);
  GenJetGroomedTau3 = book<TH1F>("GenJetGroomed_Tau3", "Tau3_{jetGroomed}", 50, 0, 1);
  GenJetGroomedTau4 = book<TH1F>("GenJetGroomed_Tau4", "Tau4_{jetGroomed}", 50, 0, 1);

  GenJetGroomedTau2Tau1 = book<TH1F>("GenJetGroomed_Tau2Tau1", "(Tau2/Tau1)_{jetGroomed}", 50, 0, 1);
  GenJetGroomedTau3Tau2 = book<TH1F>("GenJetGroomed_Tau3Tau2", "(Tau3/Tau2)_{jetGroomed}", 50, 0, 1);
  GenJetGroomedTau3Tau1 = book<TH1F>("GenJetGroomed_Tau3Tau1", "(Tau3/Tau1)_{jetGroomed}", 50, 0, 1);
  GenJetGroomedTau4Tau3 = book<TH1F>("GenJetGroomed_Tau4Tau3", "(Tau4/Tau3)_{jetGroomed}", 50, 0, 1);
  GenJetGroomedTau4Tau2 = book<TH1F>("GenJetGroomed_Tau4Tau2", "(Tau4/Tau2)_{jetGroomed}", 50, 0, 1);
  GenJetGroomedTau4Tau1 = book<TH1F>("GenJetGroomed_Tau4Tau1", "(Tau4/Tau1)_{jetGroomed}", 50, 0, 1);

  GenDeltaRJets12 = book<TH1F>("GenDeltaR_Jets12", "deltaR_{jets12}", 50, 0, 4);
  
  GenJetMassTop = book<TH1F>("GenJet_MassTop", "M_{topjet}", n_massbins, 0, max_m);
  GenJetMassGluon = book<TH1F>("GenJet_MassGluon", "M_{gluonjet}", n_massbins, 0, max_m);

  GenJetMassTau32Cut = book<TH1F>("GenJet_MassTau32Cut", "M_{tau32Cut}", n_massbins, 0, max_m);
  GenJetMassTau42Cut = book<TH1F>("GenJet_MassTau42Cut", "M_{tau42Cut}", n_massbins, 0, max_m);
  
  GenJetMassGroomedTau32Cut = book<TH1F>("GenJet_MassGroomedTau32Cut", "M_{groomedTau32Cut}", n_massbins, 0, max_m);
  GenJetMassGroomedTau42Cut = book<TH1F>("GenJet_MassGroomedTau42Cut", "M_{groomedTau42Cut}", n_massbins, 0, max_m);

  GenJetMassCombined = book<TH1F>("GenJet_MassCombined", "M_{jetCombined}", n_massbins, 0, max_m);

  // handle for ttbargen class
  h_ttbargen=ctx.get_handle<TTbarGen>("ttbargen");
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

  const auto & ttbargen = event.get(h_ttbargen);

  double genweight = event.weight;
  //genweight = 1;

  std::vector<GenTopJet> jets = event.get(h_jets);
  TLorentzVector jeti_v4;
  std::vector<TLorentzVector> jets_v4;

  for(uint i=0; i<jets.size(); i++) {
    jeti_v4.SetPxPyPzE(jets.at(i).v4().Px(), jets.at(i).v4().Py(), jets.at(i).v4().Pz(), jets.at(i).v4().E());
    jets_v4.push_back(jeti_v4);
  }

  GenParticle top;
  if(jets.size() > 0){
    if(ttbargen.IsTopHadronicDecay()){
      top = ttbargen.Top();
    }
    else if(ttbargen.IsAntiTopHadronicDecay()){
      top = ttbargen.Antitop();
    }
  }

  //---------------------------------------------------------------------------------------
  //--------------------------------- Fill Hists here -------------------------------------
  //---------------------------------------------------------------------------------------

  if(debug) cout << "\t--- Fill Hists" << endl;

  GenJetNumber->Fill(jets.size(), genweight);

  if(jets.size() > 1) {
    GenDeltaRJets12->Fill(deltaR(jets.at(0), jets.at(1)), genweight);

    TLorentzVector jet_v4_combined = jets_v4.at(0) + jets_v4.at(1);
    GenJetMassCombined->Fill(jet_v4_combined.M(), genweight);
  }

  if(jets.size() > 0) {
    GenJetMass->Fill(jets_v4.at(0).M(), genweight);

    GenJetTau1->Fill(jets.at(0).tau1(), genweight);
    GenJetTau2->Fill(jets.at(0).tau2(), genweight);
    GenJetTau3->Fill(jets.at(0).tau3(), genweight);
    GenJetTau4->Fill(jets.at(0).tau4(), genweight);

    if(jets.at(0).tau1() != 0) GenJetTau2Tau1->Fill(jets.at(0).tau2()/jets.at(0).tau1(), genweight);
    if(jets.at(0).tau2() != 0) GenJetTau3Tau2->Fill(jets.at(0).tau3()/jets.at(0).tau2(), genweight);
    if(jets.at(0).tau1() != 0) GenJetTau3Tau1->Fill(jets.at(0).tau3()/jets.at(0).tau1(), genweight);
    if(jets.at(0).tau3() != 0) GenJetTau4Tau3->Fill(jets.at(0).tau4()/jets.at(0).tau3(), genweight);
    if(jets.at(0).tau2() != 0) GenJetTau4Tau2->Fill(jets.at(0).tau4()/jets.at(0).tau2(), genweight);
    if(jets.at(0).tau1() != 0) GenJetTau4Tau1->Fill(jets.at(0).tau4()/jets.at(0).tau1(), genweight);

    GenJetGroomedTau1->Fill(jets.at(0).tau1_groomed(), genweight);
    GenJetGroomedTau2->Fill(jets.at(0).tau2_groomed(), genweight);
    GenJetGroomedTau3->Fill(jets.at(0).tau3_groomed(), genweight);
    GenJetGroomedTau4->Fill(jets.at(0).tau4_groomed(), genweight);

    if(jets.at(0).tau1_groomed() != 0) GenJetGroomedTau2Tau1->Fill(jets.at(0).tau2_groomed()/jets.at(0).tau1_groomed(), genweight);
    if(jets.at(0).tau2_groomed() != 0) GenJetGroomedTau3Tau2->Fill(jets.at(0).tau3_groomed()/jets.at(0).tau2_groomed(), genweight);
    if(jets.at(0).tau1_groomed() != 0) GenJetGroomedTau3Tau1->Fill(jets.at(0).tau3_groomed()/jets.at(0).tau1_groomed(), genweight);
    if(jets.at(0).tau3_groomed() != 0) GenJetGroomedTau4Tau3->Fill(jets.at(0).tau4_groomed()/jets.at(0).tau3_groomed(), genweight);
    if(jets.at(0).tau2_groomed() != 0) GenJetGroomedTau4Tau2->Fill(jets.at(0).tau4_groomed()/jets.at(0).tau2_groomed(), genweight);
    if(jets.at(0).tau1_groomed() != 0) GenJetGroomedTau4Tau1->Fill(jets.at(0).tau4_groomed()/jets.at(0).tau1_groomed(), genweight);

    if(deltaR(jets.at(0), top) < 1.2) GenJetMassTop->Fill(jets_v4.at(0).M(), genweight);
    else GenJetMassGluon->Fill(jets_v4.at(0).M(), genweight);

    if(jets.at(0).tau2() != 0 && jets.at(0).tau3()/jets.at(0).tau2() < 0.58) GenJetMassTau32Cut->Fill(jets_v4.at(0).M(), genweight);
    if(jets.at(0).tau2() != 0 && jets.at(0).tau4()/jets.at(0).tau2() < 0.46) GenJetMassTau42Cut->Fill(jets_v4.at(0).M(), genweight);

    if(jets.at(0).tau2_groomed() != 0 && jets.at(0).tau3_groomed()/jets.at(0).tau2_groomed() < 0.58) GenJetMassGroomedTau32Cut->Fill(jets_v4.at(0).M(), genweight);
    if(jets.at(0).tau2_groomed() != 0 && jets.at(0).tau4_groomed()/jets.at(0).tau2_groomed() < 0.46) GenJetMassGroomedTau42Cut->Fill(jets_v4.at(0).M(), genweight);

  }
  
  //---------------------------------------------------------------------------------------
  //--------------------------------- Clear all used objects ------------------------------
  //---------------------------------------------------------------------------------------
  if(debug) cout << "\t--- Clear all used objects" << endl;
  jeti_v4.Delete();

}
