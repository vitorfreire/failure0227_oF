#pragma once

#include "ofMain.h"
#include "ofxFTGLFont.h"
#include "ofxFaceTracker.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
        ofImage logo;
    
        float           nextLetterTime;
        int             lineCount;
        int             letterCount;
    
        string str;
    
        ofTrueTypeFont franklin;
    
        ofxFTGLFont font;
    
    
        vector <string> seussLines;
    
    bool bFirst;
    string typeStr;
    string savedString;
    
    int state;
    
    
    ofVideoGrabber 		vidGrabber;
    ofTexture			videoTexture;
    int 				camWidth;
    int 				camHeight;
    
	
	ofxFaceTracker tracker;
	ExpressionClassifier classifier;
    
    
};
