#pragma once

#include <iostream>

#include "reader.h"

namespace chem {
namespace sc_print_algorithms {

const size_t tab_size(4);

void print_species(const Species& species);
void print_reactions(const std::vector<Reaction>& reactions, const Species& species);
void print_reaction(const Reaction& reaction, const Species& species, const size_t& max_educt_size,
                    const size_t& max_product_size);
void print_state(const std::vector<std::string>& species_names, const Solver::State& state);

size_t get_max_name_size(const Species& species);
size_t get_max_educt_size(const std::vector<Reaction>& reactions);
size_t get_max_product_size(const std::vector<Reaction>& reactions);

std::string tab(const size_t& n);
std::string tab();

}  // namespace sc_print_algorithms
}  // namespace chem
