#pragma once

#include <Eigen/Dense>

#include "algorithms.h"

namespace chem {
using namespace Eigen;

struct TimeStep {
    enum Type { CONSTANT, VARIABLE };

    TimeStep();
    ~TimeStep() = default;

    double calc_dt(const VectorXd& concentrations, const VectorXd& dX_dt);
    double get_last_dt() const;

    Type type = CONSTANT;
    double value = 1.0;
    double last_dt = 0.0;
};

}  // namespace chem
