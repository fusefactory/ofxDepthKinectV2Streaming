//
//  KinectBlobPanel.cpp
//  Apologue2047
//
//  Created by Matteo on 22/03/2019.
//

#include "KinectBlobPanel.h"

void KinectBlobPanel::addGuiComponents(KinectDevice *kinectDevice, KinectHandTracker *kinectHandTracker){
    KinectBasePanel::addGuiComponents(kinectDevice);

    KinectBlobPanel::kinectHandTracker = kinectHandTracker;
    
    this->add(blobToggle.setup("BLOBS", true));
    blobToggle.addListener(kinectHandTracker, &::KinectHandTracker::toggleBlobs);
   
    this->add(minAreaIntSlider.setup("MIN AREA", kinectHandTracker->getMinArea(), 0, 1000));
    minAreaIntSlider.addListener(kinectHandTracker, &::KinectHandTracker::setMinArea);

    this->add(maxAreaIntSlider.setup("MAX AREA", kinectHandTracker->getMaxArea(), 1000, 50000));
    maxAreaIntSlider.addListener(kinectHandTracker, &::KinectHandTracker::setMaxArea);
}
