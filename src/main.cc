#include "io/reader.h"
#include "io/sc_print_algorithms.h"
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

            reader.read_file(file_name);

            //---------------------------------------
            sc_print_algorithms::print_species(reader.get_species());
            sc_print_algorithms::print_reactions(reader.get_reactions(), reader.get_species());
            //---------------------------------------

            set_up_solver(solver, reader);
            writer.open("file.csv", reader.get_species_names());

            std::cout << "executing" << std::endl;
            write_header(reader);
            write_body(solver.get_state());
            writer.write_state(solver.get_state());

            for (int i = 0; i < n_iters; i++) {
                solver.execute();
                write_body(solver.get_state());
                writer.write_state(solver.get_state());
            }
        }
    } catch (Exception& e) {
        std::cout << "\"" << e.what() << "\" thrown in " << e.where() << std::endl;
        return 1;
    } catch (std::exception& e) {
        std::cout << "\"" << e.what() << "\"" << std::endl;
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
    std::cout << "t, T";

    for (const auto& name : reader.get_species_names()) {
        std::cout << ", " << name;
    }

    std::cout << std::endl;
}

void write_body(const Solver::State& state) {
    std::cout << std::to_string(state.time) << ", " << std::to_string(state.temperature);

    for (long i = 0; i < state.concentrations.size(); i++) {
        std::cout << ", " << std::to_string(state.concentrations(i));
    }

    std::cout << std::endl;
}
