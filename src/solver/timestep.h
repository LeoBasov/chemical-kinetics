#pragma once

#include <Eigen/Dense>

#include "algorithms.h"

namespace chem {
using namespace Eigen;

class TimeStep {
   public:
    enum Type { CONSTANT, VARIABLE };

    TimeStep();
    ~TimeStep() = default;

    double calc_dt(const VectorXd& concentrations, const VectorXd& dX_dt);
    double get_last_dt() const;

   private:
    Type type_ = CONSTANT;
    double value_ = 1.0;
    double last_dt_ = 0.0;
};

}  // namespace chem
