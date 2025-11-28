#include "radiator.h"

Radiator::Radiator(Size base_size, Size fin_size,
    double fin_step, double fin_area_width,
    double conductivity, double  blackness)
        : base_size_{base_size}, fin_size_{fin_size},
          fin_step_{fin_step}, fin_area_width_{fin_area_width},
          conductivity_{conductivity}, blackness_{blackness} {
}

double Radiator::GetRadiatorTemperature(double t_env, double thermal_power, Orientation orient) {
    if (temperature_.value()
            && t_env == t_env_.value()
            && thermal_power == thermal_power_.value()
            && orient == orient_) {
    } else {
        t_env_ = t_env;
        thermal_power_ = thermal_power;
        orient_ = orient;
        CalculateTemperature();
    }
    return temperature_.value();
}

void Radiator::CalculateTemperature() {


    /*float KinVisc,Lamda,g,Pr,Gr,tm,AlfaSK,AlfaFK;
    float H,B,F,L,LS,f,U,AlfaL;
    tm=0.5*(tEnv+tF);
    KinVisc=AirKinViscosity(tm);
    Lamda=AirConductivity(tm);
    Pr=AirPr(tm);

    int fin_number = (fin_area_width_ - fin_size_.width) / fin_step + 1;

    switch(orient_){
    case 0:
        L = base_size_.length;
        F = 1;
        LS = fin_size_.length;
        break;
    case 1:
        L = base_size_.width;
        F = 1;
        LS = fin_number * (2 * fin_size_.height + fin_step_)
             - (fin_step_ - fin_size_.width);
        break;
    case 2:
        L = base_size_.length;
        F = 1.3;
        LS = fin_size_.length;
        break;
    case 3:
        L = base_size_.length;
        F = 0.7;
        LS = fin_size_.length;
        break;
    }

    AlfaSK = F * AlfaConv(t, t_env_, LS);

    if(orient_ == Orientation::VerticalHorizontalFin) {
        AlfaSK = AlfaSK * 0.5 * (1 + 0.7);
    }

    AlfaFK = F * AlfaKonvRad(t, t_env_, L);

    U = 2 * (WidthS + LengthS);
    f = WidthS * LengthS;
    B = std::pow(AlfaSK*U/(LamdaM*f), 0.5);
    H = HeightS + f/U;

    conduc[2]=N*LamdaM*f*B*tanh(B*H)
                +AlfaSK*(N-1)*LengthBetveenS*LengthS;
    conduc[3]=AlfaFK*(WidthF*LengthF-N*WidthS*LengthS
                          -(N-1)*LengthBetveenS*LengthS+2*(LengthF+WidthF)*HeightF);
    AlfaL=CalcAlfaL(tF,tEnv,E);
    conduc[0]=AlfaL*((LengthBetveenS*(N-1)+WidthS*N)*LengthS+2*((LengthBetveenS*(N-1)+WidthS*N)+LengthS)*HeightS);
    conduc[1]=AlfaL*(WidthF*LengthF-N*WidthS*LengthS-LengthBetveenS*(N-1)*LengthS+2*(LengthF+WidthF)*HeightF);
    conduc[4]=0;
    P[4]=0;
    for(int i=0;i<4;i++){
        P[i]=conduc[i]*(tF-tEnv);
        conduc[4]+=conduc[i];
        P[4]+=P[i];
    }*/
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
