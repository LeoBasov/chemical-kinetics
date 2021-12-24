#pragma once

#include <gtest/gtest.h>

#include "../../src/algorithms.h"

namespace chem {

TEST(algorithms, arrhenius) {
    const double activation_energy = 3.0;
    const double pre_exp_factor = 5.0;
    const double temperature = 11.0;

    const double ref = pre_exp_factor * std::exp(-activation_energy / (temperature * constants::R));
    const double calced_val = algorithms::arrhenius(pre_exp_factor, activation_energy, temperature);

    ASSERT_DOUBLE_EQ(ref, calced_val);
}

}  // namespace chem
