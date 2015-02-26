#pragma once

#include "ofMain.h"
#include "WarpedWindow.h"
#include "SoundAnalyser.h"

class ofApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);

		void getSceneNames();
		void setCurrentScene(unsigned sceneNum);
		void playVideo(int windowVersion, string playType, int channel);

		void showFramerate();

		vector<WarpedWindow> window;
		SoundAnalyser sound;

		unsigned currentWindow;
		unsigned scene;
		unsigned prevScene;

		vector<string> sceneName;
};
