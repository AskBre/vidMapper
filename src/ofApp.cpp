#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	 
	ofBackground(0); 
        ofSetFrameRate(24);
        ofSetVerticalSync(true);

	currentSurface = -1;
}

void ofApp::update(){	
	// Open a new surface for each window
	// This is where the playing and rendering is taking place
	for(int i = 0; i < surface.size(); i++) {
		surface[i].update();
	}
}

void ofApp::draw(){
        for(unsigned i = 0; i < surface.size(); i++) {
		surface[i].draw();
	}

#ifdef DEBUG
	showFramerate();
#endif
}

//--------------------------------------------------------------
void ofApp::newSurface() {
	Surface tmpSurface;

	ofFileDialogResult file = ofSystemLoadDialog();

	if(file.bSuccess) {
		cout << "Name = " << file.getName() << endl;
		tmpSurface.setSource(file);
	} else {
		cout << "No file loaded" << endl;
	}

	tmpSurface.setup(surface.size());
	surface.push_back(tmpSurface);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

        int keyNum = key-48; // "Converting" from keycode to number key

	if(keyNum >= 0 && keyNum < surface.size()) {
		currentSurface = keyNum;
	}

	if(key == 'o') {
		newSurface();
			}

        for(unsigned int i = 0; i < surface.size(); i++) 
		surface[i].setViewMode();
			
	if(currentSurface >= 0)
		 surface[currentSurface].keyPressed(key);
}

void ofApp::mouseMoved(int x, int y){
	if(currentSurface >= 0)
		surface[currentSurface].mouseMoved(x, y);
}

void ofApp::mouseDragged(int x, int y, int button){
	if(currentSurface >= 0)
		 surface[currentSurface].mouseDragged(x, y, button);
}

void ofApp::mousePressed(int x, int y, int button){
	if(currentSurface >= 0)
		 surface[currentSurface].mousePressed(x, y, button);
}

void ofApp::mouseReleased(int x, int y, int button){
	if(currentSurface >= 0)
		 surface[currentSurface].mouseReleased(x, y, button);
}

void ofApp::showFramerate() {
        ofDrawBitmapString("Framerate: " + ofToString(ofGetFrameRate()), 1, 10);
}
