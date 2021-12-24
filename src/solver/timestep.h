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

    double get_dt(const VectorXd& concentrations, const VectorXd& dX_dt) const;

   private:
    Type type_ = CONSTANT;
    double value_ = 1.0;
};

}  // namespace chem
