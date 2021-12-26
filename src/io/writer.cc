#include "writer.h"

namespace chem {

Writer::Writer() {}

void Writer::open(const std::string& file_name, const std::vector<std::string>& species_names) {
    stream_.open(file_name);

    if (!stream_.is_open()) {
        throw Exception("could not open/create file", __PRETTY_FUNCTION__);
    }

    write_header(species_names);
}

void Writer::write_header(const std::vector<std::string>& species_names) {
    stream_ << "#t, #T, #k" << std::endl;

    for (const auto& name : species_names) {
        stream_ << ", " << name;
    }

    stream_ << std::endl;
}

}  // namespace chem
