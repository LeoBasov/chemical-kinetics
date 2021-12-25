#pragma once

#include <iostream>
#include <vector>

#include "../exception/exception.h"

namespace chem {
namespace io_algorithms {

struct Species {
    std::vector<std::string> names;
    std::vector<double> concentrations;
};

Species add_species(const std::string& file_name);

}  // namespace io_algorithms
}  // namespace chem
