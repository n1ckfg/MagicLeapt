#include "ofApp.h"

void ofApp::setup() {
    snd.load("sound.mp3");
    snd.setLoop(true);
    snd.play();
}

void ofApp::update() {
    std:cout << snd.getPosition() << ", " << snd.getPositionMS() << endl;
}

void ofApp::draw() {

}
