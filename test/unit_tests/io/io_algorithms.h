#pragma once

#include <gtest/gtest.h>

#include "../../../src/io/io_algorithms.h"

namespace chem {
using namespace io_algorithms;

TEST(io_algorithms, add_species_wrong) {
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

TEST(io_algorithms, add_species) {
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

TEST(io_algorithms, add_reaction_wrong) {}

TEST(io_algorithms, add_reaction) {}

}  // namespace chem
