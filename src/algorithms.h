#pragma once

#include <cmath>

#include "constants.h"

namespace chem {
namespace algorithms {

// [activation_energy] = R⋅T
double arrhenius(const double& pre_exp_factor, const double& activation_energy, const double& temperature);

}  // namespace algorithms
}  // namespace chem
