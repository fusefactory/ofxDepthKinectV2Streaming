//
//  KinectBasePanel.hpp
//  Apologue2047
//
//  Created by Matteo on 22/03/2019.
//

#ifndef KinectBasePanel_h
#define KinectBasePanel_h

#include <stdio.h>
#include "ofxGui.h"
#include "KinectDevice.h"

class KinectBasePanel : public ofxPanel{    
    public:
        void addGuiComponents(KinectDevice *kinectDevice);
        void save();
        string &getFilename(){return filename;}
    
    protected:
        KinectDevice *kinectDevice;
        ofxButton     connectReleaseButton;
        ofxIntSlider  minDistanceIntSlider;
        ofxIntSlider  maxDistanceIntSlider;
        ofxIntSlider  leftMarginIntSlider;
        ofxIntSlider  rightMarginIntSlider;
        ofxIntSlider  topMarginIntSlider;
        ofxIntSlider  bottomMarginIntSlider;
        ofxButton     saveButton;
};
#endif /* KinectBasePanel_hpp */
