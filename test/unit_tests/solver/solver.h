#pragma once

#include <gtest/gtest.h>

#include "../../../src/solver/solver.h"

namespace chem {

TEST(Solver, all) {
    Solver solver;
    VectorXd concentrations(2);
    MatrixXd reaction_powers(1, 2);
    MatrixXd stochiometric_matrix(2, 1);
    TimeStep time_step;
    std::vector<RateConstant> rate_constants(1);
    Thermal thermal;
    Solver::State state;

    // TODO: set stuff
    concentrations(0) = 1.0;
    concentrations(1) = 0.0;

    reaction_powers(0, 0) = 1.0;
    reaction_powers(0, 1) = 0.0;

    stochiometric_matrix(0, 0) = -1.0;
    stochiometric_matrix(1, 0) = 1.0;

    time_step.type = TimeStep::CONSTANT;
    time_step.value = 0.1;

    rate_constants.at(0).type = RateConstant::CONSTANT;
    rate_constants.at(0).value = 1;

    thermal.type = Thermal::CONSTANT;
    thermal.temperature = 2000;

    solver.set_concentrations(concentrations);
    solver.set_reaction_powers(reaction_powers);
    solver.set_stochiometric_matrix(stochiometric_matrix);
    solver.set_time_step(time_step);
    solver.set_rate_constants(rate_constants);
    solver.set_thermal(thermal);

    solver.execute();

    state = solver.get_state();

    ASSERT_DOUBLE_EQ(0.9, state.concentrations(0));
    ASSERT_DOUBLE_EQ(0.1, state.concentrations(1));

    ASSERT_DOUBLE_EQ(0.1, state.time);

    ASSERT_DOUBLE_EQ(2000, state.temperature);
}

}  // namespace chem
