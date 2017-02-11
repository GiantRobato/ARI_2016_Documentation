#pragma once

#include "ofMain.h"
#include "ofxGamepad.h"
#include "ofxGui.h"
#include "ofxTCPClient.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		Gamepad gamepad;
		bool wasConnected = true;

		ofxPanel gui;
		ofxTCPClient tcpClient;
		int deltaTime, connectTime;
		string roverAddress;
		string msgTx, msgRx;
};