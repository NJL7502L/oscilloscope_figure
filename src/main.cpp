#include <Arduino.h>
#include "Fusiclogo.h"
#include "FourierTransform.h"
#include "Plotter.h"

// const int T_MIN = 0.0;
// const int T_MAX = 200.0;
// const int ARR_LENGTH = 31916;
// const float T_RES = ((T_MAX - T_MIN)/(float)ARR_LENGTH);

const int PWM_FRQ = 585937;

int a;
int b;
Plotter p;

FourierTransform Fusic(return_x,return_y);

void setup() {
  p.Begin();
  // put your setup code here, to run once:
  p.AddXYGraph( "X-Y graph w/ 500 points", 500, "x axis", a, "y axis", b );

  analogWriteFrequency(2,PWM_FRQ);
  analogWriteFrequency(3,PWM_FRQ);
  Serial.begin(115200);

  digitalWrite(LED_BUILTIN,HIGH);
  Fusic.store_parameter(0,200,30000);
}

void loop() {
  static int t = 0;
  if(t<Fusic.ARR_LENGTH){
    t++;
  }else{
    t = 0;
  }

  a = Fusic.figure[t].x_i;
  b = Fusic.figure[t].y_i;
  // p.Plot();
  delayMicroseconds(20);
  analogWrite(2, a);
  analogWrite(3, b);
}
