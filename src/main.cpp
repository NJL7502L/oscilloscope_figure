#include <Arduino.h>
#include <TimerOne.h>

#include "u_math.h"
#include "hardware.h"
#include "FourierTransform.h"
// Figures
#include "FourierFigure/FusicLogo.h"
#include "FourierFigure/MockLogo.h"
#include "FourierFigure/MonsterLogo.h"

const float ANIMATION_DURATION = 1000;

char incomingByte = 'a';
elapsedMillis elap_timer = 0;
float animationProgress = 0;

FourierTransform FusicLogo(FusicLogo_x,FusicLogo_y);
FourierTransform MockLogo(MockLogo_x,MockLogo_y);
FourierTransform MonsterLogo(MonsterLogo_x,MonsterLogo_y);

void flash(){
  static int t = 0;

  switch (incomingByte){
  case 'A':
    animationProgress = 0;
  case 'a':
    t = ((t<FusicLogo.ARR_LENGTH) ? t+1 : 0);
    point = FusicLogo.figure[t];
    break;
  case 'S':
    animationProgress = 0;
  case 's':
    t = ((t<MockLogo.ARR_LENGTH) ? t+1 : 0);
    point = MockLogo.figure[t];
    break;
  case 'D':
    animationProgress = 0;
  case 'd':
    t = ((t<MonsterLogo.ARR_LENGTH) ? t+1 : 0);
    point = MonsterLogo.figure[t];
    break;
  case 'Q':
    animationProgress = 0;
  case 'q':
    point.x = 0.5;
    point.y = 0.5;
    break;
  default:
    break;
  }

  // if(point_x + animationProgress < 1){
  //   analogWrite(PIN_X, (point_x + animationProgress) * PWM_RES);
  // }else{
  //   analogWrite(PIN_X, (point_x + animationProgress - 1) * PWM_RES);
  // }
  // analogWrite(PIN_Y, point_y * PWM_RES);
  plot(zoom(animationProgress,roll(animationProgress,point)));
}



void setup() {
  pinInit();

  Serial.begin(115200);

  FusicLogo.p = "Fusic";
  FusicLogo.aspect_ratio(1,1);
  FusicLogo.store_parameter(0,200,10000);

  MockLogo.p = "mockmock";
  MockLogo.aspect_ratio(22,14);
  MockLogo.store_parameter(0,200,10000);

  MonsterLogo.p = "Monster";
  MonsterLogo.aspect_ratio(10.5,15);
  MonsterLogo.store_parameter(0,200,10000);

  Timer1.initialize(10);
  Timer1.attachInterrupt(flash);
}

void loop() {
	if (Serial.available() > 0) {
		incomingByte = Serial.read();
		Serial.println(incomingByte);
	}

  if(elap_timer > ANIMATION_DURATION) elap_timer = 0;
  animationProgress = (elap_timer / ANIMATION_DURATION);

}
