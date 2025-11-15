#ifndef RADIATOR_H
#define RADIATOR_H

#endif // RADIATOR_H

#include <optional>

enum class Orientation {
    VerticalVerticalFin,
    VerticalHorizontalFin,
    HorizontaUpFin,
    HorizontalDownFin
};

struct Size {
    double length;
    double width;
    double height;
};

class Radiator {
public:
    Radiator(Size base_size, Size fin_size,
             double fin_step_, double fin_area_width_,
             double conductivity);

    double GetRadiatorTemperature(double t_env, double thermal_power, Orientation orient);
private:
    // calculate radiator temperature
    void CalculateTemperature();


    // base sizes
    Size base_size_;
    // fin sizers
    Size fin_size_;

    double fin_step_;
    // width of area with fins
    double fin_area_width_;
    // thermal conductivity of radiator material
    double conductivity_;

    // orientation of radiator and fin in space
    std::optional<Orientation> orient_;

    // thermal power
    std::optional<double> thermal_power_;
    // temperature of environment
    std::optional<double> t_env_;
    // temperature of radiator
    std::optional<double> temperature_;
};
