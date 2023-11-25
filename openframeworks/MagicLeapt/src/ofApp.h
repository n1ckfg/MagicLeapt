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
        int currentStroke = 0;
        int currentPoint = 0;
        
        float minPointStep = 0.1;
        float maxPointStep = 0.5;
    
        float spreadOrig = 0.05;
        float spreadDelta = 0.0005;
        float spread = spreadOrig;

        vector<float> startTimesArray;
        vector<float> stopTimesArray;

};

