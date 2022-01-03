#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

#include "../exception/exception.h"
#include "../solver/rate_constant.h"
#include "../solver/thermal.h"
#include "../solver/timestep.h"
#include "../utilities/utility.h"

namespace chem {
namespace reader_algorithms {

struct Species {
    std::vector<std::string> names;
    std::vector<double> concentrations;

    size_t get_max_name_size() const {
        size_t max_name_l(0);

        for (const auto& name : names) {
            if (name.size() > max_name_l) {
                max_name_l = name.size();
            }
        }

        return max_name_l;
    }
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

std::string read_output_file_name(const std::string& file_name);
unsigned int read_number_of_iterations(const std::string& file_name);
Thermal read_temperature(const std::string& file_name);
TimeStep read_time_step(const std::string& file_name);
Species read_species(const std::string& file_name);
std::vector<Reaction> read_reactions(const std::string& file_name, const std::vector<std::string>& species_names);
void read_products(const std::vector<std::string>& line, Reaction& reaction,
                   const std::vector<std::string>& species_names);
void read_educts(const std::vector<std::string>& line, Reaction& reaction,
                 const std::vector<std::string>& species_names);
void read_enthalpy(const std::vector<std::string>& line, Reaction& reaction);
void read_rate_constant(const std::vector<std::string>& line, Reaction& reaction);

}  // namespace reader_algorithms
}  // namespace chem
