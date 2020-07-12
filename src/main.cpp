#include <Arduino.h>
#include <TimerOne.h>

#include "FourierTransform.h"
// Figures
#include "FourierFigure/FusicLogo.h"
#include "FourierFigure/MockLogo.h"
#include "FourierFigure/MonsterLogo.h"

const int PWM_FRQ = 585937;
const int PWM_RES = 256;

float point_x;
float point_y;

FourierTransform FusicLogo(FusicLogo_x,FusicLogo_y);
FourierTransform MockLogo(MockLogo_x,MockLogo_y);
FourierTransform MonsterLogo(MonsterLogo_x,MonsterLogo_y);

void flash(){
  static int t = 0;
  // if(t<FusicLogo.ARR_LENGTH){
  //   t++;
  // }else{
  //   t = 0;
  // }

  // point_x = FusicLogo.figure[t].x;
  // point_y = FusicLogo.figure[t].y;

  // if(t<MockLogo.ARR_LENGTH){
  //   t++;
  // }else{
  //   t = 0;
  // }

  // point_x = MockLogo.figure[t].x;
  // point_y = MockLogo.figure[t].y;

  if(t<MonsterLogo.ARR_LENGTH){
    t++;
  }else{
    t = 0;
  }

  point_x = MonsterLogo.figure[t].x;
  point_y = MonsterLogo.figure[t].y;

  analogWrite(2, point_x * PWM_RES);
  analogWrite(3, point_y * PWM_RES);
}

void setup() {
  analogWriteFrequency(2,PWM_FRQ);
  analogWriteFrequency(3,PWM_FRQ);
  
  Serial.begin(115200);

  FusicLogo.p = "Fusic";
  FusicLogo.aspect_ratio(1,1);
  FusicLogo.store_parameter(0,200,30000);

  MockLogo.p = "mockmock";
  MockLogo.aspect_ratio(22,14);
  MockLogo.store_parameter(0,200,30000);

  MonsterLogo.p = "Monster";
  MonsterLogo.aspect_ratio(10.5,15);
  MonsterLogo.store_parameter(0,200,30000);

  Timer1.initialize(10);
  Timer1.attachInterrupt(flash);
}

void loop() {

}
