//
//  KinectRemote.h
//  Dokk
//
//  Created by Paolo Bonacini on 02/12/16.
//
//

#ifndef KinectRemote_h
#define KinectRemote_h

#include <stdio.h>
#include <string>
#include "KinectDevice.h"
#include "KinectStreamListener.h"
#include "KinectStreamReceiver.h"

class KinectRemote : public KinectDevice, KinectStreamListener {
    
public:
    KinectRemote(std::string name, std::string address, int port, int vertCorrection = 0, float keystone = 0);
    void newData(char *data) override;
    void start() override;
    void stop() override;
    bool isRunning() override;
    
protected:
    float *updateEdgeData() override;
    ofVec3f &updateCom() override;

private:
    KinectStreamReceiver * receiver;
    float *edgeData;
    ofVec3f com;
    int vertCorrection = 0;
    float keystone = 0;
    
};
#endif /* KinectRemote_h */
