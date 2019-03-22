//
//  KinectHandTracker.h
//  Dokk
//
//  Created by Paolo Bonacini on 03/02/17.
//
//

#ifndef KinectHandTracker_h
#define KinectHandTracker_h

#include <stdio.h>
#include "KinectObjectTracker.h"
#include "TrackedHand.h"

class KinectHandTracker : public KinectObjectTracker {
    
public:
    KinectHandTracker(KinectDevice *kinect);
    std::vector<TrackedHand> getTrackedHands();
    void update(int maxBlobs) override;
    
    void setMinArea(int &area) override;
    void setMaxArea(int &area) override;
    void toggleBlobs(bool &value) override;
    
private:
    std::vector<TrackedHand> hands;
    void calculateTrackedHands();
};
#endif /* KinectHandTracker_h */
