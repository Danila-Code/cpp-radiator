#ifndef HEAT_EXCHANGE_H
#define HEAT_EXCHANGE_H

#endif // HEAT_EXCHANGE_H

#include "similarity_criteria.h"

// the Stefan-Boltzmann constant
const double SIGMA = 5.67e-8;

enum class FlowMode {
    FILM,
    LAMINAR,
    TRANSITIONAL,
    TURBULENT
};

// return radiant heat transfer coefficient
// blackness - degree of blackness
double AlfaRadiant(double t1, double t2, double blackness);

// return convective heat transfer coefficien
// size - defining size
// tw - temperature of wall
// tf - temperature of fluid
double AlfaKonv(double tw, double tf, double size);

double AlfaKonvRad(double tw,double tf,double size);
