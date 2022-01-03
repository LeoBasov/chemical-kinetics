#pragma once

#include <Eigen/Dense>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

#include "../exception/exception.h"
#include "../utilities/constants.h"

namespace chem {
namespace algorithms {
using namespace Eigen;

// [activation_energy] = R⋅T
double arrhenius(const double& temperature_exponent, const double& pre_exp_factor, const double& activation_energy,
                 const double& temperature);
VectorXd calc_reaction_rates(const VectorXd& rate_constants, const VectorXd& concentrations,
                             const MatrixXd& reaction_powers);
double calc_time_step(const VectorXd& concentrations, const VectorXd& dX_dt, const double& factor);
double calc_total_heat_capcity(const VectorXd& concentrations, const VectorXd& heat_capacities);

}  // namespace algorithms
}  // namespace chem
