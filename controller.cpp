
#include "controller.h"
#include <iostream>
// controller state
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

CXBOXController* Player1;
CXBOXController* Player2;
CXBOXController* Player3;
CXBOXController* Player4;
CXBOXController* players[4] = { Player1 ,Player2 ,Player3 ,Player4 };
std::vector <xinput_controller*> array = {nullptr,nullptr,nullptr,nullptr};
//controller helpers
void setup_controllers(int max_players)
{
	for (int index = 0; index < max_players; ++index)
	{
		players[index] = new CXBOXController(index + 1);
	}
	for (int index = 0; index < 4; ++index)
	{
		array[index] = new xinput_controller();
	}
}

void clean_controller(int max_players)
{
	for (int index = 0; index < max_players; ++index) {
		delete players[index];
	}
}
void clean_controller_input()//reset data
{
	for (int index = 0; index < array.size(); ++index) {
			array[index]->DPAD_UP = false;
            array[index]->DPAD_DOWN = false;
            array[index]->DPAD_LEFT = false;
            array[index]->DPAD_RIGHT = false;
            array[index]->START = false;
            array[index]->BACK = false;
            array[index]->LEFT_THUMB = false;
            array[index]->RIGHT_THUMB = false;
            array[index]->LEFT_SHOULDER = false;
            array[index]->RIGHT_SHOULDER = false;
            array[index]->A = false;
            array[index]->B = false;
            array[index]->X = false;
            array[index]->Y = false;
            array[index]->bLeftTrigger = 0;
            array[index]->bRightTrigger = 0;
            array[index]->sThumbLX = 0;
            array[index]->sThumbLY = 0;
            array[index]->sThumbRX = 0;
            array[index]->sThumbRY = 0;
			array[index]->connected = false;
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
void vibrate_controller(int max_players, int number, int leftVal, int rightVal)
{
	if (number > max_players || number < 0)
		return;
	players[number]->Vibrate(leftVal, rightVal);
}
//calls every frame
std::vector <xinput_controller*> update_controller(int max_players)
{
	clean_controller_input();
	for (int index = 0; index < max_players; ++index) {
		XINPUT_STATE state = players[index]->GetState(); //current controller
		if ((*players[index]).IsConnected())
		{		//xinput_controller* controller = new xinput_controller();
			//triggers
			if (state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
			{
				array[index]->bLeftTrigger = state.Gamepad.bLeftTrigger;
			}
			if (state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
			{
				array[index]->bRightTrigger = state.Gamepad.bRightTrigger;
			}
			//shoulder
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
			{
				array[index]->LEFT_SHOULDER = true;
			}
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
			{
				array[index]->RIGHT_SHOULDER = true;
			}
			//dpad
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
			{
				array[index]->A = true;
			}

			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
			{
				array[index]->B = true;
			}

			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X)
			{
				array[index]->X = true;
			}

			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
			{
				array[index]->Y = true;
			}
			//other
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START)
			{
				array[index]->START = true;
			}
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
			{
				array[index]->BACK = true;
			}
			//dpad
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
			{
				array[index]->DPAD_UP = true;
			}
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
			{
				array[index]->DPAD_DOWN = true;
			}
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
			{
				array[index]->DPAD_LEFT = true;
			}
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
			{
				array[index]->DPAD_RIGHT = true;
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

					array[index]->sThumbLX = normalizedLX;
					array[index]->sThumbLY = normalizedLX;
					array[index]->nmagnitude = normalizedMagnitude;
					array[index]->magnitude = magnitude;
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

					array[index]->sThumbRX = normalizedRX;
					array[index]->sThumbRY = normalizedRY;
					array[index]->nmagnitude = normalizedMagnitude;
				}
				else //if the controller is in the deadzone zero out the magnitude
				{
					//magnitude = 0.0;
					//normalizedMagnitude = 0.0;
				}
			}

			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
			{
				array[index]->LEFT_THUMB = true;
			}
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
			{
				array[index]->RIGHT_THUMB = true;
			}
			array[index]->connected = true;
		}
		else array[index]->connected = false;
	}

	return array;
}
