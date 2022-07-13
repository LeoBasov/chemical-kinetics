#include "reader.h"

namespace chem {

Reader::Reader() {}

void Reader::read_file(const std::string& file_name) {
    solver_type_ = read_solver_type(file_name);
    species_ = read_species(file_name);
    reactions_ = read_reactions(file_name, species_.names);
    time_step_ = read_time_step(file_name);
    thermal_ = read_temperature(file_name);
    number_iterations_ = read_number_of_iterations(file_name);
    output_file_ = read_output_file_name(file_name);
}

Solver::Type Reader::get_solver_type() const { return solver_type_; }

VectorXd Reader::get_concentrations() const {
    VectorXd concentrations(species_.concentrations.size());

    for (size_t i = 0; i < species_.concentrations.size(); i++) {
        concentrations(i) = species_.concentrations.at(i);
    }

    return concentrations;
}

MatrixXd Reader::get_reaction_powers() const {
    MatrixXd reaction_powers(reactions_.size(), species_.names.size());

    for (long j = 0; j < reaction_powers.rows(); j++) {
        for (long i = 0; i < reaction_powers.cols(); i++) {
            reaction_powers(j, i) = reactions_.at(j).reaction_powers.at(i);
        }
    }

    return reaction_powers;
}

MatrixXd Reader::get_stochiometric_matrix() const {
    MatrixXd stochiometric_matrix(species_.names.size(), reactions_.size());

    for (long i = 0; i < stochiometric_matrix.rows(); i++) {
        for (long j = 0; j < stochiometric_matrix.cols(); j++) {
            stochiometric_matrix(i, j) = reactions_.at(j).product_stoichiometric_coefficients.at(i) -
                                         reactions_.at(j).educt_stoichiometric_coefficients.at(i);
        }
    }

    return stochiometric_matrix;
}

VectorXd Reader::get_heat_capacities() const {
    VectorXd heat_capacities(species_.heat_capacities.size());

    for (long i = 0; i < heat_capacities.size(); i++) {
        heat_capacities(i) = species_.heat_capacities.at(i);
    }

    return heat_capacities;
}

VectorXd Reader::get_enthalpies() const {
    VectorXd enthalpies(reactions_.size());

    for (long i = 0; i < enthalpies.size(); i++) {
        enthalpies(i) = reactions_.at(i).reaction_enthalpy;
    }

    return enthalpies;
}

std::vector<RateConstant> Reader::get_rate_constants() const {
    std::vector<RateConstant> rate_constants(reactions_.size());

    for (size_t i = 0; i < reactions_.size(); i++) {
        rate_constants.at(i) = reactions_.at(i).rate_constant;
    }

    return rate_constants;
}

std::vector<std::string> Reader::get_species_names() const { return species_.names; }

TimeStep Reader::get_time_step() const { return time_step_; }

Thermal Reader::get_thermal() const { return thermal_; }

Species Reader::get_species() const { return species_; }

std::vector<Reaction> Reader::get_reactions() const { return reactions_; }

unsigned int Reader::get_number_iterations() const { return number_iterations_; }

std::string Reader::get_output_file() const { return output_file_; }

}  // namespace chem
