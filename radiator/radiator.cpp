#include "radiator.h"

Radiator::Radiator(Size base_size, Size fin_size,
    double fin_step, double fin_area_width,
    double conductivity)
        : base_size_{base_size}, fin_size_{fin_size},
          fin_step_{fin_step}, fin_area_width_{fin_area_width},
          conductivity_{conductivity} {
}

double Radiator::GetRadiatorTemperature(double t_env, double thermal_power, Orientation orient) {
    if (temperature_.value()
            && t_env == t_env_.value()
            && thermal_power == thermal_power_.value()
            && orient == orient_.value()) {
    } else {
        env_t_ = env_t;
        thermal_power_ = thermal_power;
        orient_ = orient;
        CalculateTemperature();
    }
    return temperature_.value();
}

void Radiator::CalculateTemperature() {


    float KinVisc,Lamda,g,Pr,Gr,tm,AlfaSK,AlfaFK;
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
    }
}
