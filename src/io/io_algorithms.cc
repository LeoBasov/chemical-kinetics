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

    return species;
}

}  // namespace io_algorithms
}  // namespace chem
