#include "solver.h"

namespace chem {

Solver::Solver() {}

void Solver::execute() {
    const VectorXd rate_constants = calc_rate_constants();
    const VectorXd reaction_rates =
        algorithms::calc_reaction_rates(rate_constants, state_.concentrations, reaction_powers_);
    const VectorXd dX_dt = stochiometric_matrix_ * reaction_rates;

    state_.concentrations += dX_dt * time_step_.calc_dt(state_.concentrations, dX_dt);
    state_.time += time_step_.get_last_dt();
    // calc temperature
}

Solver::State Solver::get_state() const { return state_; }

VectorXd Solver::calc_rate_constants() const {
    VectorXd rate_constants;

    return rate_constants;
}

}  // namespace chem
