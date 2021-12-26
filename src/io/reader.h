#pragma once

#include "../solver/solver.h"
#include "reader_algorithms.h"

namespace chem {
using namespace reader_algorithms;

class Reader {
   public:
    Reader();
    ~Reader() = default;

    Solver read_file(const std::string& file_name) const;
};

}  // namespace chem
