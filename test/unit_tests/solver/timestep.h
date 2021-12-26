#pragma once

#include <gtest/gtest.h>

#include "../../../src/solver/timestep.h"

namespace chem {

TEST(TimeStep, calc_dt) {
    TimeStep timestep;
    VectorXd concentrations(3);
    VectorXd dX_dt(3);

    concentrations(0) = 1.0;
    concentrations(1) = 2.0;
    concentrations(2) = 3.0;

    dX_dt(0) = 4.0;
    dX_dt(1) = 5.0;
    dX_dt(2) = 6.0;

    timestep.type = TimeStep::CONSTANT;
    timestep.value = 0.1;

    ASSERT_DOUBLE_EQ(0.1, timestep.calc_dt(concentrations, dX_dt));

    timestep.type = TimeStep::VARIABLE;

    ASSERT_DOUBLE_EQ(0.025, timestep.calc_dt(concentrations, dX_dt));
}

}  // namespace chem
