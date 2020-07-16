#include <Arduino.h>

#include "u_math.h"
#include "hardware.h"
#include "FourierTransform.h"
// Figures
#include "FourierFigure/FusicLogo.h"
#include "FourierFigure/MockLogo.h"
#include "FourierFigure/MonsterLogo.h"

elapsedMillis elapAnimationTimer = 0;
const double ANIMATION_DURATION = 500;
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

FourierTransform::CarCoorFunction fugireFusic[] = {
  {FusicLogo_x},
  {FusicLogo_y}
};
FourierTransform FusicLogo(fugireFusic);

// FourierTransform::func_ptr_d mock_x[] = {MockLogo_x};
// FourierTransform::func_ptr_d mock_y[] = {MockLogo_y};
// FourierTransform MockLogo(fugireFusic);

// FourierTransform::func_ptr_d mos_x[] = {MonsterLogo_x};
// FourierTransform::func_ptr_d mos_y[] = {MonsterLogo_y};
// FourierTransform MonsterLogo(fugireFusic);

void setup() {
  pinInit();

  Serial.begin(115200);
  
  digitalWrite(LED_BUILTIN,HIGH);
  // FusicLogo.return_x[]= {FusicLogo_x};
  FusicLogo.p = "Fusic";
  FusicLogo.aspect_ratio({1,1});
  FusicLogo.store_parameter(0,200,5000);

  digitalWrite(LED_BUILTIN,LOW);

  // MockLogo.p = "mockmock";
  // MockLogo.aspect_ratio({22,14});
  // MockLogo.store_parameter(0,200,5000);

  // digitalWrite(LED_BUILTIN,HIGH);

  // MonsterLogo.p = "Monster";
  // MonsterLogo.aspect_ratio({10.5,15});
  // MonsterLogo.store_parameter(0,200,5000);

  digitalWrite(LED_BUILTIN,LOW);

  digitalWrite(LED_BUILTIN,HIGH);
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
    // point = MockLogo.getFigure(drawingProgress);
    // point = roll(animationProgress,point);
    break;
  case MONSTER:
  case monster:
    // point = MonsterLogo.getFigure(drawingProgress);
    break;
  case INIT:
  case init:
    point = initial(drawingProgress);
    break;
  default:
    break;
  }

  // plot(point);
  //roll(animationProgress,point)
  plot(zoom(animationProgress,point));
}
