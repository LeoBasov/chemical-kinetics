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
    for (size_t i = 0; i < reactions.size(); i++) {
        print_reaction(reactions.at(i), species);
    }

    std::cout << std::endl;
}

void print_reaction(const Reaction& reactions, const Species& species) {
    bool skipped(false);

    std::cout << tab(tab_size) << "reaction: ";

    for (size_t i = 0; i < reactions.educt_stoichiometric_coefficients.size(); i++) {
        if (!reactions.educt_stoichiometric_coefficients.at(i)) {
            skipped = true;
            continue;
        }

        if (i && !skipped) {
            std::cout << " + ";
        }

        std::cout << reactions.educt_stoichiometric_coefficients.at(i) << "⋅" << species.names.at(i);
        skipped = false;
    }

    std::cout << " →  ";

    for (size_t i = 0; i < reactions.product_stoichiometric_coefficients.size(); i++) {
        if (!reactions.product_stoichiometric_coefficients.at(i)) {
            skipped = true;
            continue;
        }

        if (i && !skipped) {
            std::cout << " + ";
        }

        std::cout << reactions.product_stoichiometric_coefficients.at(i) << "⋅" << species.names.at(i);
        skipped = false;
    }

    std::cout << std::endl;
}

std::string tab(const size_t& n) {
    std::string str;

    for (size_t i = 0; i < n; i++) {
        str += " ";
    }

    return str;
}

}  // namespace sc_print_algorithms
}  // namespace chem
