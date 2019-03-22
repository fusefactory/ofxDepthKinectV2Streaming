//
//  KinectBlobPanel.hpp
//  Apologue2047
//
//  Created by Matteo on 22/03/2019.
//

#ifndef KinectBlobPanel_h
#define KinectBlobPanel_h

#include <stdio.h>
#include "KinectBasePanel.h"
#include "KinectHandTracker.h"

class KinectBlobPanel : public KinectBasePanel{
    public:
        void addGuiComponents(KinectDevice *kinectDevice, KinectHandTracker *kinectHandTracker);
    
        ofxToggle       blobToggle;
        ofxIntSlider    minAreaIntSlider;
        ofxIntSlider    maxAreaIntSlider;
    protected:
        KinectHandTracker *kinectHandTracker;
};
#endif /* KinectBlobPanel_hpp */
