#pragma once

#include <gtest/gtest.h>

#include "../../src/dummy.h"

namespace hamt {
namespace gmsh {

TEST(dummy, foo) { ASSERT_EQ(0, foo()); }

TEST(dummy, ba) { ASSERT_EQ(12.1, ba()); }

}  // namespace gmsh
}  // namespace hamt
