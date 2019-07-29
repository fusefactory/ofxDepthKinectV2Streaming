//
//  KinectSettings.hpp
//  Apologue2047
//
//  Created by Matteo on 23/07/2019.
//

#ifndef KinectSettings_hpp
#define KinectSettings_hpp

#include <stdio.h>
#include "KinectDevice.h"

class intParam {
public:
    void set(int _d, int _min, int _max){
        d = _d;
        min = _min;
        max = _max;
    }
    
    int d;
    int min;
    int max;
};

class floatParam {
public:
    void set(float _d, float _min, float _max){
        d = _d;
        min = _min;
        max = _max;
    }
    float d;
    float min;
    float max;
};

class KinectSettings {
    
public:
    KinectSettings(){};
    
    intParam minDistance;
    intParam maxDistance;
    intParam leftMargin;
    intParam rightMargin;
    intParam topMargin;
    intParam bottomMargin;
    floatParam keystone;
    floatParam vertCorrection;
};

static KinectSettings getDefaultKinectSettings(){
    KinectSettings kinectSettings;
    kinectSettings.minDistance.set(1, 0, 5000);
    kinectSettings.maxDistance.set(10000, 1, 15000);
    kinectSettings.leftMargin.set(1, 0, KinectDevice::DEPTH_WIDTH);
    kinectSettings.rightMargin.set(1, 0, KinectDevice::DEPTH_WIDTH);
    kinectSettings.topMargin.set(1, 0, KinectDevice::DEPTH_HEIGHT);
    kinectSettings.bottomMargin.set(1, 0, KinectDevice::DEPTH_HEIGHT);
    kinectSettings.keystone.set(0.3, -1.0, 1.0);
    kinectSettings.vertCorrection.set(1.0, -2.0, 2.0);

    return kinectSettings;
}


#endif /* KinectSettings_hpp */
