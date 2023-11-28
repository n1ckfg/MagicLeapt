#pragma once

#include "ofMain.h"
#include "ofxLatk.h"
#include "ofxCv.h"

#ifdef TARGET_RASPBERRY_PI
#include "ofxCvPiCam.h"
#endif

#include "ofxXmlSettings.h"

class ofApp : public ofBaseApp {
    
    public:
        void setup();
        void update();
        void draw();
        void randomizePosition();
        
        ofxXmlSettings settings;
        
        ofSoundPlayer snd;
        Latk latk;
        
        int currentFrame = 0;
        int currentStroke = 0;
        int currentPoint = 0;
        
        float pointReadMultiplier = 1.0;
        
        float spreadOrig = 0.05;
        float spreadDelta = 0.001;
        float spread = spreadOrig;
        bool doSpread = false;
    
        vector<float> startTimesArray;
        vector<float> stopTimesArray;
        vector<float> diffTimesArray;
        float largestTimeDiff = 0.0;
        float randomPositionSpread;
        string latkFileName = "untitled.json";
        string soundFileName = "sound.mp3";
        float translateXorig, translateYorig, translateX, translateY;
        ofFbo fbo;

        cv::Mat frame, frameProcessed;

#ifdef TARGET_RASPBERRY_PI
        ofxCvPiCam cam;
        
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
#else
        ofVideoGrabber vidGrabber;
        int videoDevice = 0;
#endif
        
        int thresholdValue; // default 127
        int videoAlpha = 127;

        int alphaVal;
        float lineWidth;
        bool drawWireframe;
        ofxCv::ContourFinder contourFinder;
        float contourThreshold;  // default 127
        float contourMinAreaRadius; // default 10
        float contourMaxAreaRadius; // default 150
        int contourSlices; // default 20
        ofxCv::TrackingColorMode trackingColorMode; // RGB, HSV, H, HS; default RGB
    
        bool playLatk = true;
        float fboRotation = 180;
    
        int camW, camH, camFps;
};


