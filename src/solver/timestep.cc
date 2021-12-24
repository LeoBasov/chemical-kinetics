#include "timestep.h"

namespace chem {

TimeStep::TimeStep() {}

double TimeStep::get_dt(const VectorXd& concentrations, const VectorXd& dX_dt) const {
    double ret_val(value_);

    switch (type_) {
        case VARIABLE: {
            double val(0.0);

            for (long i = 0; i < concentrations.size(); i++) {
            }

            break;
        }
    }

    return ret_val;
}

}  // namespace chem
