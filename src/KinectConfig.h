//
//  Header.h
//  Dokk
//
//  Created by Paolo Bonacini on 07/12/16.
//
//

#ifndef KinectConfig_h
#define KinectConfig_h

#include <stdio.h>
#include <string>

class KinectConfig {
    
public:
    std::string serverAddress;
    int port;
    int minDistance, maxDistance;
    int leftMargin, rightMargin, topMargin, bottomMargin;
    ofVec2f position;
    ofVec2f scale;
    int vertCorrection;
    float keystone;
};

#endif /* KinectConfig_h */
