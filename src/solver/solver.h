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

    void set_concentrations(const VectorXd& concentrations);
    void set_reaction_powers(const MatrixXd& reaction_powers);
    void set_stochiometric_matrix(const MatrixXd& stochiometric_matrix);
    void set_heat_capacities(const VectorXd& heat_capacities);
    void set_enthalpies(const VectorXd& enthalpies);
    void set_time_step(const TimeStep& time_step);
    void set_rate_constants(const std::vector<RateConstant>& rate_constants);
    void set_thermal(const Thermal& thermal);

   private:
    State state_;
    MatrixXd reaction_powers_;
    MatrixXd stochiometric_matrix_;
    VectorXd heat_capacities_;
    VectorXd enthalpies_;
    TimeStep time_step_;
    std::vector<RateConstant> rate_constants_;
    Thermal thermal_;

    VectorXd calc_rate_constants() const;
};
}  // namespace chem
