#pragma once

#include <gtest/gtest.h>

#include "../../../src/solver/rate_constant.h"

namespace chem {

TEST(RateConstant, get_rate_constant) {
    RateConstant rate_constant;
    const double temperature(2000);

    rate_constant.type = RateConstant::CONSTANT;
    rate_constant.value = 0.1;
    rate_constant.pre_exp_factor = 0.25;
    rate_constant.activation_energy = 3.0;

    ASSERT_DOUBLE_EQ(0.1, rate_constant.get_rate_constant(temperature));

    rate_constant.type = RateConstant::VARIABLE;

    ASSERT_DOUBLE_EQ(0.24995490193501915, rate_constant.get_rate_constant(temperature));
}

}  // namespace chem
