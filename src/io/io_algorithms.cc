#include "io_algorithms.h"

namespace chem {
namespace io_algorithms {

Species add_species(const std::string &file_name) {
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

std::vector<Reaction> add_reactions(const std::string& file_name, const std::vector<std::string>& species_names) {
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

            add_products(results, reaction, species_names);
            add_educts(results, reaction, species_names);
            // TODO: add read reate constant
            add_enthalpy(results, reaction);

            reactions.push_back(reaction);
        }
    }

    if (!reactions.size()) {
        throw Exception("no reactions added", __PRETTY_FUNCTION__);
    }

    return reactions;
}

void add_products(const std::vector<std::string>& line, Reaction& reaction,
                  const std::vector<std::string>& species_names) {
    for (size_t i = 0; i < line.size(); i++) {
        if (line.at(i) == "products") {
            const unsigned int n_products(std::stoi(line.at(i + 1)));

            for (size_t p = 2; p < n_products + 2; p++) {
                std::vector<std::string> product(split_string(line.at(i + p), "*"));

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

void add_educts(const std::vector<std::string>& line, Reaction& reaction,
                const std::vector<std::string>& species_names) {
    for (size_t i = 0; i < line.size(); i++) {
        if (line.at(i) == "educts") {
            const unsigned int n_educts(std::stoi(line.at(i + 1)));

            for (size_t p = 2; p < n_educts + 2; p++) {
                std::vector<std::string> educt(split_string(line.at(i + p), "*"));
                std::vector<std::string> power(split_string(educt.at(1), "^"));

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

void add_enthalpy(const std::vector<std::string>& line, Reaction& reaction) {
    for (size_t i = 0; i < line.size(); i++) {
        if (line.at(i) == "reaction_enthalpy") {
            reaction.reaction_enthalpy = std::stod(line.at(i + 1));
        }
    }
}

std::vector<std::string> split_string(std::string str, const std::string& delimiter) {
    std::vector<std::string> split;

    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        split.push_back(token);
        str.erase(0, pos + delimiter.length());
    }

    split.push_back(str);

    return split;
}

}  // namespace io_algorithms
}  // namespace chem
