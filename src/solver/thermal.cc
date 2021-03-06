#include "thermal.h"

namespace chem {

Thermal::Thermal() {}

void Thermal::set_type(Type type) { type_ = type; }

void Thermal::set_temperature(const double& temperature) { temperature_ = temperature; }

double Thermal::calc_temperature(const VectorXd& concentrations, const VectorXd& heat_capacities, const VectorXd& dX,
                                 const VectorXd& enthalpies) {
    switch (type_) {
        case CONSTANT: {
            break;
        }
        case VARIABLE: {
            const double heat_capacity = algorithms::calc_total_heat_capcity(concentrations, heat_capacities);
            const double enthalpy = algorithms::calc_total_enthalpy_diff(dX, enthalpies);

            temperature_ += enthalpy / heat_capacity;

            break;
        }
        default:
            throw Exception("undefined case", __PRETTY_FUNCTION__);
    }

    return temperature_;
}

double Thermal::get_temperature() const { return temperature_; }

Thermal::Type Thermal::get_type() const { return type_; }

}  // namespace chem
