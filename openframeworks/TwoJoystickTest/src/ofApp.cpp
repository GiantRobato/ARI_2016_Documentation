#include "ofApp.h"
//using this tutorial: http://www.binarytides.com/winsock-socket-programming-tutorial/
//use http://get-site-ip.com/ to get google's ip address

//--------------------------------------------------------------
void ofApp::setup(){
	msgTx = "";
	msgRx = "";

	ofxTCPSettings settings("192.168.112.101", 9999);
	tcpClient.setup(settings);
	tcpClient.setMessageDelimiter("\n");
}

//--------------------------------------------------------------
void ofApp::update(){
	//gamepad stuff
	if (!gamepad.Refresh()) {	//gamepad disconnected
		if (wasConnected) {		//print error message once
			wasConnected = false;
			std::cout << "Please connect Xbox 360 controller." << std::endl;
		}
	}
	else {
		if (!wasConnected) {	//confirm connected controller
			wasConnected = true;
			std::cout << "Controller connected on port " << gamepad.GetPort() << std::endl;
		}

		int ly = (int)((gamepad.leftStickY + 1)*(255) / 2);
		int ry = (int)((gamepad.rightStickY + 1)*(255) / (2));
		count++;
		if (count == resetCount) {
			count = 0; //reset counter
			string s = to_string(ly) + " " + to_string(ry);
			//sendOverTCP(ly);
			sendOverTCP(s);
			std::cout << "Left stick: " << ly << "\tRight stick" << ry << std::endl;
		}
	}

	if (tcpClient.isConnected()) {
		string str = tcpClient.receiveRaw();
		if (str.length() > 0) {
			msgRx = str;
			std::cout << str << std::endl;
		}
	} else {
		msgTx = "";
		deltaTime = ofGetElapsedTimeMillis() - connectTime;

		if (deltaTime > 5000) {
			tcpClient.close(); //close so we can reconnect
			ofxTCPSettings settings("192.168.112.101", 9999);
			std::cout << "reconnecting" << std::endl;
			tcpClient.setup(settings);
			connectTime = ofGetElapsedTimeMillis();
		}

	}
}

void ofApp::sendOverTCP(int data) {
	if (tcpClient.isConnected()) {
		msgTx = to_string(data);
		tcpClient.send(msgTx);
	}
}

void ofApp::sendOverTCP(string data) {
	if (tcpClient.isConnected()) {
		tcpClient.send(data);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (tcpClient.isConnected()) {
		if (key == OF_KEY_RETURN) {
			msgTx = "127";
			tcpClient.send(msgTx);
		}
	}
}

void ofApp::testMessage(int i) {
	std::cout << "Got to here (" << i << ") " <<  std::endl;
}