#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    
    KinectConfig kinectConfig;
    kinectConfig.serverAddress = "192.168.1.77";
    kinectConfig.port = 4444;
    kinectConfig.minDistance = 500;
    kinectConfig.maxDistance = 5000;
    kinectConfig.leftMargin = 0;
    kinectConfig.rightMargin = 0;
    kinectConfig.topMargin = 0;
    kinectConfig.bottomMargin = 0;
    kinectConfig.vertCorrection = 1;
    kinectConfig.keystone = 0;
    
    kinect = new KinectRemote("kinect", kinectConfig.serverAddress, kinectConfig.port, kinectConfig.vertCorrection, kinectConfig.keystone);
    kinect->setMinDistance(kinectConfig.minDistance);
    kinect->setMaxDistance(kinectConfig.maxDistance);
    kinect->setLeftMargin(kinectConfig.leftMargin);
    kinect->setRightMargin(kinectConfig.rightMargin);
    kinect->setTopMargin(kinectConfig.topMargin);
    kinect->setBottomMargin(kinectConfig.bottomMargin);
    kinect->start();
    
    kinectGui.setup("KINECT", "kinect.xml", 10, 50);
    kinectGui.addGuiComponents(kinect);
    
    kinectGui.loadFromFile(kinectGui.getFilename());
    
    bShowGui = true;
    
    
    vidRecorder.setVideoCodec("prores");
    vidRecorder.setVideoBitrate("2000k");
    recordFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
    recordFboFlip.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
}

//--------------------------------------------------------------
void ofApp::update(){
    kinect->update();
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    recordFbo.getTexture().readToPixels(recordPixels);
    if(bRecording){
        bool success = vidRecorder.addFrame(recordPixels);
        if (!success) {
            ofLogWarning("This frame was not added!");
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    kinect->setAspect(0, 0, KinectDevice::DEPTH_WIDTH, KinectDevice::DEPTH_HEIGHT);
    kinect->draw();
    
    if (bShowGui)
        kinectGui.draw();
    
    
    recordFbo.begin();
    ofClear(0,0,0,255);
    
    ofSetColor(255);
    kinect->draw();
    
//    ofSetColor(255, 0, 0);
//    ofDrawRectangle(0, 0, 300, 300);
    
    recordFbo.end();
    
    //the following 3 rows need to vertical flip of the fbo.. wout you record (and show on screen) your output upside down
//    recordFboFlip.begin();
//    recordFbo.draw(0,recordFbo.getHeight(),recordFbo.getWidth(),-recordFbo.getHeight());
//    recordFboFlip.end();
    
    //need if you want to visualize your output on the screen
    recordFbo.draw(0,0,recordFbo.getWidth(),recordFbo.getHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'g'){
        bShowGui = ! bShowGui;
    }
    else if (key == 's'){
        kinectGui.save();
    }
    
    if(key=='R'){
        bRecording = !bRecording;
        if(bRecording && !vidRecorder.isInitialized()) {
            //insert your path in the following row and your settings 1920x1080 60fps - the last 2 parms are zero because in my case I don't want to record audio..
            ofFilePath f;
            vidRecorder.setup(f.getUserHomeDir() + "/Desktop/grab_"+ofGetTimestampString()+".mov", recordFbo.getWidth(),recordFbo.getHeight(), 60, 0, 0);
            
            //Start recording
            vidRecorder.start();
        }
        else if(!bRecording && vidRecorder.isInitialized()) {
            vidRecorder.setPaused(true);
        }
        else if(bRecording && vidRecorder.isInitialized()) {
            vidRecorder.setPaused(false);
        }
    }
    if(key=='C'){
        bRecording = false;
        vidRecorder.close();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
