#include "algorithms.h"

namespace chem {
namespace algorithms {

double arrhenius(const double& pre_exp_factor, const double& activation_energy, const double& temperature) {
    return pre_exp_factor * std::exp(-activation_energy / (constants::R * temperature));
}

}  // namespace algorithms
}  // namespace chem
