#pragma once

#include "ofMain.h"
#include "Surface.h"

//#define DEBUG

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

		void showFramerate();

		void newSurface();

		vector<Surface> surface;

		int currentSurface;
};
