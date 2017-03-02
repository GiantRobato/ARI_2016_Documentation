#pragma once

#include <stdio.h>
#include <math.h>
#include <cmath>
#define _WIN32_WINNT 0x0601		//define windows 7
#include <windows.h>
#include <XInput.h>

#pragma comment(lib, "XInput.lib") 

class Gamepad {
private:
	int cId; //controller id
	XINPUT_STATE state;
	float deadzoneX;
	float deadzoneY;
public:	
	Gamepad() : deadzoneX(0.2f), deadzoneY(0.2f) {}
	Gamepad(float dzX, float dzY) : deadzoneX(dzX), deadzoneY(dzY) {}

	float leftStickX;
	float leftStickY;
	float rightStickX;
	float rightStickY;
	float leftTrigger;
	float rightTrigger;

	int  GetPort();
	XINPUT_GAMEPAD *GetState();
	bool CheckConnection();
	bool Refresh();
	bool IsPressed(WORD);
};

