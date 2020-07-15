#ifndef u_math_h
#define u_math_h

#include <Arduino.h>
#include "FourierTransform.h"

FourierTransform::CarCoor point;

FourierTransform::CarCoor roll(double t,FourierTransform::CarCoor point){
    FourierTransform::CarCoor retVal;
    const double rollDeg = 360;

    double rollRad = rollDeg * ((2*PI)/360);

    t = 1 - t;
    retVal.x = point.x * cos(rollRad * t) - point.y * sin(rollRad * t);
    retVal.y = point.y * cos(rollRad * t) + point.x * sin(rollRad * t);
    return retVal;
}

FourierTransform::CarCoor zoom(double t,FourierTransform::CarCoor point){
    FourierTransform::CarCoor retVal;

    retVal.x = point.x * t;
    retVal.y = point.y * t;
    return retVal;
}

FourierTransform::CarCoor initial(double t){
    FourierTransform::CarCoor retVal;
    if (t < 0.2){
        retVal.x = -0.5;
        retVal.y = -0.5 + (t/0.2) * (1.0);
    }else if(t < 0.4){
        t -= 0.2;
        retVal.x = -0.5 + (t/0.2) * (1.0);
        retVal.y = 0.5;
    }else if(t < 0.6){
        t -= 0.4;
        retVal.x = 0.5;
        retVal.y = 0.5 - (t/0.2) * (1.0);
    }else if(t < 0.8){
        t -= 0.6;
        retVal.x = 0.5 - (t/0.2) * (1.0);
        retVal.y = -0.5;
    }else if(t < 1.0){
        retVal.x = 0;
        retVal.y = 0;
    }
    return retVal;
}
#endif