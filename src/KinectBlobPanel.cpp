//
//  KinectBlobPanel.cpp
//  Apologue2047
//
//  Created by Matteo on 22/03/2019.
//

#include "KinectBlobPanel.h"

void KinectBlobPanel::addGuiComponents(KinectDevice *kinectDevice, KinectObjectTracker *kinectObjectTracker){
    KinectBasePanel::addGuiComponents(kinectDevice);

    KinectBlobPanel::kinectObjectTracker = kinectObjectTracker;
    
    this->add(blobToggle.setup("BLOBS", true));
    blobToggle.addListener(kinectObjectTracker, &::KinectObjectTracker::toggleBlobs);
   
    this->add(minAreaIntSlider.setup("MIN AREA", kinectObjectTracker->getMinArea(), 0, 1000));
    minAreaIntSlider.addListener(kinectObjectTracker, &::KinectHandTracker::setMinArea);

    this->add(maxAreaIntSlider.setup("MAX AREA", kinectObjectTracker->getMaxArea(), 1000, 50000));
    maxAreaIntSlider.addListener(kinectObjectTracker, &::KinectHandTracker::setMaxArea);
}
