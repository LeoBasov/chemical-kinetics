#pragma once

#include "algorithms.h"

namespace chem {

class RateConstant {
   public:
    enum Type { CONSTANT, VARIABLE };

    struct Config {
        Type type = CONSTANT;
        double value = 0.0;
        double pre_exp_factor = 0.0;
        double activation_energy = 0.0;
    };

    RateConstant();
    ~RateConstant() = default;

    void set_config(const Config& config);
    double get_rate_constant(const double& temperature) const;

   private:
    Config config_;
};

}  // namespace chem
