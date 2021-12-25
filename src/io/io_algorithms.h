#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

#include "../exception/exception.h"

namespace chem {
namespace io_algorithms {

struct Species {
    std::vector<std::string> names;
    std::vector<double> concentrations;
};

struct RateConstant {
    enum Type { CONSTANT, VARIABLE };

    Type type = CONSTANT;
    double value = 0.0;
    double pre_exp_factor = 0.0;
    double activation_energy = 0.0;
};

struct Reaction {
    Reaction() {}
    Reaction(const size_t& n_species) { set_species(n_species); }

    std::vector<double> educt_stoichiometric_coefficients;
    std::vector<double> product_stoichiometric_coefficients;
    std::vector<double> reaction_powers;
    double reaction_enthalpy = 0.0;
    RateConstant rate_constant;

    void set_species(const size_t& n_species) {
        educt_stoichiometric_coefficients = std::vector<double>(n_species, 0.0);
        product_stoichiometric_coefficients = std::vector<double>(n_species, 0.0);
        reaction_powers = std::vector<double>(n_species, 0.0);
    }
};

Species add_species(const std::string& file_name);
std::vector<Reaction> add_reactions(const std::string& file_name, const std::vector<std::string>& species_names);
void add_products(const std::vector<std::string>& line, Reaction& reaction,
                  const std::vector<std::string>& species_names);
void add_educts(const std::vector<std::string>& line, Reaction& reaction,
                const std::vector<std::string>& species_names);
std::vector<std::string> split_string(std::string str, const std::string& delimiter);

}  // namespace io_algorithms
}  // namespace chem
