#include "sc_print_algorithms.h"

namespace chem {
namespace sc_print_algorithms {

void print_species(const Species& species) {
    const size_t n_name(7);
    const size_t n_concentration(13);
    const size_t tab_size(4);

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

    std::cout << tab(tab_size) << "╚═════════╧═══════════════╝" << std::endl;
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
