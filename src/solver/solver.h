#pragma once

#include "algorithms.h"
#include "rate_constant.h"
#include "thermal.h"
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
    MatrixXd reaction_powers_;
    MatrixXd stochiometric_matrix_;
    TimeStep time_step_;
    std::vector<RateConstant> rate_constants_;

    VectorXd calc_rate_constants() const;
};
}  // namespace chem
