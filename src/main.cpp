#include <Arduino.h>

#include "u_math.h"
#include "hardware.h"
#include "FourierTransform.h"
// Figures
#include "FourierFigure/FusicLogo.h"
#include "FourierFigure/MockLogo.h"
#include "FourierFigure/MonsterLogo.h"

elapsedMillis elapAnimationTimer = 0;
const double ANIMATION_DURATION = 1000;
double animationProgress = 1;

elapsedMicros elapDrawingTimer = 0;
const double DRAWING_DURATION = 150000;
double drawingProgress = 0;

char incomingByte = 'a';

FourierTransform FusicLogo(FusicLogo_x,FusicLogo_y);
FourierTransform MockLogo(MockLogo_x,MockLogo_y);
FourierTransform MonsterLogo(MonsterLogo_x,MonsterLogo_y);

enum{
  FUSIC     = 'A',  fusic     = 'a',
  MOCKMOCK  = 'S',  mockmock  = 's',
  MONSTER   = 'D',  monster   = 'd',
  STOP      = 'Q',  stop      = 'q',
};

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
}

void loop() {
	if (Serial.available() > 0) {
		incomingByte = Serial.read();
		Serial.println(incomingByte);
	}

  if(elapAnimationTimer > ANIMATION_DURATION) elapAnimationTimer = 0;
  animationProgress = (elapAnimationTimer / ANIMATION_DURATION);

  if(elapDrawingTimer > DRAWING_DURATION) elapDrawingTimer = 0;
  drawingProgress = (elapDrawingTimer / DRAWING_DURATION);

  switch (incomingByte){
  case FUSIC:
  case fusic:
    point = FusicLogo.getFigure(drawingProgress);
    break;
  case MOCKMOCK:
  case mockmock:
    point = MockLogo.getFigure(drawingProgress);
    break;
  case MONSTER:
  case monster:
    point = MonsterLogo.getFigure(drawingProgress);
    break;
  case STOP:
  case stop:
    point = initial(drawingProgress);
    break;
  default:
    break;
  }
  if((incomingByte>= 'A') && (incomingByte<='Z')) animationProgress = 1;

  plot(zoom(animationProgress,roll(animationProgress,point)));
}
