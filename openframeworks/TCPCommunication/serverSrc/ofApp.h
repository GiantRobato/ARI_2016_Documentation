#pragma once

#include "ofMain.h"
#include "ofxTCPServer.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();

		ofxTCPServer TCP;
		uint64_t lastSent;
};
