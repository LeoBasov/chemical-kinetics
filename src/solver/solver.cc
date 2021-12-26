#include "solver.h"

namespace chem {

Solver::Solver() {}

void Solver::execute() {
    // calc rate constants
    const VectorXd reaction_rates = algorithms::calc_reaction_rates(rate_constants_, concentrations_, reaction_powers_);
    const VectorXd dX_dt = stochiometric_matrix_ * reaction_rates;
    const double time_step = time_step_.get_dt(concentrations_, dX_dt);

    concentrations_ += dX_dt * time_step;
    // calc temperature
}

}  // namespace chem
