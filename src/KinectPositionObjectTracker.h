//
//  KinectPositionTracker.h
//  Apologue2047
//
//  Created by Matteo on 14/05/2019.
//

#ifndef KinectPositionTracker_h
#define KinectPositionTracker_h

#include <stdio.h>
#include "KinectObjectTracker.h"

class KinectPositionObjectTracker : public KinectObjectTracker {
    
public:
    KinectPositionObjectTracker(KinectDevice *kinect);
    void update(int maxBlobs) override;
    std::vector<ofVec3f> &getPositionsTracked() {return positionsTracked;}
    
private:
    std::vector<ofVec3f> positionsTracked;
    
    void calculatePositionTracked();
};

#endif /* KinectPositionTracker_h */
