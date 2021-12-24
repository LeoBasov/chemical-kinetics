#include "algorithms.h"

namespace chem {
namespace algorithms {

double arrhenius(const double& pre_exp_factor, const double& activation_energy, const double& temperature) {
    return pre_exp_factor * std::exp(-activation_energy / (constants::R * temperature));
}

VectorXd calc_reaction_rates(const VectorXd& rate_constants, const VectorXd& concentrations,
                             const MatrixXd& reaction_powers) {
    VectorXd reaction_rates(rate_constants);

    if (reaction_rates.size() * concentrations.size() != reaction_powers.size()) {
        throw Exception("arrays of incompatible size", __PRETTY_FUNCTION__);
    }

    for (long j = 0; j < reaction_rates.size(); j++) {
        for (long i = 0; i < concentrations.size(); i++) {
            reaction_rates(j) *= std::pow(concentrations(i), reaction_powers(j, i));
        }
    }

    return reaction_rates;
}

}  // namespace algorithms
}  // namespace chem
