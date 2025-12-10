#include "heat_exchange.h"
#include "radiator.h"
#include "solver.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>

Radiator::Radiator(Size base_size, Size fin_size,
    double fin_step, double fin_area_width,
    double conductivity, double  blackness)
        : base_size_{base_size}, fin_size_{fin_size},
          fin_step_{fin_step}, fin_area_width_{fin_area_width},
          conductivity_{conductivity}, blackness_{blackness} {
}

void Radiator::CalculateT(Results& res0) {
    // squares
    // the area of projection of the edges on the base
    double fins_base_sq = fin_area_width_ * fin_size_.length;
    // the surface area stretched over the radiator's fins
    double streched_sq = 2 * (fin_area_width_ + fin_size_.length) * fin_size_.height
                         + fins_base_sq;
    // radiator base area
    double base_sq = base_size_.length * base_size_.width
                     + 2 * (base_size_.width + base_size_.length) * base_size_.height;
    // radiator base area without fins streched area
    double base_without_fins_sq = base_sq - fins_base_sq;

    // length between two fins
    double can_width = fin_step_ - fin_size_.width;
    // numbers of fins

    assert(fin_step_);

    int fin_number = (fin_area_width_ - fin_size_.width) / fin_step_ + 1;
    // defining size for base
    double l_base;
    // defining size for fins
    double l_fins;
    // orientation coefficient
    double orient_coeff = 1;

    // the transverse perimeter of fin
    double fin_perim = 2 * fin_size_.length * fin_size_.width;
    // cross-sectional area of fin
    double fin_section_sq = fin_size_.length * fin_size_.width;
    // between fins area
    double between_fins_sq = fins_base_sq - fin_section_sq * fin_number;

    assert(fin_perim);
    // effective fins height
    double fin_height = fin_size_.height + fin_section_sq / fin_perim;

    switch(orient_){
    case Orientation::VerticalVerticalFin: // vertical with vertical fins
        l_base = base_size_.length;
        l_fins = fin_size_.length;
        break;
    case Orientation::VerticalHorizontalFin: // vertical with horizontal fins
        l_base = base_size_.width;
        // the length of the path enclosed by air
        l_fins = fin_number * 2 * fin_size_.height + fin_area_width_;
        break;
    case Orientation::HorizontaUpFin: // horizontal with fins up
        l_base = std::min(base_size_.length, base_size_.width);
        orient_coeff = 1.3;
        l_fins = fin_size_.length;
        break;
    case Orientation::HorizontalDownFin: // horizontal with fins down
        l_base = std::min(base_size_.length, base_size_.width);
        orient_coeff = 0.7;
        l_fins = fin_size_.length;
        break;
    }

    // P = alfa * S * (tw - t_env_)
    double cond_conv_base, cond_conv_fins, cond_rad_fins, cond_rad_base, sum_conducts;
    double t0 = res0.temperature;

        // convective heat transfer coefficient for radiators base
        double alfa_conv_base = orient_coeff * AlfaConvRad(t0, t_env_, l_base);
        // convective conduction from radiators base
        cond_conv_base = alfa_conv_base * base_without_fins_sq ;

        // convective heat transfer coefficient for radiators fins
        double alfa_conv_fins = orient_coeff * AlfaConv(t0, t_env_, l_fins);

        assert(conductivity_);
        assert(fin_section_sq);

        // intermediate value
        double temp = std::pow(alfa_conv_fins * fin_perim / conductivity_ / fin_section_sq, 0.5);

        double cond_conv_one_fin = conductivity_ * fin_section_sq * temp * std::tanh(temp * fin_height);
        // convective conduction from radiators fins
        cond_conv_fins = fin_number * cond_conv_one_fin
                         + alfa_conv_fins * between_fins_sq;

        // radiant heat transfer coefficient
        double alfa_rad = AlfaRadiant(t0, t_env_, blackness_);
        // radiant conduction from radiator's fins
        cond_rad_fins = alfa_rad * streched_sq;
        // radiant conduction from radiator's base
        cond_rad_base = alfa_rad * base_without_fins_sq;

        sum_conducts = cond_conv_base + cond_conv_fins + cond_rad_base + cond_rad_fins;

        assert(sum_conducts);

        res0.temperature = thermal_power_ / sum_conducts + t_env_;

    res0.conducts = {cond_rad_base, cond_rad_fins,
                     cond_conv_base, cond_conv_fins, sum_conducts};
    res0.powers = std::vector<double>(res0.conducts.size());

    std::transform(res0.conducts.begin(), res0.conducts.end(), res0.powers.begin(), [this, res0](double value) {
        return value * (res0.temperature - t_env_);
    });
}

Results Radiator::Calculate() {
    Solver solver(0.7, 1e-3);

    // squares
    // the area of projection of the edges on the base
    double fins_base_sq = fin_area_width_ * fin_size_.length;
    // the surface area stretched over the radiator's fins
    double streched_sq = 2 * (fin_area_width_ + fin_size_.length) * fin_size_.height
                         + fins_base_sq;
    // radiator base area
    double base_sq = base_size_.length * base_size_.width
                     + 2 * (base_size_.width + base_size_.length) * base_size_.height;
    // radiator base area without fins streched area
    double base_without_fins_sq = base_sq - fins_base_sq;

    // P = alfa * S * (tw - t_env_)
    double t0 = thermal_power_ / 10 / (base_without_fins_sq + streched_sq) + t_env_;

    std::function<void(Results&)> calc_func = [this](Results& r) {
        CalculateT(r);
    };

    Results res{t0};
    solver.Solve(res, calc_func);
    return res;
}

// Setters
void Radiator::SetBaseWidth(double width) {
    base_size_.width = width;
}

void Radiator::SetBaseLength(double length) {
    base_size_.length = length;
}

void Radiator::SetBaseThickness(double thickness) {
    base_size_.height = thickness;
}

void Radiator::SetFinLength(double length) {
    fin_size_.length = length;
}

void Radiator::SetFinWidth(double width) {
    fin_size_.width = width;
}

void Radiator::SetFinHeight(double height) {
    fin_size_.height = height;
}

void Radiator::SetFinAreaWidth(double fin_area_width) {
    fin_area_width_ = fin_area_width;
}

void Radiator::SetFinStep(double fin_step) {
    fin_step_ = fin_step;
}

void Radiator::SetConductivity(double conductivity) {
    conductivity_ = conductivity;
}

void Radiator::SetBlackness(double blackness) {
    blackness_ = blackness;
}

void Radiator::SetPower(double power) {
    thermal_power_ = power;
}

void Radiator::SetTEnv(double t_env) {
    t_env_ = t_env;
}

void Radiator::SetOrientation(Orientation orient) {
    orient_ = orient;
}
