#include "timestep.h"

namespace chem {

TimeStep::TimeStep() {}

double TimeStep::calc_dt(const VectorXd& concentrations, const VectorXd& dX_dt) {
    switch (type_) {
        case VARIABLE: {
            last_dt_ = value_;
            break;
        }
        case CONSTANT: {
            last_dt_ = algorithms::calc_time_step(concentrations, dX_dt, value_);
            break;
        }
    }

    return last_dt_;
}

double TimeStep::get_last_dt() const { return last_dt_; }

}  // namespace chem
