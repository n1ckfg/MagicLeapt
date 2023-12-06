// cc teddavis.org 2018

import ddf.minim.*; // minim req to gen audio
import xyscope.*;   // import XYscope

XYscope xy;         // create XYscope instance
boolean debugXyScope = false;
boolean clearEveryFrame = true;
boolean isVectrex = false;
int totalPointsCounter = 0;
int totalPointsClearLimit = 100; // It's bad for the Vectrex hardware to clear the screen and not immediately redraw.

void xyScopeSetup() {
  xy = new XYscope(this); // define XYscope instance
  //xy.getMixerInfo(); // lists all audio devices

  if (isVectrex) xy.vectrex(0); // 90 for landscape, 0 for portrait
  
  xy.ellipseDetail(30); // set detail of vertex ellipse

  /*
   If the SPOT-KILLER MOD was applied (z/brightness is always on),
   this auto sets the brightness (from way turned down) when the sketch runs.
   */
  //xy.z("MOTU 3-4"); // use custom 3rd channel audio device
  //xy.zRange(.5, 0);
}

void xyScopeBegin() {
  if (clearEveryFrame || totalPointsCounter > totalPointsClearLimit) {
    xy.clearWaves();
    totalPointsCounter = 0;  
  }
}

void xyScopeEnd() {
  xy.buildWaves(); // build audio from shapes
  if (debugXyScope) xy.drawAll(); // draw all analytics
}
