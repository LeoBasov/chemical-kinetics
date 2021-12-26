#pragma once

namespace chem {

struct Thermal {
    enum Type { CONSTANT };

    Thermal();
    ~Thermal() = default;

    Type type = CONSTANT;
    double value = 0.0;
};

}  // namespace chem
