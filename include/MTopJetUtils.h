#pragma once

#include <UHH2/core/include/Event.h>

////

const Particle* leading_lepton(const uhh2::Event&);

////

std::vector<GenParticle> outgoingGluons(const uhh2::Event&);

////