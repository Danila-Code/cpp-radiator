#pragma once
// all sizes in meters
// temperatures in degrees Celsius
#include <vector>

struct Results {
    double temperature;
    std::vector<double> conducts; // last element holds sum of conducts
    std::vector<double> powers; // last element holds sum of powers
};

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
    Radiator() = default;
    Radiator(Size base_size, Size fin_size,
             double fin_step_, double fin_area_width_,
             double conductivity, double blackness);

    Results Calculate();

// setters
    // base sizes
    void SetBaseWidth(double width);
    void SetBaseLength(double length);
    void SetBaseThickness(double thickness);
    // fins sizes
    void SetFinLength(double length);
    void SetFinWidth(double width);
    void SetFinHeight(double height);
    void SetFinAreaWidth(double fin_area_width);
    void SetFinStep(double fin_step);
    // thermal params
    void SetConductivity(double conductivity);
    void SetBlackness(double blackness);

    void SetPower(double power);
    void SetTEnv(double t_env);
    // orientation
    void SetOrientation(Orientation orient);

private:
    // base sizes
    Size base_size_;
    // fin sizers
    Size fin_size_;

    double fin_step_;
    // width of area with fins
    double fin_area_width_;
    // thermal conductivity of radiator material
    double conductivity_;
    // degree of blackness
    double blackness_;


    // orientation of radiator and fin in space
    Orientation orient_;

    // thermal power
    double thermal_power_;
    // temperature of environment
    double t_env_;
    // temperature of radiator
    double temperature_;
};
