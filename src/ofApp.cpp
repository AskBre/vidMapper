#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	 

	ofBackground(0); 
        ofSetFrameRate(24);
        ofSetVerticalSync(true);

	// Let's create five windows
	window.resize(5);

	for(unsigned int i = 0; i < window.size(); i++)
		window[i].setup(i);
	
	getSceneNames();
	scene = 0;
	setCurrentScene(2);
	sound.setup();

	window[2].loadExternalMask("masks/TheTreeHD.png");
	
}

//--------------------------------------------------------------
void ofApp::update(){	
	sound.update();
	
	float time = int(ofGetFrameNum()) % (3600*30);

	
	if (time == 0) {
		if(scene < 2) {
			scene++;
		} else {
			scene = 0;
		}
	}

//	for(int i = 0; i < window.size(); i++) {
//		window[i].playVideo("normal", 0);
//	}
	
//	switch (scene) {
//		case 0: // Vann
		
			window[0].playVideo("volToSpeedHip", sound.volToSpeedHipValue);
			window[1].playVideo("impulsToRandom", sound.impulsToRandomValue);
			window[2].playVideo("volToSpeed", sound.volToSpeedValue);
			window[3].playVideo("impulsToRandom", sound.impulsToRandomValue);
			window[4].playVideo("volToSpeed", sound.volToSpeedValue);
			
			/*
		break;

		case 1: // Skog
			window[0].playVideo("volToSpeed", sound.volToSpeedValue);
			window[1].playVideo("kickToBoost", sound.kickToBoostValue);
			window[2].playVideo("kickToBoost", sound.kickToBoostValue);
			window[3].playVideo("impulsToRandomPos", sound.impulsToRandomValue);
			window[4].playVideo("impulsToRandomPos", sound.impulsToRandomValue);		break;
		case 2: // Bu
			window[0].playVideo("volToSpeed", sound.volToSpeedValue);
			window[1].playVideo("kickToBoost", sound.kickToBoostValue);
			window[2].playVideo("kickToBoost", sound.kickToBoostValue);
			window[3].playVideo("impulsToRandomPos", sound.impulsToRandomValue);
			window[4].playVideo("impulsToRandomPos", sound.impulsToRandomValue);		break;
		break;
		default:
		break;
	}
	*/

	if(scene != prevScene) {
		setCurrentScene(scene);
	}

	prevScene = scene;

	cout << "Scene: " << scene << endl;
}
//--------------------------------------------------------------
void ofApp::draw(){
        for(unsigned int i = 0; i < window.size(); i++) 
		window[i].draw();

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
void ofApp::getSceneNames() {
	/*
	 *  Function for going through the /vids/ directory 
	 *  looking for scenes (skog, vann, by, etc.) filling
	 *  the sceneName-vector with these names.
	 */

        ofDirectory vidDir("vids");
        vidDir.listDir(); // Contains the scenes

        for(unsigned int i = 0; i < vidDir.size(); i++){
		sceneName.push_back(vidDir.getPath(i));
		cout << "Found scene " << sceneName[i] << endl;
	}
}

//--------------------------------------------------------------
void ofApp::setCurrentScene(unsigned sceneNum) {
	/* 
	 * Function for going through the scenes in sceneName,
	 * loading the paths into the windows.
	 */

	if(sceneNum < sceneName.size()) {
		string currentScene = sceneName[sceneNum];
		string anglePath = currentScene + "/";

		cout << "Using png sequence from " << anglePath << endl;

		for(int i = 0; i < window.size(); i++) {
			window[i].setAnglePath(anglePath);	
		}

	} else {
		cout << "ERROR: The scene number is to high!" << endl;
	}
}

//--------------------------------------------------------------
void ofApp::showFramerate() {
        ofDrawBitmapString("Framerate: " + ofToString(ofGetFrameRate()), 1, 10);
}
