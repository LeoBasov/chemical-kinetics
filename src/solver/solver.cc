#include "solver.h"

namespace chem {

Solver::Solver() {}

void Solver::execute() {
    // calc rate constants
    const VectorXd reaction_rates =
        algorithms::calc_reaction_rates(rate_constants_, state_.concentrations, reaction_powers_);
    const VectorXd dX_dt = stochiometric_matrix_ * reaction_rates;

    state_.concentrations += dX_dt * time_step_.calc_dt(state_.concentrations, dX_dt);
    state_.time += time_step_.get_last_dt();
    // calc temperature
}

Solver::State Solver::get_state() const { return state_; }

}  // namespace chem
