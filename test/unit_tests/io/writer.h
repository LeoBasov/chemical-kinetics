#pragma once

#include <gtest/gtest.h>

#include "../../../src/io/io_algorithms.h"
#include "../../../src/io/writer.h"

namespace chem {

TEST(Writer, open) {
    Writer writer;
    std::vector<std::string> species_names;
    const std::string wrong_file_name("./blubb/test.csv");
    const std::string file_name("test.csv");

    species_names.push_back("H2O");
    species_names.push_back("O2");
    species_names.push_back("H2");

    ASSERT_THROW(writer.open(wrong_file_name, species_names), Exception);
    writer.open(file_name, species_names);

    std::ifstream infile(file_name);
    std::string line;

    ASSERT_TRUE(infile.is_open());

    std::getline(infile, line);
    std::vector<std::string> result(io_algorithms::split_string(line, ","));

    ASSERT_EQ(5, result.size());

    ASSERT_EQ("#t", result.at(0));
    ASSERT_EQ("#T", result.at(1));
    ASSERT_EQ("#H2O", result.at(2));
    ASSERT_EQ("#O2", result.at(3));
    ASSERT_EQ("#H2", result.at(4));
}

TEST(Writer, write_state) {
    Writer writer;
    std::vector<std::string> species_names;
    Solver::State state;
    const std::string file_name("test.csv");

    species_names.push_back("H2O");
    species_names.push_back("O2");
    species_names.push_back("H2");

    state.temperature = 11.1;
    state.time = 13.13;

    state.concentrations = VectorXd(3);

    state.concentrations(0) = 3.3;
    state.concentrations(1) = 5.5;
    state.concentrations(2) = 7.7;

    writer.open(file_name, species_names);
    writer.write_state(state);

    std::ifstream infile(file_name);
    std::string line;

    std::getline(infile, line);
    std::getline(infile, line);
    std::vector<std::string> result(io_algorithms::split_string(line, ","));

    ASSERT_EQ(5, result.size());

    ASSERT_EQ("13.13", result.at(0));
    ASSERT_EQ("11.1", result.at(1));
    ASSERT_EQ("3.3", result.at(2));
    ASSERT_EQ("5.5", result.at(3));
    ASSERT_EQ("7.7", result.at(4));
}

}  // namespace chem
