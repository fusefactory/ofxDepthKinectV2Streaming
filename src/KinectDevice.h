//
//  KinectDevice.h
//  Dokk
//
//  Created by Paolo Bonacini on 02/12/16.
//
//

#ifndef KinectDevice_h
#define KinectDevice_h

#include <stdio.h>
#include "ofMain.h"

class KinectDevice {
    
public:
    static const int DEPTH_WIDTH = 512;
    static const int DEPTH_HEIGHT = 424;
    const float FOV_H = ofDegToRad(70.6);
    const float FOV_V = ofDegToRad(60);
    
    KinectDevice(std::string name);
    virtual void start() { };
    virtual void stop() { };
    virtual bool isRunning() { };
    void update();
    std::string getName();
    void setAspect(float x, float y, float width, float height);
    
    
    void connectRelease();
    void setMinDistance(int &distance);
    int getMinDistance();
    void setMaxDistance(int &distance);
    int getMaxDistance();
    void setLeftMargin(int &margin);
    int getLeftMargin();
    void setRightMargin(int &margin);
    int getRightMargin();
    void setTopMargin(int &margin);
    int getTopMargin();
    void setBottomMargin(int &margin);
    int getBottomMargin();
    
    ofTexture &getTexture();
    ofVec3f &getCom();
    void draw();
    void drawSelected();
    
    float convertToRealWorldX(float x, float depth);
    float convertToRealWorldY(float y, float depth);
    
protected:
    int minDistance, maxDistance;
    int leftMargin, rightMargin, topMargin, bottomMargin;
    virtual float *updateEdgeData() { };
    virtual ofVec3f &updateCom() { };
    
private:
    std::string name, fullName;
    ofTexture texture;
    float *lastData;
    ofVec3f com;
    int movement = 0;
    float x, y, width, height;
    float XtoZ, YtoZ;
};

#endif /* KinectDevice_h */
