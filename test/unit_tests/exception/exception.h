#pragma once

#include <gtest/gtest.h>

#include "../../../src/exception/exception.h"

namespace chem {

TEST(Exception, what) {
    Exception exception("what");

    ASSERT_EQ("what", std::string(exception.what()));
}

TEST(Exception, where) {
    Exception exception("what", "where");

    ASSERT_EQ("where", exception.where());
}

}  // namespace chem
