#include <Arduino.h>
#include "FusicLogo.h"
#include "FourierTransform.h"
#include "Plotter.h"

const int PWM_FRQ = 585937;
const int PWM_RES = 256;

float point_x;
float point_y;
Plotter p;

FourierTransform FusicLogo(FusicLogo_x,FusicLogo_y);

void setup() {
  p.Begin();
  p.AddXYGraph( "X-Y graph w/ 500 points", 500, "x axis", point_x, "y axis", point_y);

  analogWriteFrequency(2,PWM_FRQ);
  analogWriteFrequency(3,PWM_FRQ);
  Serial.begin(115200);

  FusicLogo.aspect_ratio(1,1);
  FusicLogo.store_parameter(0,200,30000);
}

void loop() {
  static int t = 0;
  if(t<FusicLogo.ARR_LENGTH){
    t++;
  }else{
    t = 0;
  }

  point_x = FusicLogo.figure[t].x;
  point_y = FusicLogo.figure[t].y;

  analogWrite(2, point_x * PWM_RES);
  analogWrite(3, point_y * PWM_RES);

  // p.Plot();
  delayMicroseconds(20);
}
