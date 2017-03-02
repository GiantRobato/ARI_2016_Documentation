#pragma once

#include "ofMain.h"
#include "ofxTCPClient.h"
#include "ofxGamepad.h"
#include <stdlib.h> //for exit
#include <stdio.h>

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();

		void keyPressed(int key);
		void testMessage(int);
		void sendOverTCP(int data);

		ofxTCPClient tcpClient;
		string msgTx, msgRx;
		int deltaTime, connectTime;
		SOCKET s;
		struct sockaddr_in server;
		Gamepad gamepad;
		bool wasConnected = true;
		int count = 0;
		int resetCount = 5;
};
