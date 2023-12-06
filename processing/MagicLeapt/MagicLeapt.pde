// cc teddavis.org 2018

import ddf.minim.*; // minim req to gen audio
import xyscope.*;   // import XYscope
import latkProcessing.*;

Latk latk; 
PVector offset = new PVector(-60, -80);

int currentFrame = 0;
int currentStroke = 0;
int currentPoint = 0;
float pos = 0.0;

float pointReadMultiplier = 1.0;

float spreadOrig = 0.05;
float spreadDelta = 0.001;
float spread = spreadOrig;
boolean doSpread = false;

float[] startTimesArray = { 0.641, 5.986, 8.053, 11.758, 15.322, 19.241, 23.446, 26.225, 30.573, 33.637, 36.488, 38.982, 45.040, 49.886, 53.734, 57.226, 63.569 };
float[] stopTimesArray = { 5.487, 7.340, 11.046, 14.538, 18.244, 22.876, 25.299, 29.646, 32.996, 36.060, 38.412, 44.403, 48.817, 52.451, 56.442, 62.357, 66.918 };
float[] diffTimesArray = new float[startTimesArray.length];
float largestTimeDiff = 0.0;
float randomPositionSpread;
String latkFileName = "sandia.latk";
float translateXorig, translateYorig, translateX, translateY;

void setup() {
  size(512, 512, P2D); 
  
  for (int i=0; i<startTimesArray.length; i++) {
    float newTimeDiff = abs(stopTimesArray[currentFrame] - startTimesArray[currentFrame]);
    if (newTimeDiff > largestTimeDiff) largestTimeDiff = newTimeDiff;
    diffTimesArray[i] = newTimeDiff;
  }
    
  xyScopeSetup();
  soundSetup();

  latk = new Latk(this, latkFileName);  
  latk.normalize();
}

void randomizePosition() {
    translateX = translateXorig + random(-randomPositionSpread, randomPositionSpread);
    translateY = translateYorig + random(-randomPositionSpread, randomPositionSpread);
}

void draw() {
  pos = player.position() / 1000.0;
  
  if (pos > stopTimesArray[currentFrame]) {
    currentFrame++;
    currentStroke = 0;
    currentPoint = 0;
    spread = spreadOrig;
    randomizePosition();
  }
  
  if (pos > stopTimesArray[stopTimesArray.length - 1] || currentFrame > stopTimesArray.length - 1) {
    currentFrame = 0;
    currentStroke = 0;
    currentPoint = 0;
    spread = spreadOrig;
    randomizePosition();
  }

  background(127);
  stroke(255);
  strokeWeight(10);
  fill(255);
   
  xyScopeBegin();   
    
  for (int j=0; j<currentStroke + 1; j++) {  
    xy.beginShape();
    beginShape(LINES);
    
    int kLimit = (int) latk.layers.get(0).frames.get(currentFrame).strokes.get(j).points.size();
    if (j == currentStroke) kLimit = currentPoint + 1;
    
    for (int k=0; k<kLimit; k++) {
      if (doSpread) {
        //offset.x += random(-spread, spread);
        //offset.y += random(-spread, spread);
      }
      
      PVector p = latk.layers.get(0).frames.get(currentFrame).strokes.get(j).points.get(k).co; //.add(offset);
      xy.vertex(p.x, p.y);
      vertex(p.x * 100.0, p.y * 100);      
    }
       
    endShape();
    xy.endShape();
  }

  xyScopeEnd();

  int pointsSize = latk.layers.get(0).frames.get(currentFrame).strokes.get(currentStroke).points.size() - 1;
  float pointStep_f = map(abs(largestTimeDiff - diffTimesArray[currentFrame]), 0.0, largestTimeDiff, pointsSize, 1.0) * pointReadMultiplier;
  int pointStep = int(pointStep_f);
  if (pointStep < 1) pointStep = 1;
  
  if (currentPoint < pointsSize) {
    currentPoint += pointStep;
    if (currentPoint > pointsSize) currentPoint = pointsSize;
  }
  
  if (currentStroke < int(latk.layers.get(0).frames.get(currentFrame).strokes.size()) - 1 && currentPoint >= int(latk.layers.get(0).frames.get(currentFrame).strokes.get(currentStroke).points.size()) - 1) {
    currentStroke++;
    currentPoint = 0;
  }
    
  spread += spreadDelta;  
  
  surface.setTitle(""+frameRate);
}
