#pragma once

#include "../solver/solver.h"
#include "reader_algorithms.h"

namespace chem {
using namespace reader_algorithms;

class Reader {
   public:
    Reader();
    ~Reader() = default;

    void read_file(const std::string& file_name);

    VectorXd get_concentrations() const;
    MatrixXd get_reaction_powers() const;
    MatrixXd get_stochiometric_matrix() const;
    VectorXd get_heat_capacities() const;
    VectorXd get_enthalpies() const;
    std::vector<RateConstant> get_rate_constants() const;
    std::vector<std::string> get_species_names() const;
    TimeStep get_time_step() const;
    Thermal get_thermal() const;

    Species get_species() const;
    std::vector<Reaction> get_reactions() const;
    unsigned int get_number_iterations() const;
    std::string get_output_file() const;

   private:
    Species species_;
    std::vector<Reaction> reactions_;
    TimeStep time_step_;
    Thermal thermal_;
    unsigned int number_iterations_ = 0;
    std::string output_file_;
};

}  // namespace chem
