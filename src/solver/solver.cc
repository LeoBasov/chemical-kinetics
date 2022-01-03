#include "solver.h"

namespace chem {

Solver::Solver() {}

void Solver::execute() {
    const VectorXd rate_constants = calc_rate_constants();
    const VectorXd reaction_rates =
        algorithms::calc_reaction_rates(rate_constants, state_.concentrations, reaction_powers_);
    const VectorXd dX_dt = stochiometric_matrix_ * reaction_rates;
    const VectorXd dX = dX_dt * time_step_.calc_dt(state_.concentrations, dX_dt);

    state_.concentrations += dX;
    state_.time += time_step_.get_last_dt();
    state_.temperature = thermal_.value;  // TODO: implement variable temperature
}

Solver::State Solver::get_state() const { return state_; }

void Solver::set_concentrations(const VectorXd& concentrations) { state_.concentrations = concentrations; }

void Solver::set_reaction_powers(const MatrixXd& reaction_powers) { reaction_powers_ = reaction_powers; }

void Solver::set_stochiometric_matrix(const MatrixXd& stochiometric_matrix) {
    stochiometric_matrix_ = stochiometric_matrix;
}

void Solver::set_time_step(const TimeStep& time_step) { time_step_ = time_step; }

void Solver::set_rate_constants(const std::vector<RateConstant>& rate_constants) { rate_constants_ = rate_constants; }

void Solver::set_thermal(const Thermal& thermal) {
    thermal_ = thermal;
    state_.temperature = thermal_.value;  // TODO: implement variable temperature
}

VectorXd Solver::calc_rate_constants() const {
    VectorXd rate_constants(rate_constants_.size());

    for (long i = 0; i < rate_constants.size(); i++) {
        rate_constants(i) = rate_constants_.at(i).get_rate_constant(thermal_.value);
    }

    return rate_constants;
}

}  // namespace chem
