#pragma once

#include <fstream>
#include <vector>

#include "../exception/exception.h"

namespace chem {

class Writer {
   public:
    Writer();
    ~Writer() = default;

    void open(const std::string &file_name, const std::vector<std::string> &species_names);
    void write_state();

   private:
    std::ofstream stream_;

    void write_header(const std::vector<std::string> &species_names);
};

}  // namespace chem
