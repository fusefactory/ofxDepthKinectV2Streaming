//
//  KinectStreamReceiver.h
//  Dokk
//
//  Created by Paolo Bonacini on 25/11/16.
//
//

#ifndef KinectStreamReceiver_h
#define KinectStreamReceiver_h

#include <stdio.h>
#include <vector>
#include "ofMain.h"
#include "ofxTCPClient.h"
#include "KinectStreamListener.h"

class KinectStreamReceiver : public ofThread {
    
public:
    KinectStreamReceiver(std::string address, int port);
    void start();
    void stop();
    bool isRunning();
    void addListener(KinectStreamListener *listener);
    
private:
    std::string address;
    int port;
    int connectTime;
    int deltaTime;
    ofxTCPClient tcpClient;
    void threadedFunction();
    void readBytes(char *buffer, unsigned int length);
    char *decompress(char *compressedBytes, unsigned int length);
    std::vector<KinectStreamListener *> listeners;
};
#endif /* KinectStreamReceiver_h */
