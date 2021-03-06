#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    settings.glVersionMajor = 3;
    settings.glVersionMinor = 3;
    settings.windowMode = OF_WINDOW;
    settings.setSize(512, 414);

    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    mainWindow->setWindowTitle("exampleKinectReceiver");

    shared_ptr<ofApp> mainApp(new ofApp);
    
    ofRunApp(mainWindow, mainApp);          //execute setup
    ofRunMainLoop();
}
