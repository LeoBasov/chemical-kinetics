#pragma once

#include <gtest/gtest.h>

#include "../../../src/io/reader_algorithms.h"

namespace chem {
using namespace reader_algorithms;

TEST(reader_algorithms, add_species_wrong) {
    const std::string file_name_wrong_1("./test/unit_tests/test_data/add_species/add_species_wrong_1.in");
    const std::string file_name_wrong_2("./test/unit_tests/test_data/add_species/add_species_wrong_2.in");
    const std::string file_name_wrong_3("./test/unit_tests/test_data/add_species/add_species_wrong_3.in");
    const std::string file_name_wrong_4("./test/unit_tests/test_data/add_species/does_not_exist.in");
    const std::string file_name_correct("./test/unit_tests/test_data/add_species/add_species.in");

    ASSERT_THROW(add_species(file_name_wrong_1), Exception);
    ASSERT_THROW(add_species(file_name_wrong_2), Exception);
    ASSERT_THROW(add_species(file_name_wrong_3), Exception);
    ASSERT_THROW(add_species(file_name_wrong_4), Exception);
    add_species(file_name_correct);
}

TEST(reader_algorithms, add_species) {
    const std::string file_name("./test/unit_tests/test_data/add_species/add_species.in");

    Species species = add_species(file_name);

    ASSERT_EQ(species.concentrations.size(), species.names.size());
    ASSERT_EQ(4, species.names.size());

    ASSERT_EQ("H2O", species.names.at(0));
    ASSERT_EQ("O2", species.names.at(1));
    ASSERT_EQ("H2", species.names.at(2));
    ASSERT_EQ("CO2", species.names.at(3));

    ASSERT_DOUBLE_EQ(0.5, species.concentrations.at(0));
    ASSERT_DOUBLE_EQ(1.3, species.concentrations.at(1));
    ASSERT_DOUBLE_EQ(7.3, species.concentrations.at(2));
    ASSERT_DOUBLE_EQ(0.3, species.concentrations.at(3));
}

TEST(reader_algorithms, add_reaction_wrong) {
    const std::string file_name_wrong_1("./test/unit_tests/test_data/add_reaction/add_reactions_wrong_1.in");
    const std::string file_name_wrong_2("./test/unit_tests/test_data/add_reaction/add_reactions_wrong_2.in");
    const std::string file_name_wrong_3("./test/unit_tests/test_data/add_reaction/does_not_exist.in");
    const std::string file_name_correct("./test/unit_tests/test_data/add_reaction/add_reactions.in");
    const std::string species_file_name("./test/unit_tests/test_data/add_species/add_species.in");

    Species species = add_species(species_file_name);

    ASSERT_THROW(add_reactions(file_name_wrong_1, species.names), Exception);
    ASSERT_THROW(add_reactions(file_name_wrong_2, species.names), Exception);
    ASSERT_THROW(add_reactions(file_name_wrong_3, species.names), Exception);
    add_reactions(file_name_correct, species.names);
}

TEST(reader_algorithms, add_reaction) {
    const std::string file_name("./test/unit_tests/test_data/add_reaction/add_reactions.in");
    const std::string species_file_name("./test/unit_tests/test_data/add_species/add_species.in");

    Species species = add_species(species_file_name);
    std::vector<Reaction> reactions = add_reactions(file_name, species.names);

    ASSERT_EQ(2, reactions.size());

    // reaction 1
    ASSERT_DOUBLE_EQ(0.0, reactions.at(0).product_stoichiometric_coefficients.at(0));
    ASSERT_DOUBLE_EQ(1.0, reactions.at(0).product_stoichiometric_coefficients.at(1));
    ASSERT_DOUBLE_EQ(0.5, reactions.at(0).product_stoichiometric_coefficients.at(2));
    ASSERT_DOUBLE_EQ(0.0, reactions.at(0).product_stoichiometric_coefficients.at(3));

    ASSERT_DOUBLE_EQ(1.0, reactions.at(0).educt_stoichiometric_coefficients.at(0));
    ASSERT_DOUBLE_EQ(0.0, reactions.at(0).educt_stoichiometric_coefficients.at(1));
    ASSERT_DOUBLE_EQ(0.0, reactions.at(0).educt_stoichiometric_coefficients.at(2));
    ASSERT_DOUBLE_EQ(0.0, reactions.at(0).educt_stoichiometric_coefficients.at(3));

    ASSERT_DOUBLE_EQ(1.0, reactions.at(0).reaction_powers.at(0));
    ASSERT_DOUBLE_EQ(0.0, reactions.at(0).reaction_powers.at(1));
    ASSERT_DOUBLE_EQ(0.0, reactions.at(0).reaction_powers.at(2));
    ASSERT_DOUBLE_EQ(0.0, reactions.at(0).reaction_powers.at(3));

    ASSERT_DOUBLE_EQ(7.1, reactions.at(0).reaction_enthalpy);

    ASSERT_EQ(reader_algorithms::RateConstant::CONSTANT, reactions.at(0).rate_constant.type);
    ASSERT_DOUBLE_EQ(3.7, reactions.at(0).rate_constant.value);

    // reaction 2
    ASSERT_DOUBLE_EQ(1.0, reactions.at(1).product_stoichiometric_coefficients.at(0));
    ASSERT_DOUBLE_EQ(0.0, reactions.at(1).product_stoichiometric_coefficients.at(1));
    ASSERT_DOUBLE_EQ(0.0, reactions.at(1).product_stoichiometric_coefficients.at(2));
    ASSERT_DOUBLE_EQ(0.0, reactions.at(1).product_stoichiometric_coefficients.at(3));

    ASSERT_DOUBLE_EQ(0.0, reactions.at(1).educt_stoichiometric_coefficients.at(0));
    ASSERT_DOUBLE_EQ(1.0, reactions.at(1).educt_stoichiometric_coefficients.at(1));
    ASSERT_DOUBLE_EQ(0.5, reactions.at(1).educt_stoichiometric_coefficients.at(2));
    ASSERT_DOUBLE_EQ(0.0, reactions.at(1).educt_stoichiometric_coefficients.at(3));

    ASSERT_DOUBLE_EQ(0.0, reactions.at(1).reaction_powers.at(0));
    ASSERT_DOUBLE_EQ(3.0, reactions.at(1).reaction_powers.at(1));
    ASSERT_DOUBLE_EQ(2.0, reactions.at(1).reaction_powers.at(2));
    ASSERT_DOUBLE_EQ(0.0, reactions.at(1).reaction_powers.at(3));

    ASSERT_DOUBLE_EQ(1.7, reactions.at(1).reaction_enthalpy);

    ASSERT_EQ(reader_algorithms::RateConstant::VARIABLE, reactions.at(1).rate_constant.type);
    ASSERT_DOUBLE_EQ(11.1, reactions.at(1).rate_constant.pre_exp_factor);
    ASSERT_DOUBLE_EQ(15.7, reactions.at(1).rate_constant.activation_energy);
}

}  // namespace chem
