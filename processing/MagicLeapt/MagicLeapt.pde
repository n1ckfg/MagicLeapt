// cc teddavis.org 2018

import ddf.minim.*; // minim req to gen audio
import xyscope.*;   // import XYscope
import latkProcessing.*;

Latk latk; 
PVector offset = new PVector(40, -100);
int skipPoints = 1;

void setup() {
  size(512, 512, P2D); 
  
  xyScopeSetup();

  latk = new Latk(this, "sandia.latk");  
  latk.normalize();

  for (int i=0; i<latk.layers.size(); i++) {
    LatkLayer layer = latk.layers.get(i);
    for (int j=0; j<layer.frames.size(); j++) {
      LatkFrame frame = layer.frames.get(j);
      for (int k=0; k<frame.strokes.size(); k++) {
        LatkStroke stroke = frame.strokes.get(k);
        
        for (int l=0; l<stroke.points.size(); l++) {
          PVector point = stroke.s.getVertex(l);
          point.x = abs(point.x * width) + offset.x;
          point.y = (height - abs(point.y * height)) + offset.y;
          stroke.s.setVertex(l, point);
        }
      }
    }
  }
}

void draw() {
  background(255);
  
  latk.run();
  
  xyScopeBegin();
  
  println(latk.layers.get(0).currentFrame);
  for (int i=0; i<latk.layers.size(); i++) {
    LatkLayer layer = latk.layers.get(i);
    LatkFrame frame = layer.frames.get(layer.currentFrame);
    for (int j=0; j<frame.strokes.size(); j++) {
      LatkStroke stroke = frame.strokes.get(j);
      
      xy.beginShape();
      for (int k=0; k<stroke.points.size(); k+=skipPoints) {
        PVector point = stroke.s.getVertex(k);
        xy.vertex(point.x, point.y);
      }
      xy.endShape();
    }
  }

  xyScopeEnd();

  surface.setTitle(""+frameRate);
}
