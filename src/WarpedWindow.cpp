#include "WarpedWindow.h"

//--------------------------------------------------------------
void WarpedWindow::setup(unsigned _windowVersion){	 
	windowVersion = _windowVersion;
	
	// Setup video
	playhead = 1;
	vid.allocate(400, 200, OF_IMAGE_COLOR);

        // Set mode
        // 0: View mode (global)
        // 1: Edit warper 
        // 2: Edit mask
        // 3: Create mask
        mode = 0; 
	modeName = "no mode";
        
	hasBeenZero = false;
        
	warperConfig = "warperConfig" + ofToString(windowVersion) + ".xml";
	warper.setup(0, 0, vid.getWidth(), vid.getHeight());
	warper.load(warperConfig);

        mask.setup(windowVersion);
	hasExternalMask = false;

}

//--------------------------------------------------------------
void WarpedWindow::draw() {
	warper.begin();

		switch (mode) {
			case 0: // View mode
				modeName = "view mode";
				drawFinalView();
			break;

			case 1: // Edit warper
				modeName = "edit warper mode";
				drawFinalView();
				warper.draw();
				drawWarperNumber();
			break;

			case 2: // Edit mask
				modeName = "edit mask mode";
				drawFinalView();
				mask.drawCircles();
				mask.drawCursor();
			break;

			case 3: // Create mask
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

//--------------------------------------------------------------
void WarpedWindow::keyPressed(int key){

        switch (key) {
		
		// Change modes
		case 'w':
			mode = 1; // Go to warp edit mode
		break;

		case 'm':
			if(mask.vertex.size() == 0 || mode == 2) 
				mode = 3; // Go to mask creation mode if no mask is present
			else 
				mode = 2; // else go to mask edit mode

			if(mode == 3)
				mode = 2; // Swap the modes
		break;

		case 'v':
			mode = 0; // Go to view mode
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

	cout << "Window " << windowVersion << " is now in " << modeName << endl;
        
        if(mode == 1) {
		warper.deactivate();
		warper.activate();
        } else {
		warper.deactivate();
        }

}

//--------------------------------------------------------------
void WarpedWindow::mouseMoved(int x, int y) {
        mask.updateCursor(x, y);
}
//--------------------------------------------------------------
void WarpedWindow::mouseDragged(int x, int y, int button) {
	mask.mouseDragged(x, y, button);
        mask.updateCursor(x, y);
}
//--------------------------------------------------------------
void WarpedWindow::mousePressed(int x, int y, int button) {
        mask.mousePressed(x, y, button);
}
//--------------------------------------------------------------
void WarpedWindow::mouseReleased(int x, int y, int button) {
        switch (mode) {
		case 0: // View mode
		break;

		case 1: // Edit warper
		break;

		case 2: // Edit mask
		break;

		case 3: // Create mask
			if(button == 0) {
				mask.newVertex(x, y);
			}
			else if (button == 2)
				mask.popBackVertex();
			if(isDoubleClick()) 
				mode = 2;
		break;

		default:
		break;
        }
}

//--------------------------------------------------------------
void WarpedWindow::setAnglePath(string anglePath) {
	// Iterate through all folders, setting the imgPath
	// in relation to windowVersion

	ofDirectory angleDir(anglePath);
	angleDir.listDir();

	string newImgPath = angleDir.getPath(windowVersion) + "/";
	setImgPath(newImgPath);

	cout << "Setting angle path in window version " << windowVersion << " to " << angleDir.getPath(windowVersion) << endl;
}
//--------------------------------------------------------------
void WarpedWindow::setImgPath(string _imgPath) {
	imgPath = _imgPath;

	ofDirectory imgDir(imgPath);
	imgDir.listDir();
	
	numberOfImages = imgDir.size();

	cout << "Number of images in " << imgPath << " is " << numberOfImages << endl;
}
//--------------------------------------------------------------
unsigned int WarpedWindow::backgroundSet() {
        // Small function to be able to flash the screen when
        // performing certain stuff

        if(isFlash){
		if(ofGetFrameNum() > prevFrameNum + 10)
			isFlash = false;
	
		return 255;
        } else {
		return 0;
        }
}
//--------------------------------------------------------------
void WarpedWindow::setViewMode() {
	mode = 0;
	warper.deactivate();
}
//--------------------------------------------------------------
void WarpedWindow::drawWarperNumber() {
        // Draw window number of current warper top left of warper        
	if(warper.isActive())
		ofDrawBitmapString(ofToString(windowVersion), 0, 0);
}
//--------------------------------------------------------------
void WarpedWindow::drawFinalView() {

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
//--------------------------------------------------------------
void WarpedWindow::drawVideo() {
	unsigned intPlayhead = ceil(playhead);
	string imgName = imgPath + ofToString(intPlayhead) + ".png";

	vid.loadImage(imgName);
	vid.draw(0, 0, vid.getWidth(), vid.getHeight());
}
//--------------------------------------------------------------
void WarpedWindow::loadExternalMask(string maskPath) {
	externalMask.loadImage(maskPath);
	externalMask.resize(vid.getWidth(), vid.getHeight());
	hasExternalMask = true;
}

//--------------------------------------------------------------
void WarpedWindow::playVideo(bool palindrome) {
	if(playhead < numberOfImages) {
		playhead++;
	} else {
		playhead = 0;
	}
}

//--------------------------------------------------------------
void WarpedWindow::fadeOut() {
	if(vidAlpha > 0) {
		vidAlpha -= .05;
	}
}
//--------------------------------------------------------------
void WarpedWindow::fadeIn() {
	if(vidAlpha < 1) {
		vidAlpha += .05;
	}
}
//--------------------------------------------------------------
bool WarpedWindow::isDoubleClick() {
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
