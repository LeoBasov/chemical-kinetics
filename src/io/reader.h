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
    std::vector<RateConstant> get_rate_constants() const;
    std::vector<std::string> get_species_names() const;
    TimeStep get_time_step() const;
    Thermal get_thermal() const;

    Species get_species() const;

   private:
    Species species_;
    std::vector<Reaction> reactions_;
    TimeStep time_step_;
    Thermal thermal_;
};

}  // namespace chem
