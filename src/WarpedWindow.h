#pragma once

#include "ofMain.h"
#include "ofxGLWarper.h"

#include "MaskCreator.h"


class WarpedWindow : public ofBaseApp{
	
	public:
		void setup(unsigned int windowVersion);
		void draw();

		void keyPressed(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);

		void setAnglePath(string imgPath);
		void addImg(string imgName);
		unsigned int backgroundSet();
		void setViewMode();
		void loadExternalMask(string maskPath);
		void playVideo(string playType, float value);

		unsigned int windowVersion;

	private:
		void drawWarperNumber();
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

		float playhead;
		float valueEased;

		string imgPath;
		void setImgPath(string imgPath);

		unsigned int numberOfImages;
		bool hasBeenZero;

		ofxGLWarper warper;
		string warperConfig;

		ofImage vid;
		ofPoint vidSize;
		float vidAlpha;

		MaskCreator mask;
		ofImage externalMask;
		bool hasExternalMask;
};
