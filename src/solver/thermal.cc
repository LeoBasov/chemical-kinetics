#include "thermal.h"

namespace chem {

Thermal::Thermal() {}

double Thermal::calc_temperature(const VectorXd& concentrations, const VectorXd& heat_capacities, const VectorXd& dX,
                                 const VectorXd& enthalpies) {
    switch (type) {
        case CONSTANT: {
            break;
        }
        case VARIABLE: {
            const double heat_capacity = algorithms::calc_total_heat_capcity(concentrations, heat_capacities);
            const double enthalpy = algorithms::calc_total_enthalpy_diff(dX, enthalpies);

            temperature += enthalpy / heat_capacity;

            break;
        }
        default:
            throw Exception("undefined case", __PRETTY_FUNCTION__);
    }

    return temperature;
}

double Thermal::get_last_temperature() const { return temperature; }

}  // namespace chem
