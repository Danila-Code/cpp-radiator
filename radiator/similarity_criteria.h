#ifndef SIMILARITY_CRITERIA_H
#define SIMILARITY_CRITERIA_H

#endif // SIMILARITY_CRITERIA_H

#include "air_property.h"

#include <cmath>

// similarity criteria

// acceleration of free fall
const double g = 9.81;

// The Prandtl criterion
double Pr(double t) {
    return HCapacity(t) * DViscosity(t) / Conductivity(t);
}

// The Reynolds criterion
// size - defining size
// t - defining temperature
double Re(double speed, double size, double t) {
    speed * dimension / KViscosity(t);
}

// the Grasgoff criterion
// size - defining size
// tw - temperature of wall
// tf - temperature of fluid
// td - defining temperature
double Gr(double size, double tw, double tf, double td) {
    return g * VolExpCoeff(td) * (tw - tf)
               / KViscosity(td) / KViscosity(td)
               * std::pow(size, 3);
}
