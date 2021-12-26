#include "solver.h"

namespace chem {

Solver::Solver() {}

void Solver::execute() {
    // calc rate constants
    const VectorXd reaction_rates = algorithms::calc_reaction_rates(rate_constants_, concentrations_, reaction_powers_);
    const VectorXd dX_dt = stochiometric_matrix_ * reaction_rates;

    concentrations_ += dX_dt * time_step_.calc_dt(concentrations_, dX_dt);
    // calc temperature
}

}  // namespace chem
