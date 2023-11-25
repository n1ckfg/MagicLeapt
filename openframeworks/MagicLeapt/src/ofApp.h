#pragma once

#include "ofMain.h"
#include "ofxLatk.h"
#include "ofxCv.h"
#include "ofxCvPiCam.h"
#include "ofxXmlSettings.h"

class ofApp : public ofBaseApp {
    
    public:
        void setup();
        void update();
        void draw();
        
        ofxXmlSettings settings;

        ofSoundPlayer snd;
        Latk latk;
        
        int currentFrame = 0;
        int currentStroke = 0;
        int currentPoint = 0;
        
        float minPointStep = 0.1;
        float maxPointStep = 0.5;
    
        float spreadOrig = 0.05;
        float spreadDelta = 0.001;
        float spread = spreadOrig;

        vector<float> startTimesArray;
        vector<float> stopTimesArray;
        vector<float> diffTimesArray;
        float largestTimeDiff = 0.0;

        ofFbo fbo;

        //ofVideoGrabber vidGrabber;
        ofxCvPiCam cam;
        cv::Mat frame, frameProcessed;

        // for more camera settings, see:
        // https://github.com/orgicus/ofxCvPiCam/blob/master/example-ofxCvPiCam-allSettings/src/testApp.cpp
        int camRotation = 180;        
        int camShutterSpeed = 100000; // 0 to 330000 in microseconds, default 0
        int camSharpness = 50; // -100 to 100, default 0
        int camContrast = 0; // -100 to 100, default 0
        int camBrightness = 55; // 0 to 100, default 50
        int camIso = 800; // 100 to 800, default 300
        int camExposureCompensation = 0; // -10 to 10, default 0;
        // 0 off, 1 auto, 2 night, 3 night preview, 4 backlight, 5 spotlight, 6 sports, 7, snow, 8 beach, 9 very long, 10 fixed fps, 11 antishake, 12 fireworks, 13 max
        int camExposureMode = 0; // 0 to 13, default 0
 
        int thresholdValue; // default 127
        int videoAlpha = 127;
};


