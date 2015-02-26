#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define PORT_IN 13000
#define NUM_MSG_STRINGS 20

class SoundAnalyser : public ofBaseApp {
	public:
		void setup();
		void update();

		float getValues(string type);
		float volToSpeedValue;
		float volToSpeedHipValue;
		float volToSpeedLopValue;
		float kickToBoostValue;
		float impulsToRandomValue;

	private:
		ofxOscReceiver receiver;


};
