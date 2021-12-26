#pragma once

#include "algorithms.h"
#include "timestep.h"

namespace chem {
using namespace Eigen;

class Solver {
   public:
    struct State {
        VectorXd concentrations;
        double time = 0.0;
        double temperature = 0.0;
    };

   public:
    Solver();
    ~Solver() = default;

    void execute();
    State get_state() const;

   private:
    State state_;
    VectorXd rate_constants_;
    MatrixXd reaction_powers_;
    MatrixXd stochiometric_matrix_;
    TimeStep time_step_;
};
}  // namespace chem
