//
//  KinectBasePanel.cpp
//  Apologue2047
//
//  Created by Matteo on 22/03/2019.
//

#include "KinectBasePanel.h"

void KinectBasePanel::addGuiComponents(KinectDevice *kinectDevice){
    KinectBasePanel::kinectDevice = kinectDevice;
    
    this->add(connectReleaseButton.setup("CONNECT / RELEASE"));
    connectReleaseButton.addListener(kinectDevice, &KinectDevice::connectRelease);

    this->add(saveButton.setup("SAVE"));
    saveButton.addListener(this, &KinectBasePanel::save);
    
    this->add(minDistanceIntSlider.setup("MIN DISTANCE", 1, 1, 5000));
    minDistanceIntSlider.addListener(kinectDevice, &KinectDevice::setMinDistance);

    this->add(maxDistanceIntSlider.setup("MAX DISTANCE", 10000, 1, 15000));
    maxDistanceIntSlider.addListener(kinectDevice, &KinectDevice::setMaxDistance);
    
    this->add(leftMarginIntSlider.setup("LEFT MARGIN", 0, 0, KinectDevice::DEPTH_WIDTH));
    leftMarginIntSlider.addListener(kinectDevice, &KinectDevice::setLeftMargin);
    
    this->add(rightMarginIntSlider.setup("RIGHT MARGIN", 0, 0, KinectDevice::DEPTH_WIDTH));
    rightMarginIntSlider.addListener(kinectDevice, &KinectDevice::setRightMargin);
    
    this->add(topMarginIntSlider.setup("TOP MARGIN", 0, 0, KinectDevice::DEPTH_HEIGHT));
    topMarginIntSlider.addListener(kinectDevice, &KinectDevice::setTopMargin);
    
    this->add(bottomMarginIntSlider.setup("BOTTOM MARGIN", 0, 0, KinectDevice::DEPTH_HEIGHT));
    bottomMarginIntSlider.addListener(kinectDevice, &KinectDevice::setBottomMargin);
}

void KinectBasePanel::save(){
    if(filename.size() > 1){
        this->saveToFile(filename);
    }
    else if(kinectDevice != NULL){
        filename = kinectDevice->getName()+ "kinect.xml";
    }
    else{
        filename = "kinectPasePanel.xml";
        ofLogWarning("KinectBasePanal", "filename not setted");
    }
    
    saveToFile(filename);
}
