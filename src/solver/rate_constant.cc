#include "rate_constant.h"

namespace chem {

RateConstant::RateConstant() {}

double RateConstant::get_rate_constant(const double& temperature) const {
    double rate_constant = 0.0;

    switch (type) {
        case CONSTANT: {
            rate_constant = value;
            break;
        }
        case VARIABLE: {
            rate_constant = algorithms::arrhenius(pre_exp_factor, activation_energy, temperature);
            break;
        }
    }

    return rate_constant;
}

}  // namespace chem
