#include <Arduino.h>

#include "u_math.h"
#include "hardware.h"
#include "FourierTransform.h"
// Figures
#include "FourierFigure/FusicLogo.h"
#include "FourierFigure/MockLogo.h"
#include "FourierFigure/MonsterLogo.h"

elapsedMillis elapAnimationTimer = 0;
const double ANIMATION_DURATION = 1500;
double animationProgress = 1;

elapsedMicros elapDrawingTimer = 0;
const double DRAWING_DURATION = 150000;
double drawingProgress = 0;

enum{
  FUSIC     = 'A',  fusic     = 'a',
  MOCKMOCK  = 'S',  mockmock  = 's',
  MONSTER   = 'D',  monster   = 'd',
  INIT      = 'Q',  init      = 'q',
};

char protFigure = init;
char nextFigure = init;

FourierTransform FusicLogo(FusicLogo_x,FusicLogo_y);
FourierTransform MockLogo(MockLogo_x,MockLogo_y);
FourierTransform MonsterLogo(MonsterLogo_x,MonsterLogo_y);

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
    elapAnimationTimer = 0;
		nextFigure = Serial.read();
		Serial.println(nextFigure);
	}

  if(elapAnimationTimer >= ANIMATION_DURATION) elapAnimationTimer = ANIMATION_DURATION;
  animationProgress = 0.5*(cos(2*PI*(elapAnimationTimer / ANIMATION_DURATION)) + 1);

  if(elapDrawingTimer > DRAWING_DURATION) elapDrawingTimer = 0;
  drawingProgress = (elapDrawingTimer / DRAWING_DURATION);

  if(elapAnimationTimer>(ANIMATION_DURATION/2)){
    protFigure = nextFigure;
  }

  switch (protFigure){
  case FUSIC:
  case fusic:
    point = FusicLogo.getFigure(drawingProgress);
    // point = zoom(animationProgress,point);
    break;
  case MOCKMOCK:
  case mockmock:
    point = MockLogo.getFigure(drawingProgress);
    // point = roll(animationProgress,point);
    break;
  case MONSTER:
  case monster:
    point = MonsterLogo.getFigure(drawingProgress);
    break;
  case INIT:
  case init:
    point = initial(drawingProgress);
    break;
  default:
    break;
  }

  // plot(point);
  plot(zoom(animationProgress,roll(animationProgress,point)));
}
