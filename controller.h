#ifndef __controller_H__
#define __controller_H__




#include "CXBOXController.h"
#include <iostream>
#include <vector>
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
typedef struct xinput_controller // better than the xinput.h
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
	float normalizedMagnitude = 0.0;
	bool connected = false;
};

CXBOXController* Player1;
CXBOXController* Player2;
CXBOXController* Player3;
CXBOXController* Player4;
CXBOXController* players[4] = { Player1 ,Player2 ,Player3 ,Player4 }; // controller handler

//controller helpers
int setup_controllers(int max_players)
{
	for (int index = 0; index < max_players; ++index) {
		players[index] = new CXBOXController(index + 1);
	}
	return 0;
}
void clean_controller(int max_players)
{
	for (int index = 0; index < max_players; ++index) {
		delete players[index];
	}
}
void clean_controller_input(std::vector <xinput_controller*> array)
{
	for (int index = 0; index < array.size(); ++index) {
		delete array[index];
	}
}
bool all_players_connected(int max_players)
{
	for (int index = 0; index < max_players; ++index) {
		if (!players[index]->IsConnected())
			return false;
	}
	return true;
}
void vibrate_controller(int max_players, int number, int leftVal , int rightVal)
{
	if (number > max_players || number < 0)
		return;
	players[number]->Vibrate( leftVal ,  rightVal );
}
//called every frame
std::vector <xinput_controller*> update(int max_players) //controller filter
{
	std::vector <xinput_controller*> controller_inputs(4);//memory of all controllers
	for (int index = 0; index < max_players; ++index) {
		controller_inputs[index] = new xinput_controller(); 
		XINPUT_STATE state = players[index]->GetState(); //current controller

		if ((*players[index]).IsConnected())
		{
			//xinput_controller* controller = new xinput_controller();
			//triggers
			if (state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
			{
				controller_inputs[index]->bLeftTrigger = state.Gamepad.bLeftTrigger;
			}
			if (state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
			{
				controller_inputs[index]->bRightTrigger = state.Gamepad.bRightTrigger;
			}
			//shoulder
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
			{
				controller_inputs[index]->LEFT_SHOULDER = true;
			}
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
			{
				controller_inputs[index]->RIGHT_SHOULDER = true;
			}
			//dpad
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
			{controller_inputs[index]->A = true;			}

			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
			{
				controller_inputs[index]->B = true;
			}

			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X)
			{
				controller_inputs[index]->X = true;
			}

			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
			{
				controller_inputs[index]->Y = true;
			}
			//other
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START)
			{
				controller_inputs[index]->START = true;
			}
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
			{
				controller_inputs[index]->BACK = true;
			}
			//dpad
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
			{
				controller_inputs[index]->DPAD_UP = true;
			}
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
			{
				controller_inputs[index]->DPAD_DOWN = true;
			}
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
			{
				controller_inputs[index]->DPAD_LEFT = true;
			}
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
			{
				controller_inputs[index]->DPAD_RIGHT = true;
			}
			//sticks//left
			//recommended
			{
				

				float LX = state.Gamepad.sThumbLX;
				float LY = state.Gamepad.sThumbLY;

				//determine how far the controller is pushed
				float magnitude = sqrt(LX * LX + LY * LY);

				//determine the direction the controller is pushed
				float normalizedLX = LX / magnitude;
				float normalizedLY = LY / magnitude;

				float normalizedMagnitude = 0;

				//check if the controller is outside a circular dead zone
				if (magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
				{
					//clip the magnitude at its expected maximum value
					if (magnitude > 32767) magnitude = 32767;

					//adjust magnitude relative to the end of the dead zone
					magnitude -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

					//optionally normalize the magnitude with respect to its expected range
					//giving a magnitude value of 0.0 to 1.0
					normalizedMagnitude = magnitude / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

					controller_inputs[index]->sThumbLX = normalizedLX;
					controller_inputs[index]->sThumbLY = normalizedLX;
					controller_inputs[index]->normalizedMagnitude = normalizedMagnitude;
				}
				else //if the controller is in the deadzone zero out the magnitude
				{
					//magnitude = 0.0;
					//normalizedMagnitude = 0.0;
				}
			}
			{//right stick


				float RX = state.Gamepad.sThumbRX;
				float RY = state.Gamepad.sThumbRY;

				//determine how far the controller is pushed
				float magnitude = sqrt(RX * RX + RY * RY);

				//determine the direction the controller is pushed
				float normalizedRX = RX / magnitude;
				float normalizedRY = RY / magnitude;

				float normalizedMagnitude = 0;

				//check if the controller is outside a circular dead zone
				if (magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
				{
					//clip the magnitude at its expected maximum value
					if (magnitude > 32767) magnitude = 32767;

					//adjust magnitude relative to the end of the dead zone
					magnitude -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

					//optionally normalize the magnitude with respect to its expected range
					//giving a magnitude value of 0.0 to 1.0
					normalizedMagnitude = magnitude / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

					controller_inputs[index]->sThumbRX = normalizedRX;
					controller_inputs[index]->sThumbRY = normalizedRY;
					controller_inputs[index]->normalizedMagnitude = normalizedMagnitude;
				}
				else //if the controller is in the deadzone zero out the magnitude
				{
					//magnitude = 0.0;
					//normalizedMagnitude = 0.0;
				}
			}
			
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
			{
				controller_inputs[index]->LEFT_THUMB = true;
			}
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
			{
				controller_inputs[index]->RIGHT_THUMB = true;
			}
			/*	//right
			if (abs(state.Gamepad.sThumbRX) > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
			{
				controller_inputs[index]->sThumbRX = state.Gamepad.sThumbRX;
			}
			if (abs(state.Gamepad.sThumbRY) > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
			{
				controller_inputs[index]->sThumbRY = state.Gamepad.sThumbRY;
			}*/
			controller_inputs[index]->connected = true;
		}		
	}

	return controller_inputs;
}
//demo 
#endif // !1