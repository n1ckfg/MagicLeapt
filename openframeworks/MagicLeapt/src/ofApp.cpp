#include "ofApp.h"

void ofApp::setup() {
    snd.load("sound.mp3");
    snd.setLoop(true);
    snd.play();
    
    int length = sizeof(timecodeSourceArray) / sizeof(Timecode);

    for (int i=0; i<length; i++) {
        Timecode t;
        t.startTime = timecodeSourceArray[i].startTime;
        t.stopTime = timecodeSourceArray[i].stopTime * offsetPercent;
        timecodeArray.push_back(t);
    }
}

void ofApp::update() {
    std:cout << snd.getPosition() << ", " << snd.getPositionMS() << endl;
}

void ofApp::draw() {

}
