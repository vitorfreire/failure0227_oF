#include "testApp.h"


using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void testApp::setup(){

    
    tracker.setup();
	tracker.setRescale(.5);
    
    logo.loadImage("logo.png");
    ofBackground(0);
	ofSetColor(255);
    
    camWidth 		= 640;	// try to grab at this size.
	camHeight 		= 480;
	
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);
	videoTexture.allocate(camWidth,camHeight, GL_RGB);


    nextLetterTime = ofGetElapsedTimeMillis();
    lineCount      = 0;
    letterCount    = 0;
    
    bFirst  = true;
	typeStr = ".....          .....";
    
    franklin.loadFont("frabk.ttf", 16, true, true, true);
	
    
    state = 0;
    
    ofEnableAlphaBlending();
    str = "HAHAHAHHA";
    ofSetVerticalSync(true);
    

    font.loadFont("luxirri.ttf", 90, true);
    //ofSetWindowShape(1024, font.getStringBoundingBox(str, 0,0).height);


}

//--------------------------------------------------------------
void testApp::update(){

    vidGrabber.update();
    
    if(vidGrabber.isFrameNew()) {
		if(tracker.update(toCv(vidGrabber))) {
			classifier.classify(tracker);
		}
	}


}

//--------------------------------------------------------------
void testApp::draw(){
    
    switch (state) {
        
        case 0:
            logo.draw(100, 180);
            
            ofSetColor(255);
            
            franklin.drawString(typeStr, 170, 350);
            break;
            
        case 1:
            
            ofEnableBlendMode(OF_BLENDMODE_SCREEN);
            //ofSetColor(255,255,255,80);
            
            
            //font.drawString(savedString, vidGrabber.getFrameRate/2, 320);
            font.drawString(savedString, ofGetWidth() - ( (ofGetFrameNum()*2) % int(font.getStringBoundingBox(str, 100, 100).width + ofGetWidth())), mouseY);
            
        
            vidGrabber.draw(20,20);
            tracker.draw();
            
            
            int w = 150, h = 15;
            ofPushStyle();
            ofPushMatrix();
            ofTranslate(5, 10);
            int n = classifier.size();
            int primary = classifier.getPrimaryExpression();
            for(int i = 0; i < n; i++){
                ofSetColor(i == primary ? ofColor::red : ofColor::black);
                ofRect(0, 0, w * classifier.getProbability(i) + .5, h);
                ofSetColor(255);
                ofDrawBitmapString(classifier.getDescription(i), 5, 9);
                ofTranslate(0, h + 5);
            }
            ofPopMatrix();
            ofPopStyle();
            
        
            break;
    }

    
    
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    
    switch (state) {
        case 0:
            
            if(key == OF_KEY_DEL || key == OF_KEY_BACKSPACE){
                typeStr = typeStr.substr(0, typeStr.length()-1);
            }
            else if(key == OF_KEY_RETURN ){
                // typeStr += "\n";
                savedString = typeStr;
                state = 1;
                
            } else{
                if( bFirst ){
                    typeStr.clear();
                    bFirst = false;
                }
                typeStr.append(1, (char)key);
            }
            break;
            
        case 1:
            
            if(key == 'o') state = 0;
            
            break;
    }
    
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}