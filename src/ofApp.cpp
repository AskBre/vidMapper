#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
        ofSetFrameRate(24);
        ofSetVerticalSync(true);

	currentSurface = -1;

	loadVideos();
}

void ofApp::update(){
	// Open a new surface for each window
	// This is where the playing and rendering is taking place
	for(unsigned i = 0; i < surface.size(); i++) {
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
void ofApp::loadVideos() {
	string path = "CosmicVids"; 
	ofDirectory dir(path);
	//only show png files
	//dir.allowExt("png");
	//populate the directory object
	dir.listDir();

	//go through and print out all the paths
	for(int i = 0; i < dir.size(); i++){
		Surface tmpSurface;
		ofLogNotice(dir.getPath(i));
		string file = dir.getPath(i);
		tmpSurface.setSource(file);
		tmpSurface.setup(surface.size());
		surface.push_back(tmpSurface);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

        unsigned keyNum = key-48; // "Converting" from keycode to number key

	if(keyNum >= 0 && keyNum < surface.size()) {
		currentSurface = keyNum;
	}

        for(unsigned int i = 0; i < surface.size(); i++) {
		surface[i].setViewMode();
	}

	if(currentSurface >= 0) {
		surface[currentSurface].keyPressed(key);
	}
}

void ofApp::mouseMoved(int x, int y){
	if(currentSurface >= 0) {
		surface[currentSurface].mouseMoved(x, y);
	}
}

void ofApp::mouseDragged(int x, int y, int button){
	if(currentSurface >= 0) {
		surface[currentSurface].mouseDragged(x, y, button);
	}
}

void ofApp::mousePressed(int x, int y, int button){
	if(currentSurface >= 0) {
		surface[currentSurface].mousePressed(x, y, button);
	}
}

void ofApp::mouseReleased(int x, int y, int button){
	if(currentSurface >= 0) {
		surface[currentSurface].mouseReleased(x, y, button);
	}
}

void ofApp::showFramerate() {
        ofDrawBitmapString("Framerate: " + ofToString(ofGetFrameRate()), 1, 10);
}
