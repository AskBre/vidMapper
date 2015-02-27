#pragma once

#include "ofMain.h"
#include "ofxGLWarper.h"

#include "Mask.h"


class Surface : public ofBaseApp{

	public:
		void setup(unsigned int surfaceNumber);
		void draw();
		void update();

		void keyPressed(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);

		unsigned int backgroundSet();
		void setViewMode();
		void loadExternalMask(string maskPath);

		void setSource(ofFileDialogResult file);

		unsigned int _surfaceNumber;

	private:
		void drawSurfaceNumber();
		void drawFinalView();
		void drawVideo();

		void fadeOut();
		void fadeIn();
		bool isDoubleClick();

		int mode;
		string modeName;

		bool isFlash;
		int prevFrameNum;
		unsigned int backgroundColor;
		int lastTime;

		float valueEased;

		bool isSourceVideo;

		unsigned int numberOfImages;
		bool hasBeenZero;

		ofxGLWarper warper;
		string warperConfig;

		ofVideoPlayer vid;
		ofPoint vidSize;
		float vidAlpha;

		MaskCreator mask;
		ofImage externalMask;
		bool hasExternalMask;
};
