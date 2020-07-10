#include <Arduino.h>
#include "FourierTransform.h"
#include "Plotter.h"

double x;
double y;
Plotter p;

void setup() {
  p.Begin();
  // put your setup code here, to run once:
  p.AddXYGraph( "X-Y graph w/ 500 points", 500, "x axis", x, "y axis", y );

  analogWriteFrequency(10,234375);
}

void loop() {
  // put your main code here, to run repeatedly:
  // analogWrite(10, 256*((millis() % 100)/100.0f));
  static float t = 0;
  if(t<200){
    t+=0.1;
  }else{
    t = 0.1;
  }
  x =return_x(t);
  y = return_y(t);
  p.Plot();
}