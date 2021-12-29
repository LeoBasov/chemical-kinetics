#pragma once

#include <iostream>

#include "reader.h"

namespace chem {
namespace sc_print_algorithms {

void print_species(const Species& species);
std::string tab(const size_t& n);

}  // namespace sc_print_algorithms
}  // namespace chem
