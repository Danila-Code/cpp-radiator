#include "heat_exchange.h"

#include <algorithm>
#include <array>

namespace {
FlowMode GetFlowMode(double value) {
    const std::array<double, 4> GrPr{1e-3, 500, 2e7, 1e13};
    for (int i = 0; i < GrPr.size(); ++i) {
        if (value <= GrPr[i]) {
            return static_cast<FlowMode>(i);
        }
    }
}
}  // namespace

// return radiant heat transfer coefficient
// blackness - degree of blackness
double AlfaRadiant(double t1, double t2, double blackness) {
    // temperatures in K degree
    double tk1 = t1 + T0;
    double tk2 = t2 + T0;
    double tk_sum = tk1 + tk2;
    return (tk1 / tk_sum * tk1  + tk2 / tk_sum * tk2) * SIGMA * blackness;
}

// return convective heat transfer coefficien
// size - defining size
// tw - temperature of wall
// tf - temperature of fluid
double AlfaKonv(double tw, double tf, double size) {
    // coeffs in criteria formula Nu = Coef * (Gr * Pr)^CoefDegree
    const std::array<double, 4> Coef = {0.5, 1.18, 0.54, 0.135};
    const std::array<double, 4> CoefDegree = {0, 0.125, 0.25, 0.33};

    double td = (tw + tf) / 2;  // defining temperature
    double value = Gr(size, tw, tf, td) * Pr(td);
    int mode = static_cast<int>(GetFlowMode(value));

    return Coef[mode] * std::pow(value, CoefDegree[mode])
                      * Conductivity(td) / size;
}

//Расчёт конвективного коэффициента теплоотдачи для радиатора в неограниченном пространстве
double AlfaKonvRad(double tw,double tf,double size){
    double alfaK, Const, td;
    td = 0.5 * (tw + tf);
    Const = std::pow(840 * 1000 / size, 3);
    if((tw - tf) < Const){
        alfaK = (1.423 - 0.0023699 * td + 8.4493e-6 * td * td)
                * std::pow(abs(tw - tf) / size, 0.25);
    }else{
        alfaK = (1.7004 - 0.0047922 * td + 1.1259e-5 * td * td)
                * std::pow(abs(tw - tf), 0.33);
    }
    return alfaK;
}
