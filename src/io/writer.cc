#include "writer.h"

namespace chem {

Writer::Writer() {}

void Writer::open(const std::string& file_name, const std::vector<std::string>& species_names) {
    stream_.open(file_name);

    if (!stream_.is_open()) {
        throw Exception("could not open or create file", __PRETTY_FUNCTION__);
    }

    write_header(species_names);
}

void Writer::write_header(const std::vector<std::string>& species_names) {
    stream_ << "#t,#T";

    for (const auto& name : species_names) {
        stream_ << ",#" << name;
    }

    stream_ << std::endl;
}

void Writer::write_state(const Solver::State& state) {
    stream_ << state.time << std::scientific << "," << std::to_string(state.temperature) << std::scientific;

    for (long i = 0; i < state.concentrations.size(); i++) {
        stream_ << "," << state.concentrations(i) << std::scientific;
    }

    stream_ << std::endl;
}

}  // namespace chem
