//
//  KinectStreamReceiver.cpp
//  Dokk
//
//  Created by Paolo Bonacini on 25/11/16.
//
//

#include "KinectStreamReceiver.h"
#include "zlib.h"

KinectStreamReceiver::KinectStreamReceiver(std::string address, int port) {
    KinectStreamReceiver::address = address;
    KinectStreamReceiver::port = port;
}

void KinectStreamReceiver::addListener(KinectStreamListener * listener) {
    listeners.push_back(listener);
}

void KinectStreamReceiver::start() {
    connectTime = 0;
    deltaTime = 0;
    startThread();
}

void KinectStreamReceiver::stop() {
    stopThread();
    if (tcpClient.isConnected()) {
        tcpClient.close();
    }
}

bool KinectStreamReceiver::isRunning() {
    return isThreadRunning();
}

void KinectStreamReceiver::threadedFunction() {
    while (isThreadRunning()) {
        
        if (!tcpClient.isConnected()) {
            
            // if we are not connected lets try and reconnect every 5 seconds
            deltaTime = ofGetElapsedTimeMillis() - connectTime;
            
            if (deltaTime > 5000){
                cout << ofGetTimestampString() + " - KinectStreamReceiver: trying connection to " + address + ":" + to_string(port) << endl;
                
                tcpClient.setup(address, port);
                connectTime = ofGetElapsedTimeMillis();
                
                if (tcpClient.isConnected()) {
                    cout << ofGetTimestampString() + " - KinectStreamReceiver connected to " + address + ":" + to_string(port) << endl;
                }
            }
        }
        
        if (tcpClient.isConnected()) {
            
            // header (data length)
            char *header = new char[4];
            readBytes(header, 4);
            int b0 = (int)(0x0ff & header[0]);
            int b1 = (int)(0x0ff & header[1]);
            int b2 = (int)(0x0ff & header[2]);
            int b3 = (int)(0x0ff & header[3]);
            int length = ((b0 << 24) | (b1 << 16) | (b2 << 8) | b3);
            
            if (length > 0) {
                // data
                char *data = new char[length];
                readBytes(data, length);
                char *uncompressed = decompress(data, length);
                
                for (KinectStreamListener *listener : listeners) {
                    listener->newData(uncompressed);
                }
                
                free(uncompressed);
                delete[] data;
                delete[] header;
            }
        }
        
//        sleep(10);
    }
}

void KinectStreamReceiver::readBytes(char *buffer, unsigned int length) {
    int bytesRead = 0;
    int result;
    while (tcpClient.isConnected() && bytesRead < length)
    {
        result = tcpClient.receiveRawBytes(buffer + bytesRead, length - bytesRead);
        if (result >= 0) {
            bytesRead += result;
        }
    }
}

char *KinectStreamReceiver::decompress(char *compressedBytes, unsigned int length) {
    const int outSize = 512 * 424 * 2;
    char *uncompressedBytes = (char *)calloc(sizeof(char), outSize);
    
    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = length;
    strm.next_in = (Bytef *)(compressedBytes);
    
    if (inflateInit (&strm) != Z_OK) {
        free(uncompressedBytes);
        return uncompressedBytes;
    }
    
    bool done = false;
    do {
        strm.avail_out = outSize - strm.total_out;
        strm.next_out = (Bytef *)(uncompressedBytes + strm.total_out);
        
        int ret = inflate(&strm, Z_SYNC_FLUSH);
        if (ret == Z_STREAM_END) done = true;
        else if (ret != Z_OK) break;
        
    } while (!done || strm.avail_out > 0);
    
    if (inflateEnd (&strm) != Z_OK) {
        free(uncompressedBytes);
        return uncompressedBytes;
    }  
    
    return uncompressedBytes;
}
