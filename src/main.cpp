#include <Arduino.h>
#include "FourierTransform.h"
#include "CartesianCoordinates.h"
#include "Plotter.h"

int x;
int y;
Plotter p;

class CarCoor{
public:
  int x_i;
  int y_i;
};

CarCoor figure[10000];
// class Minmax{
// public:
//   float min;
//   float max;
// };
// Minmax m_x,m_y;


double mapf(double val, double in_min, double in_max, double out_min, double out_max) {
  return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void store_parameter(){
  for (int i = 0; i < 10000; i+=1){
    figure[i].x_i = mapf(return_x(200*(i/10000.0)),1480.15,1662.39,0,255);
    figure[i].y_i = mapf(return_y(200*(i/10000.0)),-1003.87,-821.45,0,255);
  }
}

void setup() {
  p.Begin();
  // put your setup code here, to run once:
  p.AddXYGraph( "X-Y graph w/ 500 points", 500, "x axis", x, "y axis", y );

  analogWriteFrequency(2,234375);
  analogWriteFrequency(3,234375);
  Serial.begin(115200);

  // m_x.min = return_x(0.1);
  // m_x.max = return_x(0.1);

  // m_y.min = return_y(0.1);
  // m_y.max = return_y(0.1);
  store_parameter();
}

// void print_minmax(){
//   // put your main code here, to run repeatedly:
//   // analogWrite(10, 256*((millis() % 100)/100.0f));
//   static float t = 0;

//   if(t<200){
//     t+=0.1;
//   }else{
//     t = 0.1;
//   }
//   x = return_x(t);
//   y = return_y(t);

//   m_x.min = min(m_x.min ,x);
//   m_x.max = max(m_x.max ,x);

//   m_y.min = min(m_y.min ,y);
//   m_y.max = max(m_y.max ,y);

//   Serial.print("\tx min:\t");
//   Serial.print(m_x.min);
//   Serial.print("\tx max:\t");
//   Serial.print(m_x.max);
//   Serial.print("\ty min:\t");
//   Serial.print(m_y.min);
//   Serial.print("\ty max:\t");
//   Serial.print(m_y.max);
//   Serial.print("\tt :\t");
//   Serial.print(t);
//   Serial.println();
//   // p.Plot();
// }

void loop() {
  // put your main code here, to run repeatedly:
  // analogWrite(10, 256*((millis() % 100)/100.0f));
  static int t = 0;
  if(t<10000){
    t++;
  }else{
    t = 0;
  }

  x = figure[t].x_i;
  y = figure[t].y_i;
  // p.Plot();
  delayMicroseconds(100);
  analogWrite(2, x);
  analogWrite(3, y);
}