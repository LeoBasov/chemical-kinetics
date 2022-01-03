#pragma once

#include "algorithms.h"

namespace chem {
using namespace Eigen;

class Thermal {
   public:
    enum Type { CONSTANT, VARIABLE };

    Thermal();
    ~Thermal() = default;

    Type type = CONSTANT;
    double temperature = 0.0;

    double calc_temperature(const VectorXd& concentrations, const VectorXd& heat_capacities, const VectorXd& dX,
                            const VectorXd& enthalpies);
    double get_last_temperature() const;

   private:
    double heat_capacity_ = 0.0;
};

}  // namespace chem
