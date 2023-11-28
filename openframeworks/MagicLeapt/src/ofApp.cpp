#include "ofApp.h"

using namespace cv;
using namespace ofxCv;

void ofApp::setup() {
    settings.loadFile("settings.xml");
    ofHideCursor();
    
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    
    playLatk = (bool) settings.getValue("settings:play_latk", 1);
    fboRotation = settings.getValue("settings:fbo_rotation", 180);

    if (playLatk) {
        latkFileName = settings.getValue("settings:latk_file_name", "untitled.json");
        soundFileName = settings.getValue("settings:sound_file_name", "sound.mp3");
        latk = Latk(latkFileName);
        
        snd.load(soundFileName);
        snd.setLoop(true);
        snd.play();
    }
    
    startTimesArray.push_back(0.641); // 1. This place is a message, and part of a system of messages.
    startTimesArray.push_back(5.986); // 2. Pay attention to it!
    startTimesArray.push_back(8.053); // 3. Sending this message was important to us.
    startTimesArray.push_back(11.758); // 4. We considered ourselves to be a powerful culture.
    startTimesArray.push_back(15.322); // 5. This place is not a place of honor.
    startTimesArray.push_back(19.241); // 6. No highly esteemed deed is commemorated here.
    startTimesArray.push_back(23.446); // 7. Nothing valued is here.
    startTimesArray.push_back(26.225); // 8. What is here was dangerous and repulsive to us.
    startTimesArray.push_back(30.573); // 9. This message is a warning about danger.
    startTimesArray.push_back(33.637); // 10. The danger is in a particular location.
    startTimesArray.push_back(36.488); // 11. It increases towards a center.
    startTimesArray.push_back(38.982); // 12. The center of danger is here, of a particular size and shape, and below us.
    startTimesArray.push_back(45.040); // 13. The danger is still present, in your time, as it was in ours.
    startTimesArray.push_back(49.886); // 14. The danger is to the body, and it can kill.
    startTimesArray.push_back(53.734); // 15. The form of the danger is an emanation of energy.
    startTimesArray.push_back(57.226); // 16. The danger is unleashed only if you substantially disturb this place physically.
    startTimesArray.push_back(63.569); // 17. This place is best shunned and left uninhabited.
    
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
    
    camW = settings.getValue("settings:cam_width", 640);
    camH = settings.getValue("settings:cam_height", 480);
    camFps = settings.getValue("settings:cam_fps", 40); // RPi cam can do this

#ifdef TARGET_RASPBERRY_PI
    camRotation = settings.getValue("settings:cam_rotation", 0);
    camSharpness = settings.getValue("settings:sharpness", 0);
    camContrast = settings.getValue("settings:contrast", 0);
    camBrightness = settings.getValue("settings:brightness", 50);
    camIso = settings.getValue("settings:iso", 300);
    camExposureMode = settings.getValue("settings:exposure_mode", 0);
    camExposureCompensation = settings.getValue("settings:exposure_compensation", 0);
    camShutterSpeed = settings.getValue("settings:shutter_speed", 0);
    
    cam.setup(camW, camH, camFps, false); // color/gray;
    
    cam.setRotation(camRotation);
    cam.setSharpness(camSharpness);
    cam.setContrast(camContrast);
    cam.setBrightness(camBrightness);
    cam.setISO(camIso);
    cam.setExposureMode((MMAL_PARAM_EXPOSUREMODE_T) camExposureMode);
    cam.setExposureCompensation(camExposureCompensation);
    cam.setShutterSpeed(camShutterSpeed);
#else
    vector<ofVideoDevice> devices = vidGrabber.listDevices();
    
    for(size_t i = 0; i < devices.size(); i++){
        if(devices[i].bAvailable){
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }else{
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }
    
    videoDevice = settings.getValue("settings:video_device", 0);
    vidGrabber.setDeviceID(videoDevice);
    vidGrabber.setDesiredFrameRate(camFps);
    vidGrabber.initGrabber(camW, camH);
#endif
    
    contourLineWidth = settings.getValue("settings:contour_line_width", 10);
    lineWidth = settings.getValue("settings:line_width", 10);
    alphaVal = settings.getValue("settings:alpha_val", 255);
    contourSlices = settings.getValue("settings:contour_slices", 10);
    
    contourAlpha = settings.getValue("settings:contour_alpha", 127);
    pointReadMultiplier = settings.getValue("settings:point_read_multiplier", 1.0);
    translateXorig = settings.getValue("settings:translate_x", 40.0);
    translateYorig = settings.getValue("settings:translate_y", -115.0);
    randomPositionSpread = settings.getValue("settings:random_position_spread", 10.0);
       
    contourMinAreaRadius = settings.getValue("settings:contour_min_radius", 10.0);
    contourMaxAreaRadius = settings.getValue("settings:contour_max_radius", 150.0);
    contourFinder.setMinAreaRadius(contourMinAreaRadius);
    contourFinder.setMaxAreaRadius(contourMaxAreaRadius);
}

void ofApp::randomizePosition() {
    translateX = translateXorig + ofRandom(-randomPositionSpread, randomPositionSpread);
    translateY = translateYorig + ofRandom(-randomPositionSpread, randomPositionSpread);
}

void ofApp::update() {
    if (playLatk) {
        float pos = snd.getPositionMS() / 1000.0;
        //spread += spreadDelta;
        
        if (pos > stopTimesArray[currentFrame]) {
            currentFrame++;
            currentStroke = 0;
            currentPoint = 0;
            spread = spreadOrig;
            randomizePosition();
        }
        
        if (pos > stopTimesArray[int(stopTimesArray.size()) - 1] || currentFrame > int(stopTimesArray.size()) - 1) {
            currentFrame = 0;
            currentStroke = 0;
            currentPoint = 0;
            spread = spreadOrig;
            randomizePosition();
        }
    }

#ifdef TARGET_RASPBERRY_PI
    frame = cam.grab();
#else
    vidGrabber.update();
    if (vidGrabber.isFrameNew()) {
        frame = toCv(vidGrabber.getPixelsRef());
    }
#endif
}

void ofApp::draw() {
    fbo.begin();
    ofBackground(0);

    if (!frame.empty()) {
        //threshold(frame, frameProcessed, thresholdValue, 255, 0);
        //drawMat(frameProcessed, 0, 0, fbo.getWidth(), fbo.getHeight());
        
        int contourCounter = 0;
        //unsigned char * pixels = gray.getPixels().getData();
        //int gw = gray.getWidth();
        
        for (int h=0; h<255; h += int(255/contourSlices)) {
            contourFinder.setThreshold(h);
            contourFinder.findContours(frame);
            //contourFinder.draw();
            
            int n = contourFinder.size();
            for (int h = 0; h < n; h++) {
                ofPolyline line = contourFinder.getPolyline(h);
                vector<glm::vec3> cvPoints = line.getVertices();
                
                //int index = cvPoints.size() / 2;
                //int x = int(cvPoints[index].x);
                //int y = int(cvPoints[index].y);
                //ofColor col = pixels[x + y * gw];
                
                ofMesh mesh;
                mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
                
                float widthSmooth = 10;
                float angleSmooth;
                
                int cvPointsSize = int(cvPoints.size());
                for (int i = 0; i < cvPointsSize; i++) {
                    int me_m_one = i - 1;
                    int me_p_one = i + 1;
                    if (me_m_one < 0) me_m_one = 0;
                    if (me_p_one == cvPointsSize) me_p_one = cvPointsSize - 1;
                    
                    ofPoint diff = cvPoints[me_p_one] - cvPoints[me_m_one];
                    float angle = atan2(diff.y, diff.x);
                    
                    if (i == 0) {
                        angleSmooth = angle;
                    } else {
                        angleSmooth = ofLerpDegrees(angleSmooth, angle, 1.0);
                    }
                    
                    float dist = diff.length();
                    
                    float w = ofMap(dist, 0, 20, contourLineWidth, 2, true); //40, 2, true);
                    
                    widthSmooth = 0.9f * widthSmooth + 0.1f * w;
                    
                    ofPoint offset;
                    offset.x = cos(angleSmooth + PI/2) * widthSmooth;
                    offset.y = sin(angleSmooth + PI/2) * widthSmooth;
                    
                    float frW = frame.size().width;
                    float fbW = fbo.getWidth();
                    float frH = frame.size().height;
                    float fbH = fbo.getHeight();
                    if (frW != fbW || frH != fbH) {
                        cvPoints[i].x = (cvPoints[i].x / frW) * fbW;
                        cvPoints[i].y = (cvPoints[i].y / frH) * fbH;
                    }
                    mesh.addVertex(cvPoints[i] + offset);
                    mesh.addVertex(cvPoints[i] - offset);
                }
                
                //ofSetColor(col, alphaVal);
                ofSetColor(255, contourAlpha);
                mesh.draw();
                //if (drawWireframe) {
                    //ofSetColor(col);
                    //mesh.drawWireframe();
                //}
                
                contourCounter++;
            }
        }
    }
    
    // latk lines
    if (playLatk) {
        ofSetColor(255, alphaVal);
        ofPushMatrix();
        ofSetLineWidth(lineWidth);
        ofScale(ofGetWidth() / 128.0, ofGetHeight() / -128.0);
        ofTranslate(translateX, translateY);
        ofNoFill();
        
        for (int j=0; j<currentStroke + 1; j++) {
            ofMesh mesh;
            mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
            
            float widthSmooth = 1;
            float angleSmooth;
            
            int kLimit = (int) latk.layers[0].frames[currentFrame].strokes[j].points.size();
            if (j == currentStroke) kLimit = currentPoint + 1;
            
            /*
             for (int k=0; k<kLimit; k++) {
                ofVec3f co = latk.layers[0].frames[currentFrame].strokes[j].points[k];
                if (doSpread) {
                    ofVertex(co.x + ofRandom(-spread, spread), co.y + ofRandom(-spread, spread), 0);
                } else {
                    ofVertex(co.x, co.y, 0);
                }
            }
             */
            for (int k=0; k<kLimit; k++) {
                int me_m_one = k - 1;
                int me_p_one = k + 1;
                if (me_m_one < 0) me_m_one = 0;
                if (me_p_one == kLimit) me_p_one = kLimit - 1;
                
                ofPoint diff = latk.layers[0].frames[currentFrame].strokes[j].points[me_p_one] - latk.layers[0].frames[currentFrame].strokes[j].points[me_m_one];
                float angle = atan2(diff.y, diff.x);
                
                if (k == 0) {
                    angleSmooth = angle;
                } else {
                    angleSmooth = ofLerpDegrees(angleSmooth, angle, 1.0);
                }
                
                float dist = diff.length();
                
                float w = ofMap(dist, 0, 20, lineWidth, 2, true); //40, 2, true);
                
                widthSmooth = 0.2f * widthSmooth + 0.1f * w;
                
                ofPoint offset;
                offset.x = cos(angleSmooth + PI/2) * widthSmooth;
                offset.y = sin(angleSmooth + PI/2) * widthSmooth;
                
                mesh.addVertex(latk.layers[0].frames[currentFrame].strokes[j].points[k] + offset);
                mesh.addVertex(latk.layers[0].frames[currentFrame].strokes[j].points[k] - offset);
            }
            //ofSetColor(col, alphaVal);
            ofSetColor(255, alphaVal);
            mesh.draw();
        }
        ofPopMatrix();
    }
    
    fbo.end();
        
    float width = fbo.getWidth();
    float height = fbo.getHeight();
    ofTranslate(width / 2, height / 2);
    ofRotateDeg(fboRotation);
    fbo.draw(-width / 2, -height / 2);
    
    if (playLatk) {
        float pointsSize = latk.layers[0].frames[currentFrame].strokes[currentStroke].points.size() - 1;
        float pointStep_f = ofMap(abs(largestTimeDiff - diffTimesArray[currentFrame]), 0.0, largestTimeDiff, pointsSize, 1.0) * pointReadMultiplier;
        int pointStep = int(pointStep_f);
        if (pointStep < 1) pointStep = 1;
        //cout << pointStep_f << ", " << pointStep << endl;
        
        if (currentPoint < pointsSize) {
            currentPoint += pointStep;
            if (currentPoint > pointsSize) currentPoint = pointsSize;
        }
        
        if (currentStroke < int(latk.layers[0].frames[currentFrame].strokes.size()) - 1 && currentPoint >= int(latk.layers[0].frames[currentFrame].strokes[currentStroke].points.size()) - 1) {
            currentStroke++;
            currentPoint = 0;
        }
    }
}
