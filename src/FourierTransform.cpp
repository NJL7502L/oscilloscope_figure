#include "FourierTransform.h"
#include <Arduino.h>


FourierTransform::FourierTransform(double (*ret_x)(double), double (*ret_y)(double)){
    return_x = ret_x;
    return_y = ret_y;
}

double FourierTransform::mapf(double val, double in_min, double in_max, double out_min, double out_max){
    return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void FourierTransform::store_parameter(int t_min, int t_max, int arr_length){
    T_MIN = t_min;
    T_MAX = t_max;
    ARR_LENGTH = arr_length;

    T_RES = ((T_MAX - T_MIN)/(double)ARR_LENGTH);
    figure = new CarCoor[ARR_LENGTH];

    for (int i = 0; i < ARR_LENGTH; i++){
        figure[i].x = return_x(i*T_RES);
        figure[i].y = return_y(i*T_RES);

        if(i == 0){
            x_min = figure[i].x;
            x_max = figure[i].x;
            y_min = figure[i].y;
            y_max = figure[i].y;
        }else{
            x_min = min(x_min,figure[i].x);
            x_max = max(x_max,figure[i].x);
            y_min = min(y_min,figure[i].y);
            y_max = max(y_max,figure[i].y);
        }
        progress(i);
    }
    for (int i = 0; i < ARR_LENGTH; i++){
        figure[i].x = mapf(figure[i].x,x_min,x_max,0.5 - (aspect_x/2.0), 0.5 + (aspect_x/2.0)) - 0.5;
        figure[i].y = mapf(figure[i].y,y_min,y_max,0.5 - (aspect_y/2.0), 0.5 + (aspect_y/2.0)) - 0.5;
    }
}
