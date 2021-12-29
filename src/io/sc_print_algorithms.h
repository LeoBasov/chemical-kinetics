#pragma once

#include <iostream>

#include "reader.h"

namespace chem {
namespace sc_print_algorithms {

const size_t tab_size(4);

void print_species(const Species& species);
void print_reactions(const std::vector<Reaction>& reactions, const Species& species);
void print_reaction(const Reaction& reaction, const Species& species);

std::string tab(const size_t& n);

}  // namespace sc_print_algorithms
}  // namespace chem
