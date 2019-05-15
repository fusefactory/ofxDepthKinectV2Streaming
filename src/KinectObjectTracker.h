//
//  KinectObjectTracker.h
//  Dokk
//
//  Created by Paolo Bonacini on 07/12/16.
//
//

#ifndef KinectObjectTracker_h
#define KinectObjectTracker_h

#include <stdio.h>
#include <vector>
#include "ofMain.h"
#include "KinectDevice.h"
#include "ofxOpenCv.h"

class KinectObjectTracker : public ofThread {
    
public:
    KinectObjectTracker(KinectDevice *kinect);
    virtual void update(int maxBlobs);
    
    virtual void setMinArea(int &area);
    int getMinArea();
    virtual void setMaxArea(int &area);
    int getMaxArea();
    
    virtual void toggleBlobs(bool &value);
    bool showingBlobs();
    void drawBlobs(float x, float y, float width, float height);
    vector<ofxCvBlob> getBlobs();

protected:
    KinectDevice *kinect;
    ofPixels depthPixels;
    ofxCvContourFinder contourFinder;
    
private:
    int objectMinArea = 10, objectMaxArea = 10000;
    
    ofxCvColorImage colorImage;
    ofxCvGrayscaleImage grayImage;
    
    bool showBlobs = true;
    ofFbo fbo;
    
    std::vector<ofVec3f> objectsTracked;
};

#endif /* KinectObjectTracker_h */
