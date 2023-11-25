#include "ofApp.h"

void ofApp::setup() {
    ofHideCursor();
    
    latk = Latk("numbers.json");
    
    snd.load("sound.mp3");
    snd.setLoop(true);
    snd.play();
    
    startTimesArray.push_back(0.641);
    startTimesArray.push_back(5.986);
    startTimesArray.push_back(8.053);
    startTimesArray.push_back(11.758);
    startTimesArray.push_back(15.322);
    startTimesArray.push_back(19.241);
    startTimesArray.push_back(23.446);
    startTimesArray.push_back(26.225);
    startTimesArray.push_back(30.573);
    startTimesArray.push_back(33.637);
    startTimesArray.push_back(36.488);
    startTimesArray.push_back(38.982);
    startTimesArray.push_back(45.040);
    startTimesArray.push_back(49.886);
    startTimesArray.push_back(53.734);
    startTimesArray.push_back(57.226);
    startTimesArray.push_back(63.569);
    
    stopTimesArray.push_back(5.487);
    stopTimesArray.push_back(7.340);
    stopTimesArray.push_back(11.046);
    stopTimesArray.push_back(14.538);
    stopTimesArray.push_back(18.244);
    stopTimesArray.push_back(22.876);
    stopTimesArray.push_back(25.299);
    stopTimesArray.push_back(29.646);
    stopTimesArray.push_back(32.996);
    stopTimesArray.push_back(36.060);
    stopTimesArray.push_back(38.412);
    stopTimesArray.push_back(44.403);
    stopTimesArray.push_back(48.817);
    stopTimesArray.push_back(52.451);
    stopTimesArray.push_back(56.442);
    stopTimesArray.push_back(62.357);
    stopTimesArray.push_back(66.918);
    
    for (int i=0; i<startTimesArray.size(); i++) {
        float newTimeDiff = abs(stopTimesArray[currentFrame] - startTimesArray[currentFrame]);
        if (newTimeDiff > largestTimeDiff) largestTimeDiff = newTimeDiff;
        diffTimesArray.push_back(newTimeDiff);
    }
}

void ofApp::update() {
    float pos = snd.getPositionMS() / 1000.0;
    spread += spreadDelta;
    
    if (pos > stopTimesArray[currentFrame]) {
        currentFrame++;
        currentStroke = 0;
        currentPoint = 0;
        spread = spreadOrig;
    }
    
    if (pos > stopTimesArray[int(stopTimesArray.size()) - 1] || currentFrame > int(stopTimesArray.size()) - 1) {
        currentFrame = 0;
        currentStroke = 0;
        currentPoint = 0;
        spread = spreadOrig;
    }
    
    //std:cout << pos << ", " << stopTimesArray[currentFrame] << endl;
}

void ofApp::draw() {
    ofBackground(0);
    ofSetColor(255);
    ofSetLineWidth(5);
    ofScale(ofGetWidth() / 128.0, ofGetHeight() / -128.0);
    ofTranslate(40, -115);
    ofNoFill();
    
    for (int j=0; j<currentStroke + 1; j++) {
        ofBeginShape();
        
        int kLimit = (int) latk.layers[0].frames[currentFrame].strokes[j].points.size();
        if (j == currentStroke) kLimit = currentPoint + 1;

        for (int k=0; k<kLimit; k++) {
            ofVec3f co = latk.layers[0].frames[currentFrame].strokes[j].points[k];
            ofVertex(co.x + ofRandom(-spread, spread), co.y + ofRandom(-spread, spread), 0);
        }
        ofEndShape();
    }
    
    float pointsSize = latk.layers[0].frames[currentFrame].strokes[currentStroke].points.size() - 1;
    float pointStep_f = ofMap(abs(largestTimeDiff - diffTimesArray[currentFrame]), 0.0, largestTimeDiff, pointsSize, 1.0) / 20.0;
    int pointStep = int(pointStep_f);
    if (pointStep < 1) pointStep = 1;
    cout << pointStep_f << ", " << pointStep << endl;
    
    if (currentPoint < pointsSize) {
        currentPoint += pointStep;
        if (currentPoint > pointsSize) currentPoint = pointsSize;
    }
            
    if (currentStroke < int(latk.layers[0].frames[currentFrame].strokes.size()) - 1 && currentPoint >= int(latk.layers[0].frames[currentFrame].strokes[currentStroke].points.size()) - 1) {
        currentStroke++;
        currentPoint = 0;
    }
}
