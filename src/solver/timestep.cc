#include "timestep.h"

namespace chem {

TimeStep::TimeStep() {}

double TimeStep::get_dt(const VectorXd& concentrations, const VectorXd& dX_dt) const {
    switch (type_) {
        case VARIABLE: {
            return value_;
            break;
        }
        case CONSTANT: {
            return algorithms::calc_time_step(concentrations, dX_dt, value_);
            break;
        }
    }
}

}  // namespace chem
