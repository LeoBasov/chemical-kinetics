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

TEST(Writer, write_state) {}

}  // namespace chem
