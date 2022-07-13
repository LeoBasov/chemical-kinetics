#include "solver.h"

namespace chem {

Solver::Solver() {}

void Solver::execute() {
    switch (type_) {
        case MASTER_EQUATION: {
            execute_master_equation();
            break;
        }
        case FOKKER_PLANCK: {
            execute_fokker_planck();
            break;
        }
        default: {
            break;
        }
    }
}

Solver::State Solver::get_state() const { return state_; }

void Solver::set_solver_type(const Type& type) { type_ = type; }

void Solver::set_concentrations(const VectorXd& concentrations) { state_.concentrations = concentrations; }

void Solver::set_reaction_powers(const MatrixXd& reaction_powers) { reaction_powers_ = reaction_powers; }

void Solver::set_stochiometric_matrix(const MatrixXd& stochiometric_matrix) {
    stochiometric_matrix_ = stochiometric_matrix;
}

void Solver::set_heat_capacities(const VectorXd& heat_capacities) { heat_capacities_ = heat_capacities; }

void Solver::set_enthalpies(const VectorXd& enthalpies) { enthalpies_ = enthalpies; }

void Solver::set_time_step(const TimeStep& time_step) { time_step_ = time_step; }

void Solver::set_rate_constants(const std::vector<RateConstant>& rate_constants) { rate_constants_ = rate_constants; }

void Solver::set_thermal(const Thermal& thermal) {
    thermal_ = thermal;
    state_.temperature = thermal_.get_temperature();
}

VectorXd Solver::calc_rate_constants() const {
    VectorXd rate_constants(rate_constants_.size());

    for (long i = 0; i < rate_constants.size(); i++) {
        rate_constants(i) = rate_constants_.at(i).get_rate_constant(state_.temperature);
    }

    return rate_constants;
}

void Solver::execute_master_equation() {
    const VectorXd rate_constants = calc_rate_constants();
    const VectorXd reaction_rates =
        algorithms::calc_reaction_rates(rate_constants, state_.concentrations, reaction_powers_);
    const VectorXd dX_dt = stochiometric_matrix_ * reaction_rates;

    state_.concentrations += dX_dt * time_step_.calc_dt(state_.concentrations, dX_dt);
    state_.temperature = thermal_.calc_temperature(state_.concentrations, heat_capacities_,
                                                   reaction_rates * time_step_.get_last_dt(), enthalpies_);
    state_.time += time_step_.get_last_dt();
}

void Solver::execute_fokker_planck() {
    const VectorXd rate_constants = calc_rate_constants();
    const VectorXd reaction_rates =
        algorithms::calc_reaction_rates(rate_constants, state_.concentrations, reaction_powers_);
    const VectorXd A = stochiometric_matrix_ * reaction_rates;
    const VectorXd D_pre = stochiometric_matrix_.transpose() * stochiometric_matrix_;
    const VectorXd D = D_pre * reaction_rates;

    for (uint i = 0; i < A.rows(); i++) {
        const double r = random_.NormalRandomNumber();
        state_.concentrations(i) = exp(A(i) * time_step_.calc_dt(state_.concentrations, A)) * state_.concentrations(i) -
                                   sqrt(D(0) * (1 - exp(A(i) * time_step_.get_last_dt()))) * r;
        state_.concentrations(i) = std::max(0.0, state_.concentrations(i));
    }

    state_.temperature = thermal_.calc_temperature(state_.concentrations, heat_capacities_,
                                                   reaction_rates * time_step_.get_last_dt(), enthalpies_);
    state_.time += time_step_.get_last_dt();
}

}  // namespace chem
