#ifndef hardware_h
#define hardware_h

#include <Arduino.h>
#include "FourierTransform.h"

const int PWM_FRQ = 585937;
const int PWM_RES = 256;

const int PIN_X = 5;
const int PIN_Y = 6;

void pinInit(){
    analogWriteFrequency(PIN_X,PWM_FRQ);
    analogWriteFrequency(PIN_Y,PWM_FRQ);
}

void plot(FourierTransform::CarCoorPoint point){
    point.x += 0.5;
    point.y += 0.5;
    analogWrite(PIN_X, point.x * PWM_RES);
    analogWrite(PIN_Y, point.y * PWM_RES);
}

#endif