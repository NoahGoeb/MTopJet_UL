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
  
}
