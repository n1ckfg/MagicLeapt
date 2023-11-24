#include "ofApp.h"

void ofApp::setup() {
    latk = Latk("untitled.json");

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
}

void ofApp::update() {
    float pos = snd.getPositionMS() / 1000.0;
    if (pos > stopTimesArray[currentFrame]) {
        currentFrame++;
        if (currentFrame >= stopTimesArray.size()) currentFrame = 0;
    }
    std:cout << pos << ", " << stopTimesArray[currentFrame] << endl;
}

void ofApp::draw() {
    ofBackground(0);
    ofSetColor(255);
    ofSetLineWidth(5);
    ofScale(ofGetWidth() / 128.0, ofGetHeight() / -128.0);
    ofTranslate(40, -115);
    ofNoFill();
    for (int i=0; i<latk.layers.size(); i++) {
        for (int j=0; j<latk.layers[i].frames[currentFrame].strokes.size(); j++) {
            ofBeginShape();
            for (int k=0; k<latk.layers[i].frames[currentFrame].strokes[j].points.size(); k++) {
                ofVec3f co = latk.layers[i].frames[currentFrame].strokes[j].points[k];
                //cout << co << endl;
                ofVertex(co.x, co.y, 0);
            }
            ofEndShape();
        }
    }
}
