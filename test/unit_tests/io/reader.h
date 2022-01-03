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

    ASSERT_EQ(Thermal::CONSTANT, thermal.get_type());
    ASSERT_DOUBLE_EQ(2000, thermal.get_temperature());
}

TEST(Reader, get_species_name) {
    const std::string file_name("./test/unit_tests/test_data/reader/reader_dt_var.in");
    Reader reader;
    std::vector<std::string> species_names;

    reader.read_file(file_name);

    species_names = reader.get_species_names();

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

TEST(Reader, get_rate_constants) {
    const std::string file_name("./test/unit_tests/test_data/reader/reader_dt_var.in");
    Reader reader;
    std::vector<RateConstant> rate_constants;

    reader.read_file(file_name);

    rate_constants = reader.get_rate_constants();

    ASSERT_EQ(2, rate_constants.size());

    ASSERT_EQ(RateConstant::CONSTANT, rate_constants.at(0).type);
    ASSERT_DOUBLE_EQ(3.7, rate_constants.at(0).value);

    ASSERT_EQ(RateConstant::VARIABLE, rate_constants.at(1).type);
    ASSERT_DOUBLE_EQ(11.1, rate_constants.at(1).pre_exp_factor);
    ASSERT_DOUBLE_EQ(15.7, rate_constants.at(1).activation_energy);
}

TEST(Reader, get_stochiometric_matrix) {
    const std::string file_name("./test/unit_tests/test_data/reader/reader_dt_var.in");
    Reader reader;
    MatrixXd stochiometric_matrix;

    reader.read_file(file_name);

    stochiometric_matrix = reader.get_stochiometric_matrix();

    ASSERT_EQ(8, stochiometric_matrix.size());
    ASSERT_EQ(4, stochiometric_matrix.rows());
    ASSERT_EQ(2, stochiometric_matrix.cols());

    ASSERT_DOUBLE_EQ(-1.0, stochiometric_matrix(0, 0));
    ASSERT_DOUBLE_EQ(1.0, stochiometric_matrix(1, 0));
    ASSERT_DOUBLE_EQ(0.5, stochiometric_matrix(2, 0));
    ASSERT_DOUBLE_EQ(0.0, stochiometric_matrix(3, 0));

    ASSERT_DOUBLE_EQ(1.0, stochiometric_matrix(0, 1));
    ASSERT_DOUBLE_EQ(-1.0, stochiometric_matrix(1, 1));
    ASSERT_DOUBLE_EQ(-0.5, stochiometric_matrix(2, 1));
    ASSERT_DOUBLE_EQ(0.0, stochiometric_matrix(3, 1));
}

TEST(Reader, get_reaction_powers) {
    const std::string file_name("./test/unit_tests/test_data/reader/reader_dt_var.in");
    Reader reader;
    MatrixXd reaction_powers;

    reader.read_file(file_name);

    reaction_powers = reader.get_reaction_powers();

    ASSERT_EQ(8, reaction_powers.size());
    ASSERT_EQ(2, reaction_powers.rows());
    ASSERT_EQ(4, reaction_powers.cols());

    ASSERT_DOUBLE_EQ(1.0, reaction_powers(0, 0));
    ASSERT_DOUBLE_EQ(0.0, reaction_powers(0, 1));
    ASSERT_DOUBLE_EQ(0.0, reaction_powers(0, 2));
    ASSERT_DOUBLE_EQ(0.0, reaction_powers(0, 3));

    ASSERT_DOUBLE_EQ(0.0, reaction_powers(1, 0));
    ASSERT_DOUBLE_EQ(3.0, reaction_powers(1, 1));
    ASSERT_DOUBLE_EQ(2.0, reaction_powers(1, 2));
    ASSERT_DOUBLE_EQ(0.0, reaction_powers(1, 3));
}

}  // namespace chem
