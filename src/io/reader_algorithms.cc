#include "reader_algorithms.h"

namespace chem {
namespace reader_algorithms {

unsigned int read_number_of_iterations(const std::string& file_name) {
    Thermal thermal;
    std::ifstream infile(file_name);
    std::string line;

    if (!infile.is_open()) {
        throw Exception("file does not exist", __PRETTY_FUNCTION__);
    }

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                         std::istream_iterator<std::string>());

        if (results.size() && results.front() == "n_iterations") {
            if (results.size() != 2) {
                throw Exception("wrong number of arguments", __PRETTY_FUNCTION__);
            }else{
                return std::stoi(results.at(1));
            }
        }
    }

    throw Exception("temperature not found", __PRETTY_FUNCTION__);
}

Thermal read_temperature(const std::string& file_name) {
    Thermal thermal;
    std::ifstream infile(file_name);
    std::string line;

    if (!infile.is_open()) {
        throw Exception("file does not exist", __PRETTY_FUNCTION__);
    }

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                         std::istream_iterator<std::string>());

        if (results.size() && results.front() == "temperature") {
            if (results.size() != 3) {
                throw Exception("wrong number of arguments", __PRETTY_FUNCTION__);
            }

            if (results.at(1) == "constant") {
                thermal.type = Thermal::CONSTANT;
            } else {
                throw Exception("wrong temperature step type [" + results.at(1) + "]", __PRETTY_FUNCTION__);
            }

            thermal.value = std::stod(results.at(2));

            return thermal;
        }
    }

    throw Exception("temperature not found", __PRETTY_FUNCTION__);
}

TimeStep read_time_step(const std::string& file_name) {
    TimeStep time_step;
    std::ifstream infile(file_name);
    std::string line;

    if (!infile.is_open()) {
        throw Exception("file does not exist", __PRETTY_FUNCTION__);
    }

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                         std::istream_iterator<std::string>());

        if (results.size() && results.front() == "time_step") {
            if (results.size() != 3) {
                throw Exception("wrong number of arguments", __PRETTY_FUNCTION__);
            }

            if (results.at(1) == "constant") {
                time_step.type = TimeStep::CONSTANT;
            } else if (results.at(1) == "variable") {
                time_step.type = TimeStep::VARIABLE;
            } else {
                throw Exception("wrong time step type [" + results.at(1) + "]", __PRETTY_FUNCTION__);
            }

            time_step.value = std::stod(results.at(2));

            return time_step;
        }
    }

    throw Exception("time_step not found", __PRETTY_FUNCTION__);
}

Species read_species(const std::string& file_name) {
    Species species;
    std::ifstream infile(file_name);
    std::string line;

    if (!infile.is_open()) {
        throw Exception("file does not exist", __PRETTY_FUNCTION__);
    }

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                         std::istream_iterator<std::string>());

        if (results.size() && results.front() == "add_species") {
            if (results.size() && (results.size() - 1) % 2) {
                throw Exception("wrong number of arguments", __PRETTY_FUNCTION__);
            }

            for (size_t i = 2; i < results.size(); i += 2) {
                if (std::find(species.names.begin(), species.names.end(), results.at(i - 1)) != species.names.end()) {
                    throw Exception("multiple definition of species", __PRETTY_FUNCTION__);
                } else {
                    species.names.push_back(results.at(i - 1));
                    species.concentrations.push_back(std::stod(results.at(i)));
                }
            }
        }
    }

    return species;
}

std::vector<Reaction> read_reactions(const std::string& file_name, const std::vector<std::string>& species_names) {
    std::vector<Reaction> reactions;
    std::ifstream infile(file_name);
    std::string line;

    if (!infile.is_open()) {
        throw Exception("file does not exist", __PRETTY_FUNCTION__);
    }

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                         std::istream_iterator<std::string>());

        if (results.size() && results.front() == "add_reaction") {
            Reaction reaction(species_names.size());

            read_products(results, reaction, species_names);
            read_educts(results, reaction, species_names);
            read_rate_constant(results, reaction);
            read_enthalpy(results, reaction);

            reactions.push_back(reaction);
        }
    }

    if (!reactions.size()) {
        throw Exception("no reactions added", __PRETTY_FUNCTION__);
    }

    return reactions;
}

void read_products(const std::vector<std::string>& line, Reaction& reaction,
                   const std::vector<std::string>& species_names) {
    for (size_t i = 0; i < line.size(); i++) {
        if (line.at(i) == "products") {
            const unsigned int n_products(std::stoi(line.at(i + 1)));

            for (size_t p = 2; p < n_products + 2; p++) {
                std::vector<std::string> product(utility::split_string(line.at(i + p), "*"));

                if (product.size() != 2) {
                    throw Exception("wrong product format", __PRETTY_FUNCTION__);
                }

                auto iter = std::find(species_names.begin(), species_names.end(), product.at(1));

                if (iter == species_names.end()) {
                    throw Exception("species not defined", __PRETTY_FUNCTION__);
                } else {
                    reaction.product_stoichiometric_coefficients.at(iter - species_names.begin()) =
                        std::stod(product.at(0));
                }
            }
        }
    }
}

void read_educts(const std::vector<std::string>& line, Reaction& reaction,
                 const std::vector<std::string>& species_names) {
    for (size_t i = 0; i < line.size(); i++) {
        if (line.at(i) == "educts") {
            const unsigned int n_educts(std::stoi(line.at(i + 1)));

            for (size_t p = 2; p < n_educts + 2; p++) {
                std::vector<std::string> educt(utility::split_string(line.at(i + p), "*"));
                std::vector<std::string> power(utility::split_string(educt.at(1), "^"));

                if (educt.size() != 2 || power.size() != 2) {
                    throw Exception("wrong educt format", __PRETTY_FUNCTION__);
                }

                auto iter = std::find(species_names.begin(), species_names.end(), power.at(0));

                if (iter == species_names.end()) {
                    throw Exception("species not defined", __PRETTY_FUNCTION__);
                } else {
                    reaction.educt_stoichiometric_coefficients.at(iter - species_names.begin()) =
                        std::stod(educt.at(0));
                    reaction.reaction_powers.at(iter - species_names.begin()) = std::stod(power.at(1));
                }
            }
        }
    }
}

void read_enthalpy(const std::vector<std::string>& line, Reaction& reaction) {
    for (size_t i = 0; i < line.size(); i++) {
        if (line.at(i) == "reaction_enthalpy") {
            reaction.reaction_enthalpy = std::stod(line.at(i + 1));
        }
    }
}

void read_rate_constant(const std::vector<std::string>& line, Reaction& reaction) {
    for (size_t i = 0; i < line.size(); i++) {
        if (line.at(i) == "rate_constant") {
            if (line.at(i + 1) == "constant") {
                reaction.rate_constant.type = RateConstant::CONSTANT;
                reaction.rate_constant.value = std::stod(line.at(i + 2));
            } else if (line.at(i + 1) == "variable") {
                reaction.rate_constant.type = RateConstant::VARIABLE;
                reaction.rate_constant.pre_exp_factor = std::stod(line.at(i + 2));
                reaction.rate_constant.activation_energy = std::stod(line.at(i + 3));
            } else {
                throw Exception("undefined rate constant type", __PRETTY_FUNCTION__);
            }
        }
    }
}

}  // namespace reader_algorithms
}  // namespace chem
