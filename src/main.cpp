#include <Arduino.h>

#include "u_math.h"
#include "hardware.h"
#include "FourierTransform.h"
// Figures
#include "FourierFigure/FusicLogo.h"
#include "FourierFigure/MockLogo.h"
#include "FourierFigure/MonsterLogo.h"
#include "FourierFigure/Title.h"
#include "FourierFigure/Nail.h"

elapsedMillis elapAnimationTimer = 0;
const double ANIMATION_DURATION = 1500;
double animationProgress = 1;

elapsedMicros elapDrawingTimer = 0;
const double DRAWING_DURATION = 75000;//150000;
double drawingProgress = 0;

enum{
  fusic     = 'a',
  mockmock  = 's',
  monster   = 'd',
  title     = 'f',
  nail      = 'g',
  init      = 'q',
};

char protFigure = init;
char nextFigure = init;

FourierTransform FusicLogo(FusicLogo_x,FusicLogo_y);
FourierTransform MockLogo(MockLogo_x,MockLogo_y);
FourierTransform MonsterLogo(MonsterLogo_x,MonsterLogo_y);
FourierTransform Title(Title_x,Title_y);
FourierTransform Nail(Nail_x,Nail_y);

void setup() {
  pinInit();

  Serial.begin(115200);

  FusicLogo.p = "Fusic";
  FusicLogo.aspect_ratio(1,1);
  FusicLogo.store_parameter(0,100,5000);

  MockLogo.p = "mockmock";
  MockLogo.aspect_ratio(22,14);
  MockLogo.store_parameter(0,200,5000);

  MonsterLogo.p = "Monster";
  MonsterLogo.aspect_ratio(10.5,15);
  MonsterLogo.store_parameter(0,200,5000);

  Title.p = "Title";
  Title.aspect_ratio(35,13);
  Title.store_parameter(0,50,5000);

  Nail.p = "Nail";
  Nail.aspect_ratio(1,1);
  Nail.store_parameter(0,50,5000);
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
  case fusic:
    point = FusicLogo.getFigure(drawingProgress);
    // point = zoom(animationProgress,point);
    break;
  case mockmock:
    point = MockLogo.getFigure(drawingProgress);
    // point = roll(animationProgress,point);
    break;
  case monster:
    point = MonsterLogo.getFigure(drawingProgress);
    break;
  case title:
    point = Title.getFigure(drawingProgress);
    break;
  case nail:
    point = Nail.getFigure(drawingProgress);
    break;
  case init:
    point = initial(drawingProgress);
    break;
  default:
    break;
  }

  // plot(point);
  plot(zoom(animationProgress,roll(animationProgress,point)));
}
