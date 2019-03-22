//
//  KinectStreamListener.h
//  Dokk
//
//  Created by Paolo Bonacini on 02/12/16.
//
//

#ifndef KinectStreamListener_h
#define KinectStreamListener_h

class KinectStreamListener {
    
public:
    virtual void newData(char *data) {};
};

#endif /* KinectStreamListener_h */
