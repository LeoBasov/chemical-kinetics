﻿#pragma once

#include <gtest/gtest.h>

#include "../../../src/solver/algorithms.h"

namespace chem {

TEST(algorithms, arrhenius) {
    const double activation_energy = 3.0;
    const double pre_exp_factor = 5.0;
    const double temperature = 11.0;
    const double temperature_exponent = 0.5;

    const double ref = std::pow(temperature, temperature_exponent) * pre_exp_factor *
                       std::exp(-activation_energy / (temperature * constants::R));
    const double calced_val =
        algorithms::arrhenius(temperature_exponent, pre_exp_factor, activation_energy, temperature);

    ASSERT_DOUBLE_EQ(ref, calced_val);
}

TEST(algorithms, calc_reaction_rates) {
    const long n_reactions(3), n_species(4);
    Eigen::VectorXd rate_constants(n_reactions);
    Eigen::VectorXd concentrations(n_species);
    Eigen::MatrixXd reaction_powers(n_reactions, n_species);

    rate_constants(0) = 3.0;
    rate_constants(1) = 5.0;
    rate_constants(2) = 7.0;

    concentrations(0) = 4.0;
    concentrations(1) = 5.0;
    concentrations(2) = 6.0;
    concentrations(3) = 7.0;

    reaction_powers(0, 0) = 1.0;
    reaction_powers(0, 1) = 0.0;
    reaction_powers(0, 2) = 0.0;
    reaction_powers(0, 3) = 0.0;

    reaction_powers(1, 0) = 0.0;
    reaction_powers(1, 1) = 1.0;
    reaction_powers(1, 2) = 0.0;
    reaction_powers(1, 3) = 0.0;

    reaction_powers(2, 0) = 0.0;
    reaction_powers(2, 1) = 0.0;
    reaction_powers(2, 2) = 1.0;
    reaction_powers(2, 3) = 1.0;

    const double ref_1(rate_constants(0) * std::pow(concentrations(0), reaction_powers(0, 0)) *
                       std::pow(concentrations(1), reaction_powers(0, 1)) *
                       std::pow(concentrations(2), reaction_powers(0, 2)) *
                       std::pow(concentrations(3), reaction_powers(0, 3)));
    const double ref_2(rate_constants(1) * std::pow(concentrations(0), reaction_powers(1, 0)) *
                       std::pow(concentrations(1), reaction_powers(1, 1)) *
                       std::pow(concentrations(2), reaction_powers(1, 2)) *
                       std::pow(concentrations(3), reaction_powers(1, 3)));
    const double ref_3(rate_constants(2) * std::pow(concentrations(0), reaction_powers(2, 0)) *
                       std::pow(concentrations(1), reaction_powers(2, 1)) *
                       std::pow(concentrations(2), reaction_powers(2, 2)) *
                       std::pow(concentrations(3), reaction_powers(2, 3)));

    const Eigen::VectorXd reaction_rates(
        algorithms::calc_reaction_rates(rate_constants, concentrations, reaction_powers));

    ASSERT_EQ(3, reaction_rates.size());

    ASSERT_DOUBLE_EQ(ref_1, reaction_rates(0));
    ASSERT_DOUBLE_EQ(ref_2, reaction_rates(1));
    ASSERT_DOUBLE_EQ(ref_3, reaction_rates(2));

    Eigen::VectorXd rate_constants_new(n_species);

    ASSERT_THROW(algorithms::calc_reaction_rates(rate_constants_new, concentrations, reaction_powers), Exception);
}

TEST(algorithms, calc_time_step) {
    const double factor(0.1);
    Eigen::VectorXd concentration(3);
    Eigen::VectorXd dX_dt(4);

    ASSERT_THROW(algorithms::calc_time_step(concentration, dX_dt, factor), Exception);

    dX_dt = Eigen::VectorXd(3);

    concentration(0) = 1.0;
    concentration(1) = 2.0;
    concentration(2) = 3.0;

    dX_dt(0) = 4.0;
    dX_dt(1) = 5.0;
    dX_dt(2) = 6.0;

    const double result(algorithms::calc_time_step(concentration, dX_dt, factor));

    ASSERT_DOUBLE_EQ(0.1 * 0.25, result);
}

TEST(algorithm, calc_total_heat_capcity) {
    Eigen::VectorXd heat_capacities(3);
    Eigen::VectorXd concentration(3);

    heat_capacities(0) = 1.0;
    heat_capacities(1) = 2.0;
    heat_capacities(2) = 3.0;

    concentration(0) = 4.0;
    concentration(1) = 5.0;
    concentration(2) = 6.0;

    const double result(algorithms::calc_total_heat_capcity(concentration, heat_capacities));
    const double ref = (4.0 + 10 + 18) / (4 + 5 + 6);

    ASSERT_DOUBLE_EQ(ref, result);
}

TEST(algorithm, calc_total_enthalpy_diff) {
    Eigen::VectorXd reaction_rate_dt(3);
    Eigen::VectorXd enthalpies(3);

    reaction_rate_dt(0) = 1.0;
    reaction_rate_dt(1) = 2.0;
    reaction_rate_dt(2) = 3.0;

    enthalpies(0) = 4.0;
    enthalpies(1) = 5.0;
    enthalpies(2) = 6.0;

    const double result = algorithms::calc_total_enthalpy_diff(reaction_rate_dt, enthalpies);
    const double ref = 4.0 + 10.0 + 18.0;

    ASSERT_DOUBLE_EQ(ref, result);
}

}  // namespace chem
