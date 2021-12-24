#pragma once

#include "algorithms.h"

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
};
}  // namespace chem
