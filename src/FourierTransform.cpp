#include "FourierTransform.h"
#include <Arduino.h>

FourierTransform::FourierTransform(CarCoorFunction functions[]){
    NumFunctions = 1;//sizeof(functions)/sizeof(functions[0]);
    figureFunctions = new CarCoorFunction[NumFunctions];

    for (int i = 0; i < NumFunctions; i++) {
        figureFunctions[i].x = functions[i].x;
        figureFunctions[i].y = functions[i].y;
    }
}

double FourierTransform::mapf(double val, double in_min, double in_max, double out_min, double out_max){
    return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void FourierTransform::store_parameter(int t_min, int t_max, int arr_length){
    T_MIN = t_min;
    T_MAX = t_max;
    NumPoints = arr_length;

    T_RES = ((T_MAX - T_MIN)/(double)NumPoints);
    figurePoints = new CarCoorPoint[NumPoints];

    for (int i = 0; i < NumPoints; i++){
        figurePoints[i].x = figureFunctions[0].x(i*T_RES);
        figurePoints[i].y = figureFunctions[0].y(i*T_RES);

        if(i == 0){
            minVal = figurePoints[i];
            maxVal = figurePoints[i];
        }else{
            minVal.x = min(minVal.x,figurePoints[i].x);
            minVal.y = min(minVal.y,figurePoints[i].y);
            maxVal.x = max(maxVal.x,figurePoints[i].x);
            maxVal.y = max(maxVal.y,figurePoints[i].y);
        }
        progress(i);
    }
    for (int i = 0; i < NumPoints; i++){
        figurePoints[i].x = mapf(figurePoints[i].x,minVal.x,maxVal.x,0.5 - (aspect.x/2.0), 0.5 + (aspect.x/2.0)) - 0.5;
        figurePoints[i].y = mapf(figurePoints[i].y,minVal.y,maxVal.y,0.5 - (aspect.y/2.0), 0.5 + (aspect.y/2.0)) - 0.5;
    }
}
