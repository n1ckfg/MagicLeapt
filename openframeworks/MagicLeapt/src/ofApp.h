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

        struct Timecode {
            float startTime;
            float stopTime;
        };
        
        Timecode timecodeSourceArray[17] = {
            { 0.641, 5.487 },
            { 5.986, 7.340 },
            { 8.053, 11.046 },
            { 11.758, 14.538 },
            { 15.322, 18.244 },
            { 19.241, 22.876 },
            { 23.446, 25.299 },
            { 26.225, 29.646 },
            { 30.573, 32.996 },
            { 33.637, 36.060 },
            { 36.488, 38.412 },
            { 38.982, 44.403 },
            { 45.040, 48.817 },
            { 49.886, 52.451 },
            { 53.734, 56.442 },
            { 57.226, 62.357 },
            { 63.569, 66.918 }
        };
        
        float offsetPercent = 0.8;
    
        vector<Timecode> timecodeArray;
    
};

