#pragma once

#include "algorithms.h"

namespace chem {

struct RateConstant {
    enum Type { CONSTANT, VARIABLE };

    RateConstant();

    Type type = CONSTANT;
    double value = 0.0;
    double temperature_exponent = 0.0;
    double pre_exp_factor = 0.0;
    double activation_energy = 0.0;

    double get_rate_constant(const double& temperature) const;
};

}  // namespace chem
