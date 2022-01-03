#pragma once

#include <fstream>
#include <vector>

#include "../exception/exception.h"
#include "../solver/solver.h"

namespace chem {

class Writer {
   public:
    Writer();
    ~Writer() = default;

    void open(const std::string &file_name, const std::vector<std::string> &species_names);
    void write_state(const Solver::State &state);

   private:
    std::ofstream stream_;
    const long precision_ = 3;

    void write_header(const std::vector<std::string> &species_names);
};

}  // namespace chem
