//
//  KinectRemote.cpp
//  Dokk
//
//  Created by Paolo Bonacini on 02/12/16.
//
//

#include "KinectRemote.h"
#define _USE_MATH_DEFINES
#include <math.h>

KinectRemote::KinectRemote(std::string name, std::string address, int port, unsigned int bytesPerPixel) : KinectDevice(name, bytesPerPixel) {
    edgeData = new float[int(DEPTH_WIDTH * DEPTH_HEIGHT * 3)]; // rgb
    
    receiver = new KinectStreamReceiver(address, port);
    receiver->addListener(this);
}

void KinectRemote::start() {
    receiver->start();
}

void KinectRemote::stop() {
    receiver->stop();
}

bool KinectRemote::isRunning() {
    return receiver->isRunning();
}

void KinectRemote::newData(char *data) {
    float comX = 0;
    float comY = 0;
    float comZ = 0;
    
    int count = 0;
    for (int y = 0.0; y < DEPTH_HEIGHT; y++) {
        for (int x = 0.0; x < DEPTH_WIDTH; x++) {
            
            
            float mx = x;

            const int index = (x + y * DEPTH_WIDTH);
            const int posX = xKeystone(mx, y, keystone);
            const int posY = y;
            
            //clear pixels
            edgeData[index * 3 + 0] = 0.0;
            edgeData[index * 3 + 1] = 0.0;
            edgeData[index * 3 + 2] = 0.0;
            
            // keystone
            if (posX >= leftMargin && posX <= DEPTH_WIDTH - rightMargin && posY >= topMargin && posY <= DEPTH_HEIGHT - bottomMargin) {

                int depthIndex = int((posX + y * DEPTH_WIDTH) * bytesPerPixel);
                int depth = 0;
                
                //1 byte
                if(bytesPerPixel == 1){
                    int value = data[depthIndex] & 255;
                    depth =  value * 39; //ipotizzo che il numero massimo in mm sia 10000 e lo divido per 256
                }
                //2 byte
                else if (bytesPerPixel == 2){
                    int byte0 = 0;
                    int byte1 = 0;
                    int byte2 = data[depthIndex + 0];
                    int byte3 = data[depthIndex + 1];
                    depth = byte0 << 24 | (byte1 & 0xFF) << 16 | (byte2 & 0xFF) << 8 | (byte3 & 0xFF);
                }

                bool valid = false;
                if (posX >= leftMargin && posX <= DEPTH_WIDTH - rightMargin && posY >= topMargin && posY <= DEPTH_HEIGHT - bottomMargin) {
                    int correctMaxDistance = maxDistance * (1.0 - vertCorrection * (cos(M_PI / 3.0 * (DEPTH_HEIGHT - y) / DEPTH_HEIGHT) - 0.5));
                    
                    if (depth >= minDistance && depth <= correctMaxDistance) {
                        float intensity = (depth - minDistance) / (float)(correctMaxDistance - minDistance);
                        edgeData[index * 3 + 0] = 1 - intensity;
                        edgeData[index * 3 + 1] = 1 - intensity;
                        edgeData[index * 3 + 2] = 1 - intensity;
                        valid = true;
                        
                        comX += posX;
                        comY += y;
                        comZ += 1 - intensity;
                        count++;
                    }
                }
                if (!valid) {
                    edgeData[index * 3 + 0] = 0.0;
                    edgeData[index * 3 + 1] = 0.0;
                    edgeData[index * 3 + 2] = 0.0;
                }
            }
        }
    }
    
    if (count > 0) {
        comX /= (float)count;
        comY /= (float)count;
        comZ /= (float)count;
        com.set(comX, comY, comZ);
    }
}

float *KinectRemote::updateEdgeData() {
    return edgeData;
}

void KinectRemote::clearEdgeData(){
    for(int i = 0; i < KinectDevice::DEPTH_WIDTH * KinectDevice::DEPTH_HEIGHT * 3; i++){
        edgeData[i] = 0.0f;
    }
}


ofVec3f &KinectRemote::updateCom() {
    return com;
}

int KinectRemote::xKeystone(const float pX, const float pY, const float keystone){
    float relYFromCenter = (pY - DEPTH_HEIGHT_HALF) / DEPTH_HEIGHT_HALF; //from -1 to 1
    float absXFromCenter = (pX - DEPTH_WIDTH_HALF);
    
    int x = pX + relYFromCenter * keystone * absXFromCenter;
    
    return MIN(x, DEPTH_WIDTH-1);
}


