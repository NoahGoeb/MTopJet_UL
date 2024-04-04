#pragma once
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/AnalysisModule.h"

#include <iostream>

using namespace std;

class WriteOutput: public uhh2::AnalysisModule{
public:

  explicit WriteOutput(uhh2::Context&);
  virtual bool process(uhh2::Event & ) override;

private:
  uhh2::Event::Handle<double>h_weight;


};
