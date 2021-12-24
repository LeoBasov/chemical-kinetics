#pragma once

#include <Eigen/Dense>
#include <cmath>
#include <iostream>
#include <vector>

#include "constants.h"
#include "exception/exception.h"

namespace chem {
namespace algorithms {
using namespace Eigen;

// [activation_energy] = R⋅T
double arrhenius(const double& pre_exp_factor, const double& activation_energy, const double& temperature);
VectorXd calc_reaction_rates(const VectorXd& rate_constants, const VectorXd& concentrations,
                             const MatrixXd& reaction_powers);

}  // namespace algorithms
}  // namespace chem
