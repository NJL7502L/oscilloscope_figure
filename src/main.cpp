#include <Arduino.h>
#include <TimerOne.h>

#include "FourierTransform.h"
// Figures
#include "FourierFigure/FusicLogo.h"
#include "FourierFigure/MockLogo.h"
#include "FourierFigure/MonsterLogo.h"

const int PWM_FRQ = 585937;
const int PWM_RES = 256;

const int PIN_X = 5;
const int PIN_Y = 6;

const float SCROLL_SPEED = 1000;

char incomingByte = 'a';
elapsedMillis elap_scroll = 0;
float scroll = 0;

float point_x;
float point_y;

FourierTransform FusicLogo(FusicLogo_x,FusicLogo_y);
FourierTransform MockLogo(MockLogo_x,MockLogo_y);
FourierTransform MonsterLogo(MonsterLogo_x,MonsterLogo_y);

void flash(){
  static int t = 0;

  switch (incomingByte){
  case 'A':
    scroll = 0;
  case 'a':
    t = ((t<FusicLogo.ARR_LENGTH) ? t+1 : 0);
    point_x = FusicLogo.figure[t].x;
    point_y = FusicLogo.figure[t].y;
    break;
  case 'S':
    scroll = 0;
  case 's':
    t = ((t<MockLogo.ARR_LENGTH) ? t+1 : 0);
    point_x = MockLogo.figure[t].x;
    point_y = MockLogo.figure[t].y;
    break;
  case 'D':
    scroll = 0;
  case 'd':
    t = ((t<MonsterLogo.ARR_LENGTH) ? t+1 : 0);
    point_x = MonsterLogo.figure[t].x;
    point_y = MonsterLogo.figure[t].y;
    break;
  case 'Q':
    scroll = 0;
  case 'q':
    point_x = 0.5;
    point_y = 0.5;
    break;
  default:
    break;
  }

  // if(point_x + scroll < 1){
  //   analogWrite(PIN_X, (point_x + scroll) * PWM_RES);
  // }else{
  //   analogWrite(PIN_X, (point_x + scroll - 1) * PWM_RES);
  // }
  // analogWrite(PIN_Y, point_y * PWM_RES);

  analogWrite(PIN_X, (point_x * scroll + 0.5 + scroll * -0.5) * PWM_RES);
  analogWrite(PIN_Y, (point_y* scroll + 0.5 + scroll * -0.5) * PWM_RES);
}

void setup() {
  analogWriteFrequency(PIN_X,PWM_FRQ);
  analogWriteFrequency(PIN_Y,PWM_FRQ);
  
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

  if(elap_scroll > SCROLL_SPEED) elap_scroll = 0;
  scroll = (elap_scroll / SCROLL_SPEED);

}
