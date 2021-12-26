#include "rate_constant.h"

namespace chem {

RateConstant::RateConstant() {}

void RateConstant::set_config(const Config& config) { config_ = config; }

double RateConstant::get_rate_constant(const double& temperature) const {
    double rate_constant = 0.0;

    switch (config_.type) {
        case CONSTANT: {
            rate_constant = config_.value;
            break;
        }
        case VARIABLE: {
            rate_constant = algorithms::arrhenius(config_.pre_exp_factor, config_.activation_energy, temperature);
            break;
        }
    }

    return rate_constant;
}

}  // namespace chem
