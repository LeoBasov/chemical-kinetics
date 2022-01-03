#include "algorithms.h"

namespace chem {
namespace algorithms {

double arrhenius(const double& temperature_exponent, const double& pre_exp_factor, const double& activation_energy,
                 const double& temperature) {
    return std::pow(temperature, temperature_exponent) * pre_exp_factor *
           std::exp(-activation_energy / (constants::R * temperature));
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

double calc_time_step(const VectorXd& concentrations, const VectorXd& dX_dt, const double& factor) {
    double value = std::numeric_limits<double>::max();

    if (concentrations.size() != dX_dt.size()) {
        throw Exception("arrays of incompatible size", __PRETTY_FUNCTION__);
    }

    for (long i = 0; i < concentrations.size(); i++) {
        const double new_val(std::abs(concentrations(i) / dX_dt(i)));

        if (new_val < value && new_val > 0.0) {
            value = new_val;
        }
    }

    return factor * value;
}

}  // namespace algorithms
}  // namespace chem
