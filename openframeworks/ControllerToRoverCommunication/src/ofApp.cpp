#include "ofApp.h"

void ofApp::setup(){
	roverAddress = "192.168.112.101";

	ofxTCPSettings settings(roverAddress, 9999);
	tcpClient.setup(settings);
	tcpClient.setMessageDelimiter("\n");
	gui.setup();
}

void ofApp::update(){
	if (!gamepad.Refresh()) {	//gamepad disconnected
		if (wasConnected) {		//print error message once
			wasConnected = false;
			std::cout << "Please connect Xbox 360 controller." << std::endl;
		}
	} else {
		if (!wasConnected) {	//confirm connected controller
			wasConnected = true;
			std::cout << "Controller connected on port " << gamepad.GetPort() << std::endl;
		}
		//send commands over tcp
		if (tcpClient.isConnected()) {
			msgTx = to_string(gamepad.leftStickY) + " " + to_string(gamepad.rightStickY);
			tcpClient.send(msgTx);

			string str = tcpClient.receiveRaw();
			if (str.length() > 0) {
				msgRx = str;
				std::cout << str << std::endl;
			}
		}
		else {
			msgTx = "";
			deltaTime = ofGetElapsedTimeMillis() - connectTime;

			if (deltaTime > 5000) {
				tcpClient.setup(roverAddress, 9999);
				connectTime = ofGetElapsedTimeMillis();
			}
		}
	} //end of gamepad 1 code
}

//--------------------------------------------------------------
void ofApp::draw(){
}