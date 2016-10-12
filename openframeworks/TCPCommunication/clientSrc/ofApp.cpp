#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	msgTx = "";
	msgRx = "";

	ofxTCPSettings settings("127.0.0.1", 11999);
	tcpClient.setup(settings);
	tcpClient.setMessageDelimiter("\n");
}

void ofApp::update(){
	if (tcpClient.isConnected()) {
		// we are connected - lets try to receive from the server
		string str = tcpClient.receive();
		if (str.length() > 0) {
			msgRx = str;
			std::cout << str << std::endl;
		}
	} else {
		msgTx = "";
		// if we are not connected lets try and reconnect every 5 seconds
		deltaTime = ofGetElapsedTimeMillis() - connectTime;

		if (deltaTime > 5000) {
			tcpClient.setup("127.0.0.1", 11999);
			connectTime = ofGetElapsedTimeMillis();
		}
	}
}

void ofApp::keyPressed(int key){
	if (tcpClient.isConnected()) {
		if (key == OF_KEY_RETURN) {
			msgTx = "Hello!";
			tcpClient.send(msgTx);
		}
	}
}