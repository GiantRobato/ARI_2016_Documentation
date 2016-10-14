#pragma once

#include "ofMain.h"
#include "ofxTCPClient.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void keyPressed(int key);

		ofxTCPClient tcpClient;

		string msgTx, msgRx;
		int deltaTime, connectTime;
};
