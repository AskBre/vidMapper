#include "Surface.h"

//--------------------------------------------------------------
void Surface::setup(unsigned surfaceNumber){
	_surfaceNumber= surfaceNumber;

        // Set mode
        mode = VIEW_MODE;
	modeName = "no mode";

	hasBeenZero = false;

	warperConfig = "warperConfig" + ofToString(_surfaceNumber) + ".xml";
	warper.setup(0, 0, vid.getWidth(), vid.getHeight());
	warper.load(warperConfig);

        mask.setup(_surfaceNumber);
	hasExternalMask = false;

	vidAlpha = 1;
}

void Surface::draw() {
	warper.begin();

		switch (mode) {
			case VIEW_MODE:
				modeName = "view mode";
				drawFinalView();
			break;

			case WARP_EDIT:
				modeName = "edit warper mode";
				drawFinalView();
				warper.draw();
				drawSurfaceNumber();
			break;

			case MASK_EDIT:
				modeName = "edit mask mode";
				drawFinalView();
				mask.drawCircles();
				mask.drawCursor();
			break;

			case MASK_CREATE:
				modeName = "create mask mode";
				drawVideo();
				mask.drawLines();
				mask.drawCursor();
			break;

			default:
				modeName = "no mode";
				drawFinalView();
			break;
		}

	warper.end();
}

void Surface::update() {
	vid.update();
	/*
	if(playhead < numberOfImages) {
		playhead++;
	} else {
		playhead = 0;
	}
	*/
}

//--------------------------------------------------------------
void Surface::keyPressed(int key){

        switch (key) {

		// Change modes
		case 'w':
			mode = WARP_EDIT;
		break;

		case 'm':
			// Go to mask creation mode if no mask is present
			if(mask.vertex.size() == 0 || mode == MASK_EDIT) mode = MASK_CREATE;
			else mode = MASK_EDIT;

//			if(mode == MASK_CREATE) mode = MASK_EDIT;
		break;

		case 'v':
			mode = VIEW_MODE; // Go to view mode
		break;

		case 'r':
			mask.deleteShape();
			hasExternalMask = false;
		break;

		// Save and load the warper coordinates
		case 's':
			warper.save(warperConfig);
			mask.saveShape();

			isFlash = true;
			prevFrameNum = ofGetFrameNum();
		break;

		case 'l':
			mask.loadShape();
			warper.load(warperConfig);

			isFlash = true;
			prevFrameNum = ofGetFrameNum();
		break;

		default:
		break;
        }

	cout << "Surface " << _surfaceNumber << " is now in " << modeName << endl;

        if(mode == WARP_EDIT) {
		warper.deactivate();
		warper.activate();
        } else {
		warper.deactivate();
        }

}

void Surface::mouseMoved(int x, int y) {
        mask.updateCursor(x, y);
}

void Surface::mouseDragged(int x, int y, int button) {
	mask.mouseDragged(x, y, button);
        mask.updateCursor(x, y);
}

void Surface::mousePressed(int x, int y, int button) {
        mask.mousePressed(x, y, button);
}

void Surface::mouseReleased(int x, int y, int button) {
        switch (mode) {
		case VIEW_MODE:
		break;

		case WARP_EDIT:
		break;

		case MASK_EDIT:
		break;

		case MASK_CREATE:
			if(button == 0) mask.newVertex(x, y);
			else if (button == 2) mask.popBackVertex();

			if(isDoubleClick()) mode = MASK_EDIT;
		break;

		default:
		break;
        }
}

//--------------------------------------------------------------
void Surface::setSource(ofFileDialogResult file) {
	cout << "Opening the file " << file.getPath() << endl;

	vid.loadMovie(file.getPath());
	vid.setLoopState(OF_LOOP_NORMAL);
	vid.play();
}

unsigned int Surface::backgroundSet() {
        // Small function to be able to flash the screen when
        // performing certain stuff

        if(isFlash){
		if(ofGetFrameNum() > prevFrameNum + 10) isFlash = false;

		return 255;
        } else {
		return 0;
        }
}

void Surface::setViewMode() {
	mode = VIEW_MODE;
	warper.deactivate();
}

void Surface::drawSurfaceNumber() {
        // Draw surfaec number of current surface top left of surface
	if(warper.isActive()) ofDrawBitmapString(ofToString(_surfaceNumber), 0, 0);
}

void Surface::drawFinalView() {

	ofPushStyle();
		if(hasExternalMask) {
			glEnable(GL_BLEND);
			glColorMask(0, 0, 0, 1);
			glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
			externalMask.draw(0,0);

			glColorMask(1, 1, 1, 1);
			glBlendFunc(GL_ONE_MINUS_DST_ALPHA, GL_DST_ALPHA);
		}


		if(mask.vertex.size() > 0) { // If the mask exists
		// Add the mask shape to buffer
			glEnable(GL_BLEND);
			glColorMask(0, 0, 0, 1);
			glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
			mask.drawShape(vidAlpha);

			// Draw the video into the buffer, masked by the current alpha
			glColorMask(1, 1, 1, 1);
			glBlendFunc(GL_ONE_MINUS_DST_ALPHA, GL_DST_ALPHA);
		}

		glColor4f(1, 1, 1, vidAlpha);
		drawVideo();
		glDisable(GL_BLEND);
	ofPopStyle();
}

void Surface::drawVideo() {
	vid.draw(0, 0, vid.getWidth(), vid.getHeight());
}

//--------------------------------------------------------------
void Surface::loadExternalMask(string maskPath) {
	externalMask.loadImage(maskPath);
	externalMask.resize(vid.getWidth(), vid.getHeight());
	hasExternalMask = true;
}


void Surface::fadeOut() {
	if(vidAlpha > 0) vidAlpha -= .05;
}
void Surface::fadeIn() {
	if(vidAlpha < 1) vidAlpha += .05;
}
bool Surface::isDoubleClick() {
        unsigned int timer = 250;

        if(ofGetElapsedTimeMillis() - lastTime < timer) {
		lastTime = ofGetElapsedTimeMillis();
		return true;
        }
        else {
		lastTime = ofGetElapsedTimeMillis();
		return false;
        }
}
