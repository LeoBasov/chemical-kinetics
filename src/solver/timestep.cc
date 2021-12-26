#include "timestep.h"

namespace chem {

TimeStep::TimeStep() {}

double TimeStep::calc_dt(const VectorXd& concentrations, const VectorXd& dX_dt) {
    switch (type) {
        case CONSTANT: {
            last_dt = value;
            break;
        }
        case VARIABLE: {
            last_dt = algorithms::calc_time_step(concentrations, dX_dt, value);
            break;
        }
    }

    return last_dt;
}

double TimeStep::get_last_dt() const { return last_dt; }

}  // namespace chem
