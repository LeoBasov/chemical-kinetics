#pragma once

#include <gtest/gtest.h>

#include "../../../src/io/reader.h"

namespace chem {

TEST(Reader, read_file) {
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

}  // namespace chem
