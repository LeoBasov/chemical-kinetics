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

}  // namespace io_algorithms
}  // namespace chem
