#ifndef AIR_PROPERTY_H
#define AIR_PROPERTY_H

#endif // AIR_PROPERTY_H

const double T0 = 273.15;

// The temperature t is set in degrees Celsius

// air density
double Density(double t) {
    return 1.296 - 4.9e-3 * t + 1.4e-5 * t * t;
}

// air kinematic viscosity
double KViscosity(double t) {
    return 1e-6 * (13.28 + 8.7e-2 * t + 1.2e-4 * t * t);
}

// air dynamic  viscosity
double DViscosity(double t) {
    return 1e-6 * (17.17 + 0.48 * t);
}

// air coductivity
double Conductivity(double t) {
    return 1e-2 * (2.44 + 7.8e-3 * t - 2e-6 * t * t);
}

// air heat capacity
double HCapacity(double t) {
    return 1006;
}

// air volumetric expansion coefficient
double VolExpCoeff(double t) {
    return 1 / (t + T0);
}

// thermal conductivity
double TConductivity(double t) {
    return Conductivity(t) / Density(t) / HCapacity(t);
}
