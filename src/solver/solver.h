#pragma once

#include "algorithms.h"
#include "timestep.h"

namespace chem {
using namespace Eigen;

class Solver {
   public:
    Solver();
    ~Solver() = default;

    void execute();

   private:
    std::vector<double> dts_;
    std::vector<VectorXd> concentrations_;
    VectorXd rate_constants_;
    MatrixXd reaction_powers_;
    MatrixXd stochiometric_matrix_;
    TimeStep time_step_;
};
}  // namespace chem
