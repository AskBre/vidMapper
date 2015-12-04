#include "Mask.h"

//--------------------------------------------------------------
void MaskCreator::setup(unsigned _maskVersion){
	maskVersion = _maskVersion;

        vertexBigRadius = 8;

        circleColor = 0xff0000;

        ofSetPolyMode(OF_POLY_WINDING_ODD);

        // Setup cursor (circle that shows the mouse position inside the warp) (Change to crosshair?)
        cursor.radius = 10;
        cursor.fillColor = 0xff0000;
        cursor.borderColor = 0xfffff0;

        // Setup blur
        int blurRadius = 8;
        float blurShape = .2;
        int blurPasses = 8;
        float blurDownsample = 0.5;
        isBlur = false;
        blur.setup(ofGetWidth(), ofGetHeight(), blurRadius, blurShape, blurPasses, blurDownsample);
//        blur.setBrightness(.5);

	loadShape();
}

//--------------------------------------------------------------
void MaskCreator::mouseDragged(int x, int y, int button){
        for(unsigned int i = 0; i < vertex.size(); i++) {
		if(vertex[i].bBeingDragged)
			vertex[i].updatePos(x, y);
	}
}

//--------------------------------------------------------------
void MaskCreator::mousePressed(int x, int y, int button){
        for(unsigned int i = 0; i < vertex.size(); i++) {
		if(isMouseTouchingVertex(i, x, y)) vertex[i].bBeingDragged = true;
		else vertex[i].bBeingDragged = false;
	}
}

// Drawing
//--------------------------------------------------------------
void MaskCreator::drawLines(){
	ofPushStyle();
		ofSetHexColor(0xffffff);
		for(unsigned int i = 1; i < vertex.size(); i++) {
			ofLine(vertex[i].x, vertex[i].y, vertex[i-1].x, vertex[i-1].y);
		}

		if(vertex.size() == 1) ofCircle(vertex[0].x, vertex[0].y, 1);
	ofPopStyle();
}

void MaskCreator::drawShape(float alpha){
	ofPushStyle();
		glColor4f(1, 1, 1, 1-alpha);
		ofFill();
		if(isBlur) blur.begin();
		ofBeginShape();
		for(unsigned int i = 0; i < vertex.size(); i++) {
			ofVertex(vertex[i].x, vertex[i].y);
		}
		ofEndShape();
		if(isBlur)
			blur.end();
		if(isBlur)
			blur.draw();
	ofPopStyle();
}

void MaskCreator::drawCircles(){
	ofPushStyle();
		ofSetHexColor(circleColor);
		ofNoFill();
		for(unsigned int i = 0; i < vertex.size(); i++) {
			ofCircle(vertex[i].x, vertex[i].y, vertex[i].radius);
		}
	ofPopStyle();
}

void MaskCreator::drawCursor(){
	ofPushStyle();
		ofNoFill();
		ofSetHexColor(cursor.borderColor);
		ofCircle(cursor.x, cursor.y, cursor.radius);
		ofFill();
		ofSetHexColor(cursor.fillColor);
		ofCircle(cursor.x, cursor.y, cursor.radius/4);
	ofPopStyle();
}
//--------------------------------------------------------------
void MaskCreator::updateCursor(int x, int y){
        cursor.x = x;
        cursor.y = y;

        for (unsigned int i = 0; i < vertex.size(); i++){
		if (isMouseTouchingVertex(i, x, y)) {
			vertex[i].bOver = true;
			vertex[i].radius = vertexBigRadius;
		} else {
			vertex[i].bOver = false;
			vertex[i].radius = 0;
		}
        }
}

//--------------------------------------------------------------
void MaskCreator::editShape(){
        for (unsigned int i = 0; i < vertex.size(); i++) {
		if (vertex[i].bBeingDragged)
			vertex[i].updatePos(cursor.x, cursor.y);
        }
}

//--------------------------------------------------------------
void MaskCreator::newVertex(int x, int y) {
        DraggableVertex newVertex;

        newVertex.x = x;
        newVertex.y = y;
        newVertex.bOver = false;
        newVertex.bBeingDragged = false;
        newVertex.radius = 0;

        vertex.push_back(newVertex);
}

//--------------------------------------------------------------
void MaskCreator::popBackVertex() {
        if(vertex.size() > 0)
		vertex.pop_back();
}

//--------------------------------------------------------------
void MaskCreator::eraseVertex() {
        for(unsigned int i = 0; i < vertex.size(); i++) {
		if(vertex[i].bOver)
			vertex.erase(vertex.begin() + i);
        }
}

//--------------------------------------------------------------
void MaskCreator::deleteShape() {
        vertex.clear();
}
//--------------------------------------------------------------
void MaskCreator::loadShape() {
	string maskName = "masks/mask" + ofToString(maskVersion) + ".xml";
	vertex.clear();

	ofxXmlSettings settings;
	if(settings.loadFile(maskName)){
		settings.pushTag("positions");
		int numberOfSavedPoints = settings.getNumTags("position");
		for(int i = 0; i < numberOfSavedPoints; i++){
			settings.pushTag("position", i);

			ofPoint p;
			p.x = settings.getValue("X", 0);
			p.y = settings.getValue("Y", 0);

			newVertex(p.x, p.y);
			settings.popTag();
		}

		settings.popTag(); //pop position
		cout << "Mask loaded!" << endl;
	}
	else{
		ofLogError("Position file did not load!");
	}
}

//--------------------------------------------------------------
void MaskCreator::saveShape() {
	string maskName = "masks/mask" + ofToString(maskVersion) + ".xml";

	ofxXmlSettings positions;
	positions.addTag("positions");
	positions.pushTag("positions");
	//points is a vector<ofPoint> that we want to save to a file
	for(int i = 0; i < vertex.size(); i++){
//each position tag represents one point
		positions.addTag("position");
		positions.pushTag("position",i);
		//so set the three values in the file
		positions.addValue("X", vertex[i].x);
		positions.addValue("Y", vertex[i].y);
		positions.popTag();//pop position
	}

	positions.popTag(); //pop position
	positions.saveFile(maskName);
	cout << "Mask saved!" << endl;
}

//--------------------------------------------------------------
bool MaskCreator::isMouseTouchingVertex(unsigned int i, int x, int y) {
	float diffX = x - vertex[i].x;
	float diffY = y - vertex[i].y;
	float dist = sqrt(diffX*diffX + diffY*diffY);

	if (dist < vertexBigRadius/4) return true;
	else return false;
}

//--------------------------------------------------------------
/* I'll save this for later, it's more of a bonus than a core feature
void MaskCreator::addVertex(int x, int y){
        // First return the closest two vertexes that are connected
        // Then add a new vertex between these

        vector<<vector <float> > distances;

        // Get a vector of all the distances
        for (unsigned int i = 0; i < vertex.size(); i++){
	float diffX = x - vertex[i].x;
	float diffY = y - vertex[i].y;
	float dist = sqrt(diffX*diffX + diffY*diffY);
	distances.push_back(i);
	distances[i].push_back(dist);
        }

}
*/
