#include <Arduino.h>
#include "FourierTransform.h"
#include "CartesianCoordinates.h"
#include "Plotter.h"

const int T_MIN = 0.0;
const int T_MAX = 200.0;
const int ARR_LENGTH = 10000;
const float T_RES = ((T_MAX - T_MIN)/(float)ARR_LENGTH);

const int PWM_FRQ = 585937;

int a;
int b;
Plotter p;

class CarCoor{
public:
  float x;
  float y;

  int x_i;
  int y_i;
};

float x_min;
float x_max;
float y_min;
float y_max;

CarCoor figure[ARR_LENGTH];

double mapf(double val, double in_min, double in_max, double out_min, double out_max) {
  return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void store_parameter(){
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

  }
  for (int i = 0; i < ARR_LENGTH; i++){
    figure[i].x_i = mapf(figure[i].x,x_min,x_max,0,255);
    figure[i].y_i = mapf(figure[i].y,y_min,y_max,0,255);
  }
}

void setup() {
  p.Begin();
  // put your setup code here, to run once:
  p.AddXYGraph( "X-Y graph w/ 500 points", 500, "x axis", a, "y axis", b );

  analogWriteFrequency(2,PWM_FRQ);
  analogWriteFrequency(3,PWM_FRQ);
  Serial.begin(115200);
  
  store_parameter();
  digitalWrite(LED_BUILTIN,HIGH);
}

void loop() {
  static int t = 0;
  if(t<ARR_LENGTH){
    t++;
  }else{
    t = 0;
  }

  a = figure[t].x_i;
  b = figure[t].y_i;
  // p.Plot();
  delayMicroseconds(20);
  analogWrite(2, a);
  analogWrite(3, b);
}