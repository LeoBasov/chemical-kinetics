#include <gtest/gtest.h>

#include "io/reader.h"
#include "io/reader_algorithms.h"
#include "io/writer.h"
#include "solver/algorihtms.h"
#include "solver/rate_constant.h"
#include "solver/timestep.h"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
