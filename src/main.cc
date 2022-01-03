#include "io/reader.h"
#include "io/sc_print_algorithms.h"
#include "io/writer.h"
#include "solver/solver.h"

using namespace chem;

void set_up_solver(Solver& solver, const Reader& reader);
void print_to_screen(const uint current_iteration, const uint max_iter);

int main(int argc, char** argv) {
    Reader reader;
    Writer writer;
    Solver solver;
    std::string file_name;

    try {
        if (argc != 2) {
            throw Exception("wrong argument count [" + std::to_string(argc) + "]", __PRETTY_FUNCTION__);
        } else {
            file_name = argv[1];

            reader.read_file(file_name);

            sc_print_algorithms::print_species(reader.get_species());
            sc_print_algorithms::print_reactions(reader.get_reactions(), reader.get_species());

            set_up_solver(solver, reader);
            writer.open(reader.get_output_file(), reader.get_species_names());

            writer.write_state(solver.get_state());

            for (unsigned int i = 0; i < reader.get_number_iterations(); i++) {
                solver.execute();
                print_to_screen(i, reader.get_number_iterations());
                writer.write_state(solver.get_state());
            }

            sc_print_algorithms::print_state(reader.get_species_names(), solver.get_state());
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

void print_to_screen(const uint current_iteration, const uint max_iter) {
    std::cout << "\r" << sc_print_algorithms::tab() << "iteration: " << current_iteration + 1 << "/" << max_iter;

    if (current_iteration + 1 >= max_iter) {
        std::cout << sc_print_algorithms::tab() << " : complete" << std::endl;
    }
}
