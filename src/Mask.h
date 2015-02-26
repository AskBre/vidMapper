#pragma once

#include "ofMain.h"
#include "ofxBlur.h"
#include "ofxXmlSettings.h"

typedef struct {
        float x;
        float y;
        bool bBeingDragged;
        bool bOver;
        float radius;
        void updatePos(int newX, int newY) {
		x = newX;
		y = newY;
        }
}DraggableVertex;

typedef struct {
        float x;
        float y;
        float radius;
        int fillColor;
        int borderColor;
}CircleCursor;

class MaskCreator : public ofBaseApp{
        public:
		void setup(unsigned maskVersion);

		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void drawShape(float alpha);

		void drawLines();
		void drawCircles();
		//	void addVertex(int x, int y);
		void drawCursor();
		void updateCursor(int x, int y);

		void editShape();

		void newVertex(int x, int y);
		void popBackVertex();
		void eraseVertex();
		void deleteShape();
		void loadShape();
		void saveShape();

		vector<DraggableVertex> vertex;


	private:
		unsigned maskVersion;

		bool isMouseTouchingVertex(unsigned int i, int x, int y);

		CircleCursor cursor;
		
		int vertexBigRadius;
		int circleColor;

		ofxBlur blur;
		bool isBlur;
		
		ofMesh shape;
};
