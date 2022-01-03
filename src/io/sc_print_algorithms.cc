#include "sc_print_algorithms.h"

namespace chem {
namespace sc_print_algorithms {

void print_species(const Species& species) {
    const size_t n_name(7);
    const size_t n_concentration(13);

    std::cout << tab(tab_size) << "╔═════════╤═══════════════╗" << std::endl;
    std::cout << tab(tab_size) << "║ species │ concentration ║" << std::endl;
    std::cout << tab(tab_size) << "╠═════════╪═══════════════╣" << std::endl;

    for (size_t i = 0; i < species.names.size(); i++) {
        const size_t n_name_loc(n_name - species.names.at(i).size());
        const size_t n_concentration_loc(n_concentration - std::to_string(species.concentrations.at(i)).size());

        if (i) {
            std::cout << tab(tab_size) << "╟─────────┼───────────────╢" << std::endl;
        }

        std::cout << tab(tab_size) << "║ " << tab(n_name_loc) << species.names.at(i) << " │ "
                  << tab(n_concentration_loc) << std::to_string(species.concentrations.at(i)) << " ║" << std::endl;
    }

    std::cout << tab(tab_size) << "╚═════════╧═══════════════╝" << std::endl << std::endl;
}

void print_reactions(const std::vector<Reaction>& reactions, const Species& species) {
    const size_t max_educt_size(get_max_educt_size(reactions));
    const size_t max_prduct_size(get_max_product_size(reactions));

    for (size_t i = 0; i < reactions.size(); i++) {
        print_reaction(reactions.at(i), species, max_educt_size, max_prduct_size);
    }

    std::cout << std::endl;
}

void print_reaction(const Reaction& reaction, const Species& species, const size_t& max_educt_size,
                    const size_t& max_product_size) {
    bool first(true);
    size_t max_name_l(get_max_name_size(species));
    size_t length(0);

    std::cout << tab(tab_size) << "reaction: ";
    std::cout.precision(1);

    for (size_t i = 0; i < reaction.educt_stoichiometric_coefficients.size(); i++) {
        if (!reaction.educt_stoichiometric_coefficients.at(i)) {
            continue;
        }

        if (i && !first) {
            std::cout << " + ";
        }

        std::cout << std::scientific << reaction.educt_stoichiometric_coefficients.at(i) << "⋅" << species.names.at(i)
                  << tab(max_name_l - species.names.at(i).size());
        first = false;
        length++;
    }

    std::cout << tab((11 + max_name_l) * (max_educt_size - length));

    length = 0;
    first = true;
    std::cout << " →  ";

    for (size_t i = 0; i < reaction.product_stoichiometric_coefficients.size(); i++) {
        if (!reaction.product_stoichiometric_coefficients.at(i)) {
            continue;
        }

        if (i && !first) {
            std::cout << " + ";
        }

        std::cout << reaction.product_stoichiometric_coefficients.at(i) << "⋅" << species.names.at(i)
                  << tab(max_name_l - species.names.at(i).size());
        first = false;
        length++;
    }

    std::cout << tab((11 + max_name_l) * (max_product_size - length));

    if (reaction.rate_constant.type == RateConstant::CONSTANT) {
        std::cout << " : k = CONST";
    } else {
        std::cout << " : k = VARIABLE";
    }

    std::cout << std::endl;
}

size_t get_max_name_size(const Species& species) {
    size_t max_name_l(0);

    for (const auto& name : species.names) {
        if (name.size() > max_name_l) {
            max_name_l = name.size();
        }
    }

    return max_name_l;
}

size_t get_max_educt_size(const std::vector<Reaction>& reactions) {
    size_t educt_size(0);

    for (const auto& reaction : reactions) {
        size_t loc_size(0);

        for (size_t i = 0; i < reaction.educt_stoichiometric_coefficients.size(); i++) {
            if (!reaction.educt_stoichiometric_coefficients.at(i)) {
                continue;
            }

            loc_size++;
        }

        if (loc_size > educt_size) {
            educt_size = loc_size;
        }
    }

    return educt_size;
}

size_t get_max_product_size(const std::vector<Reaction>& reactions) {
    size_t product_size(0);

    for (const auto& reaction : reactions) {
        size_t loc_size(0);

        for (size_t i = 0; i < reaction.product_stoichiometric_coefficients.size(); i++) {
            if (!reaction.product_stoichiometric_coefficients.at(i)) {
                continue;
            }

            loc_size++;
        }

        if (loc_size > product_size) {
            product_size = loc_size;
        }
    }

    return product_size;
}

std::string tab(const size_t& n) {
    std::string str;

    for (size_t i = 0; i < n; i++) {
        str += " ";
    }

    return str;
}

std::string tab() { return tab(tab_size); }

}  // namespace sc_print_algorithms
}  // namespace chem
