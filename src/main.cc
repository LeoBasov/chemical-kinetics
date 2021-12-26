#include "io/reader.h"
#include "io/writer.h"
#include "solver/solver.h"

using namespace chem;

void set_up_solver(Solver& solver, const Reader& reader);
void write_header(const Reader& reader);
void write_body(const Solver::State& state);

int main(int argc, char** argv) {
    Reader reader;
    Writer writer;
    Solver solver;
    int n_iters(0);
    std::string file_name;

    try {
        if (argc != 3) {
            throw Exception("wrong argument count [" + std::to_string(argc) + "]", __PRETTY_FUNCTION__);
        } else {
            file_name = argv[1];
            n_iters = std::stoi(argv[2]);

            std::cout << "reading" << std::endl;
            reader.read_file(file_name);

            set_up_solver(solver, reader);

            std::cout << "executing" << std::endl;
            write_header(reader);
            write_body(solver.get_state());

            for (int i = 0; i < n_iters; i++) {
                solver.execute();
                write_body(solver.get_state());
            }

            std::cout << "writing" << std::endl;
        }
    } catch (Exception& e) {
        std::cout << "\"" << e.what() << "\" thrown in " << e.where() << std::endl;
        return 1;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}

void set_up_solver(Solver& solver, const Reader& reader) {
    solver.set_concentrations(reader.get_concentrations());
    solver.set_reaction_powers(reader.get_reaction_powers());
    solver.set_stochiometric_matrix(reader.get_stochiometric_matrix());
    solver.set_rate_constants(reader.get_rate_constants());
    solver.set_time_step(reader.get_time_step());
    solver.set_thermal(reader.get_thermal());
}

void write_header(const Reader& reader) {
    std::cout << "#t,#T";

    for (const auto& name : reader.get_species_name()) {
        std::cout << ",#" << name;
    }

    std::cout << std::endl;
}

void write_body(const Solver::State& state) {
    std::cout << state.time << "," << state.temperature;

    for (long i = 0; i < state.concentrations.size(); i++) {
        std::cout << "," << state.concentrations(i);
    }

    std::cout << std::endl;
}
