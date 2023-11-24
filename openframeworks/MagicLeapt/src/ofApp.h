#pragma once

#include "ofMain.h"
#include "ofxLatk.h"

class ofApp : public ofBaseApp {
    
    public:
        void setup();
        void update();
        void draw();

        ofSoundPlayer snd;
        Latk latk;
        
        int currentFrame = 0;
        int currentPoint = 0;
        float offsetPercent = 0.8;
        
        vector<float> startTimesArray;
        vector<float> stopTimesArray;

};

