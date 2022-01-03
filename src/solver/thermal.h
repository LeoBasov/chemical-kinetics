#pragma once

#include "algorithms.h"

namespace chem {
using namespace Eigen;

class Thermal {
   public:
    enum Type { CONSTANT, VARIABLE };

    Thermal();
    ~Thermal() = default;

    void set_type(Type type);
    void set_temperature(const double& temperature);

    double calc_temperature(const VectorXd& concentrations, const VectorXd& heat_capacities, const VectorXd& dX,
                            const VectorXd& enthalpies);
    double get_temperature() const;
    Type get_type() const;

   private:
    Type type_ = CONSTANT;
    double temperature_ = 0.0;
    double heat_capacity_ = 0.0;
};

}  // namespace chem
