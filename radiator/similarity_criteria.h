#pragma once

#include "air_property.h"

#include <cmath>

// similarity criteria

// acceleration of free fall
const double g = 9.81;

// The Prandtl criterion
inline double Pr(double t) {
    return HCapacity(t) * DViscosity(t) / Conductivity(t);
}

// The Reynolds criterion
// size - defining size
// t - defining temperature
inline double Re(double speed, double size, double t) {
    return speed * size / KViscosity(t);
}

// the Grasgoff criterion
// size - defining size
// tw - temperature of wall
// tf - temperature of fluid
// td - defining temperature
inline double Gr(double size, double tw, double tf, double td) {
    return g * VolExpCoeff(td) * (tw - tf)
               / KViscosity(td) / KViscosity(td)
               * std::pow(size, 3);
}
