#ifndef u_math_h
#define u_math_h

#include <Arduino.h>
#include "FourierTransform.h"

FourierTransform::CarCoor point;

FourierTransform::CarCoor roll(float t,FourierTransform::CarCoor point){
    FourierTransform::CarCoor retVal;
    const float rollDeg = 90;

    float rollRad = rollDeg * ((2*PI)/360);

    t = 1 - t;
    retVal.x = point.x * cos(rollRad * t) - point.y * sin(rollRad * t);
    retVal.y = point.y * cos(rollRad * t) + point.x * sin(rollRad * t);
    return retVal;
}

FourierTransform::CarCoor zoom(float t,FourierTransform::CarCoor point){
    FourierTransform::CarCoor retVal;

    retVal.x = point.x * t;
    retVal.y = point.y * t;
    return retVal;
}
#endif