#include "solver.h"

namespace chem {

Solver::Solver() {}

void Solver::execute() {
    const VectorXd reaction_rates =
        algorithms::calc_reaction_rates(rate_constants_, concentrations_.back(), reaction_powers_);
    const VectorXd dX_dt = stochiometric_matrix_ * reaction_rates;
}

}  // namespace chem
