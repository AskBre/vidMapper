#include "SoundAnalyser.h"

//--------------------------------------------------------------
void SoundAnalyser::setup(){
	// listen on the given port
	cout << "listening for osc messages on port " << PORT_IN << "\n";

	receiver.setup(PORT_IN);

	ofBackground(0);

}

void SoundAnalyser::update() {
	// check for waiting messages

	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
		if(m.getAddress() == "/volToSpeed"){
			volToSpeedValue =  m.getArgAsFloat(0);
		} else if (m.getAddress() == "/volToSpeedHip"){
			volToSpeedHipValue =  m.getArgAsFloat(0);
		} else if (m.getAddress() == "/volToSpeedLop"){
			volToSpeedLopValue =  m.getArgAsFloat(0);
		} else if (m.getAddress() == "/kickToBoost"){
			kickToBoostValue =  m.getArgAsFloat(0);
		}  else if (m.getAddress() == "/impulsToRandom"){
			impulsToRandomValue =  m.getArgAsFloat(0);
		} else {
			cout << "Address not in use: " << m.getAddress() << endl;
		}
	}
}

float SoundAnalyser::getValues(string type) {
	// check for waiting messages
	float value;

	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
		if(m.getAddress() == "/" + ofToString(type)){
			value =  m.getArgAsFloat(0);
		} else {
			value = -1;
			cout << "Not found: " << type << endl;
		}
	}
	return value;
}
