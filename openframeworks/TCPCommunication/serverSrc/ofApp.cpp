#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofxTCPSettings settings(11999);

	TCP.setup(settings);
	TCP.setMessageDelimiter("\n");
	lastSent = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
	uint64_t now = ofGetElapsedTimeMillis();
	if (now - lastSent >= 100) {
		for (int i = 0; i < TCP.getLastID(); i++) {
			if (!TCP.isClientConnected(i)) continue;
			string str = TCP.receive(i);
			std::cout << "Recieved: " << str << "\n";
			TCP.send(i, "You sent: " + str);
		}
		lastSent = now;
	}
}