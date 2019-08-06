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
    const int DEPTH_WIDTH_HALF = DEPTH_WIDTH / 2;
    static const int DEPTH_HEIGHT = 424;
    const int DEPTH_HEIGHT_HALF = DEPTH_HEIGHT / 2;
    const float FOV_H = ofDegToRad(70.6);
    const float FOV_V = ofDegToRad(60);
    
    KinectDevice(std::string name);
    virtual void start() { };
    virtual void stop() { };
	virtual bool isRunning() { return false; };
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
    void setKeystone(float &_keystone);
    float getKeystone();
    void setVertCorrection(float &_vertCorrection);
    float getVertCorrection();
    
    void loadKinectRecording(string _filename);
    
    ofTexture &getTexture();
    ofVec3f &getCom();
    void draw();
    void drawSelected();
    
    float convertToRealWorldX(float x, float depth);
    float convertToRealWorldY(float y, float depth);
    
    bool readKinectRecording = false;
    string kinectRecordingFilename = "";
    ofVideoPlayer kinectRecording;
    void setReadKinectRecording(bool _readKinectRecording){readKinectRecording = _readKinectRecording;};
    bool getReadKinectRecording(){return readKinectRecording;};
    ofFbo kinectRecordingFbo;
    ofShader depthShader;
    ofMatrix4x4 projectionFlat;
    ofMatrix4x4 modelviewFlat;
    
protected:
    int minDistance, maxDistance;
    int leftMargin, rightMargin, topMargin, bottomMargin;
    float keystone, vertCorrection;
	virtual float* updateEdgeData() { return NULL; };
	virtual ofVec3f& updateCom() { return ofVec3f();  };
    
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
