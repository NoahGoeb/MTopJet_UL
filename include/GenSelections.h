#pragma once

#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/Selection.h>

#include <UHH2/common/include/TTbarGen.h>

using namespace std;


namespace uhh2 {

  class TTbarSemilep : public Selection {

  public:
    explicit TTbarSemilep(Context&);
    virtual bool passes(const Event&) override;

  protected:
    uhh2::Event::Handle<TTbarGen> h_ttbargen;

  };

  class GenMuonSel : public Selection {

  public:
    explicit GenMuonSel(Context&, double);
    virtual bool passes(const Event&) override;

  protected:
    double ptmin;
    uhh2::Event::Handle<TTbarGen> h_ttbargen;
  };

  class GenElecSel : public Selection {

  public:
    explicit GenElecSel(Context&, double);
    virtual bool passes(const Event&) override;

  protected:
    double ptmin;
    uhh2::Event::Handle<TTbarGen> h_ttbargen;
  };

  class LeadingJetPT_gen : public Selection {

  public:
    explicit LeadingJetPT_gen(Context&, const std::string &, float);
    virtual bool passes(const Event&) override;

  private:
    uhh2::Event::Handle<std::vector<GenTopJet>> h_jets;
    float ptcut_;
  };

  class MassCut2_gen : public Selection {

  public:
    explicit MassCut2_gen(Context&, const std::string &, const std::string &);
    virtual bool passes(const Event&) override;

  private:
    uhh2::Event::Handle<std::vector<GenTopJet>> h_hadjets;
    uhh2::Event::Handle<std::vector<GenTopJet>> h_lepjets;
    uhh2::Event::Handle<TTbarGen> h_ttbargen;
  };

  class MassCut3_gen : public Selection {

  public:
    explicit MassCut3_gen(Context&, const std::string &, const std::string &, float);
    virtual bool passes(const Event&) override;

  private:
    uhh2::Event::Handle<std::vector<GenTopJet>> h_hadjets;
    uhh2::Event::Handle<std::vector<GenTopJet>> h_lepjets;
    uhh2::Event::Handle<TTbarGen> h_ttbargen;
    float dR_;
  };

  class SubjetQuality_gen : public Selection {

  public:
    explicit SubjetQuality_gen(Context&, const std::string &, float, float);
    virtual bool passes(const Event&) override;

  private:
    uhh2::Event::Handle<std::vector<GenTopJet>> h_jets;
    float ptmin, etamax;
  };

  class NoNearJet_gen : public Selection {

  public:
    explicit NoNearJet_gen(Context&, const std::string &, float);
    virtual bool passes(const Event&) override;

  private:
    uhh2::Event::Handle<std::vector<GenTopJet>> h_jets;
    float dR;
  };
  
  
}
