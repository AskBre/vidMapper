#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	 
	ofBackground(0); 
        ofSetFrameRate(24);
        ofSetVerticalSync(true);

	// Amount of videos
	window.resize(1);

	// Setup each window
	for(unsigned int i = 0; i < window.size(); i++) {
		window[i].setup(i);
	}
	
//	window[2].loadExternalMask("masks/TheTreeHD.png");
}

//--------------------------------------------------------------
void ofApp::update(){	
	// Open a new window for each window
	// This is where the playing and rendering is taking place
	for(int i = 0; i < window.size(); i++) {
		window[0].playVideo();
	}
}
//--------------------------------------------------------------
void ofApp::draw(){
        for(unsigned int i = 0; i < window.size(); i++) {
//		window[i].draw();
	}

#ifdef DEBUG
	showFramerate();
#endif
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

        int keyNum = key-48; // "Converting" from keycode to number key

	if(keyNum >= 0 && keyNum < window.size()) {
		currentWindow = keyNum;
	}

	if(key == 'o') {
		ofFileDialogResult fileResult;
		fileResult = ofSystemLoadDialog();

		if(fileResult.bSuccess) {
			cout << "Name = " << fileResult.getName() << endl;
			
		} else {
			cout << "No file loaded" << endl;
		}
	}

        for(unsigned int i = 0; i < window.size(); i++) 
		window[i].setViewMode();
			
	if(currentWindow >= 0)
		 window[currentWindow].keyPressed(key);
}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
	if(currentWindow >= 0)
		 window[currentWindow].mouseMoved(x, y);
}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if(currentWindow >= 0)
		 window[currentWindow].mouseDragged(x, y, button);
}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if(currentWindow >= 0)
		 window[currentWindow].mousePressed(x, y, button);
}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if(currentWindow >= 0)
		 window[currentWindow].mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::showFramerate() {
        ofDrawBitmapString("Framerate: " + ofToString(ofGetFrameRate()), 1, 10);
}
