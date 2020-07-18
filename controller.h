#ifndef __controller_H__
#define __controller_H__




#include "CXBOXController.h"
#include <iostream>
#include <vector>
#include <cmath>
/*constants
bool GAMEPAD_DPAD_UP          0x0001
bool GAMEPAD_DPAD_DOWN        0x0002
bool GAMEPAD_DPAD_LEFT        0x0004
bool GAMEPAD_DPAD_RIGHT       0x0008
bool GAMEPAD_START            0x0010
bool GAMEPAD_BACK             0x0020
bool GAMEPAD_LEFT_THUMB       0x0040
bool GAMEPAD_RIGHT_THUMB      0x0080
bool GAMEPAD_LEFT_SHOULDER    0x0100
bool GAMEPAD_RIGHT_SHOULDER   0x0200
bool GAMEPAD_A                0x1000
bool GAMEPAD_B                0x2000
bool GAMEPAD_X                0x4000
bool GAMEPAD_Y                0x8000

typedef struct _XINPUT_GAMEPAD
{
	WORD  wButtons;
	BYTE  bLeftTrigger;
	BYTE  bRightTrigger;
	SHORT sThumbLX;
	SHORT sThumbLY;
	SHORT sThumbRX;
	SHORT sThumbRY;
} XINPUT_GAMEPAD, *PXINPUT_GAMEPAD;

*/
struct xinput_controller // better than the xinput.h
{
	/*
	typedef struct _XINPUT_GAMEPAD
	{
		WORD                                wButtons;
		BYTE                                bLeftTrigger;
		BYTE                                bRightTrigger;
		SHORT                               sThumbLX;
		SHORT                               sThumbLY;
		SHORT                               sThumbRX;
		SHORT                               sThumbRY;
	} XINPUT_GAMEPAD, *PXINPUT_GAMEPAD;
	*/
	bool  DPAD_UP = false;
	bool  DPAD_DOWN = false;
	bool  DPAD_LEFT = false;
	bool  DPAD_RIGHT = false;
	bool  START = false;
	bool  BACK = false;
	bool  LEFT_THUMB = false;
	bool  RIGHT_THUMB = false;
	bool  LEFT_SHOULDER = false;
	bool  RIGHT_SHOULDER = false;
	bool  A = false;
	bool  B = false;
	bool  X = false;
	bool  Y = false;
	BYTE bLeftTrigger = 0;
	BYTE bRightTrigger = 0;
	float sThumbLX = 0;
	float sThumbLY = 0;
	float sThumbRX = 0;
	float sThumbRY = 0;
	float magnitude = 0.0;
	float nmagnitude = 0.0;
	bool connected = false;
};
//controller helpers
void setup_controllers(int max_players);
void clean_controller(int max_players);
void clean_controller_input();
bool all_players_connected(int max_players);
void vibrate_controller(int max_players, int number, int leftVal, int rightVal);
//called every frame
std::vector <xinput_controller*> update_controller(int max_players); //controller filter
//demo
#endif // !1
