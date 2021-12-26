#include "reader.h"

namespace chem {

Reader::Reader() {}

Solver Reader::read_file(const std::string& file_name) const {
    Solver solver;
    Species species = add_species(file_name);
    std::vector<Reaction> reactions = add_reactions(file_name, species.names);

    return solver;
}

}  // namespace chem
