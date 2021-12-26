#pragma once

#include <gtest/gtest.h>

#include "../../../src/io/reader.h"

namespace chem {

TEST(Reader, get_time_step) {
    const std::string wrong_file_name("wrong_name.in");
    const std::string file_name_const_dt("./test/unit_tests/test_data/reader/reader_dt_cont.in");
    const std::string file_name_var_dt("./test/unit_tests/test_data/reader/reader_dt_var.in");
    Reader reader;

    ASSERT_THROW(reader.read_file(wrong_file_name), Exception);

    reader.read_file(file_name_const_dt);

    ASSERT_EQ(TimeStep::CONSTANT, reader.get_time_step().type);

    reader.read_file(file_name_var_dt);

    ASSERT_EQ(TimeStep::VARIABLE, reader.get_time_step().type);
    ASSERT_DOUBLE_EQ(1e-7, reader.get_time_step().value);
}

TEST(Reader, get_thermal) {
    const std::string file_name("./test/unit_tests/test_data/reader/reader_dt_var.in");
    Reader reader;
    Thermal thermal;

    reader.read_file(file_name);

    thermal = reader.get_thermal();

    ASSERT_EQ(Thermal::CONSTANT, thermal.type);
    ASSERT_DOUBLE_EQ(2000, thermal.value);
}

TEST(Reader, get_species_name) {
    const std::string file_name("./test/unit_tests/test_data/reader/reader_dt_var.in");
    Reader reader;
    std::vector<std::string> species_names;

    reader.read_file(file_name);

    species_names = reader.get_species_name();

    ASSERT_EQ(4, species_names.size());

    ASSERT_EQ("H2O", species_names.at(0));
    ASSERT_EQ("O2", species_names.at(1));
    ASSERT_EQ("H2", species_names.at(2));
    ASSERT_EQ("CO2", species_names.at(3));
}

TEST(Reader, get_concentrations) {
    const std::string file_name("./test/unit_tests/test_data/reader/reader_dt_var.in");
    Reader reader;
    VectorXd concentrations;

    reader.read_file(file_name);

    concentrations = reader.get_concentrations();

    ASSERT_EQ(4, concentrations.size());

    ASSERT_DOUBLE_EQ(0.5, concentrations(0));
    ASSERT_DOUBLE_EQ(1.3, concentrations(1));
    ASSERT_DOUBLE_EQ(7.3, concentrations(2));
    ASSERT_DOUBLE_EQ(0.3, concentrations(3));
}

}  // namespace chem
