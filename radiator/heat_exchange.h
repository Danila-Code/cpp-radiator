#pragma once

#include "similarity_criteria.h"

// the Stefan-Boltzmann constant
const double SIGMA = 5.67;

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
double AlfaConv(double tw, double tf, double size);

double AlfaConvRad(double tw,double tf,double size);

// P = conduc * (tw - t_env);
double CalcP(double tw, double t_env, double conduc);
