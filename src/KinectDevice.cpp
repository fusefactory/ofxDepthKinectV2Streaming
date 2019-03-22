//
//  KinectDevice.cpp
//  Dokk
//
//  Created by Paolo Bonacini on 02/12/16.
//
//

#include "KinectDevice.h"
#include "ofApp.h"
#include <algorithm>

KinectDevice::KinectDevice(std::string name) {
    KinectDevice::name = name;
    fullName = name + " KINECT";
    std::transform(fullName.begin(), fullName.end(), fullName.begin(), ::toupper);
    
    XtoZ = (float)tan(FOV_H / 2) * 2;
    YtoZ = (float)tan(FOV_V / 2) * 2;
    
    lastData = new float[DEPTH_WIDTH * DEPTH_HEIGHT];
    texture.allocate(DEPTH_WIDTH, DEPTH_HEIGHT, GL_RGB);
    texture.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST); // for collison map
    
    // init black texture
    float *data = new float[DEPTH_WIDTH * DEPTH_HEIGHT * 3];
    for (int i = 0; i < DEPTH_WIDTH * DEPTH_HEIGHT * 3; i++) {
        data[i] = 0;
    }
    texture.loadData(data, DEPTH_WIDTH, DEPTH_HEIGHT, GL_RGB);
    delete[] data;
}

std::string KinectDevice::getName() {
    return name;
}

void KinectDevice::connectRelease(){
    if (isRunning()) {
        stop();
    } else {
        start();
    }
}

void KinectDevice::setMinDistance(int &distance) {
    minDistance = distance;
}

int KinectDevice::getMinDistance() {
    return minDistance;
}

void KinectDevice::setMaxDistance(int &distance) {
    maxDistance = distance;
}

int KinectDevice::getMaxDistance() {
    return maxDistance;
}

void KinectDevice::setLeftMargin(int &margin) {
    leftMargin = margin;
}

int KinectDevice::getLeftMargin() {
    return leftMargin;
}

void KinectDevice::setRightMargin(int &margin) {
    rightMargin = margin;
}

int KinectDevice::getRightMargin() {
    return rightMargin;
}

void KinectDevice::setTopMargin(int &margin) {
    topMargin = margin;
}

int KinectDevice::getTopMargin() {
    return topMargin;
}

void KinectDevice::setBottomMargin(int &margin) {
    bottomMargin = margin;
}

int KinectDevice::getBottomMargin() {
    return bottomMargin;
}

void KinectDevice::update() {
    float *data = updateEdgeData();
    texture.loadData(data, DEPTH_WIDTH, DEPTH_HEIGHT, GL_RGB);
    com = updateCom();
}

ofTexture &KinectDevice::getTexture() {
    return texture;
}

ofVec3f &KinectDevice::getCom() {
    return com;
}

void KinectDevice::setAspect(float x, float y, float width, float height) {
    KinectDevice::x = x;
    KinectDevice::y = y;
    KinectDevice::width = width;
    KinectDevice::height = height;
}

void KinectDevice::draw() {
    ofSetColor(255);
    texture.draw(x, y, width, height);
}

void KinectDevice::drawInfo(){
    ofSetColor(255);

    ofDrawBitmapStringHighlight(fullName, x + 20, y + 20);
    if (isRunning()) {
        ofSetColor(0, 255, 0, 255);
    } else {
        ofSetColor(255, 0, 0, 255);
    }
    
    ofDrawRectangle(x + 10, y + 6, 4, 20);
    ofSetColor(0, 0, 255);
    ofDrawLine(x + width / 2.0, y, x + width / 2.0, y + height);
}

void KinectDevice::drawSelected() {
    ofSetColor(20, 97, 189);
    ofDrawRectangle(x + 4, y + 6, 4, 20);
}

float KinectDevice::convertToRealWorldX(float x, float depth) {
    return (x / DEPTH_WIDTH - 0.5f) * depth * XtoZ;
}

float KinectDevice::convertToRealWorldY(float y, float depth) {
    return (0.5f - y / DEPTH_HEIGHT) * depth * YtoZ;
}




