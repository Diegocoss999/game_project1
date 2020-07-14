
#include "controller.h"
#include <iostream>

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
//calls every frame
std::vector <xinput_controller*> update(int max_players)
{
	std::vector <xinput_controller*> controller_inputs(4);
	for (int index = 0; index < max_players; ++index) {
		xinput_controller* controller = new xinput_controller();
		controller_inputs[index] = controller;
		if ((*players[index]).IsConnected())
		{
			//xinput_controller* controller = new xinput_controller();
			//triggers
			if ((*players[index]).GetState().Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
			{
				(*controller).bLeftTrigger = (*players[index]).GetState().Gamepad.bLeftTrigger;
			}
			if ((*players[index]).GetState().Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
			{
				(*controller).bRightTrigger = (*players[index]).GetState().Gamepad.bRightTrigger;
			}
			//shoulder
			if ((*players[index]).GetState().Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
			{
				(*controller).LEFT_SHOULDER = true;
			}
			if ((*players[index]).GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
			{
				(*controller).RIGHT_SHOULDER = true;
			}
			//dpad
			if ((*players[index]).GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
			{(*controller).A = true;			}

			if ((*players[index]).GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B)
			{
				(*controller).B = true;
			}

			if ((*players[index]).GetState().Gamepad.wButtons & XINPUT_GAMEPAD_X)
			{
				(*controller).X = true;
			}

			if ((*players[index]).GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
			{
				(*controller).Y = true;
			}
			//other
			if ((*players[index]).GetState().Gamepad.wButtons & XINPUT_GAMEPAD_START)
			{
				(*controller).START = true;
			}
			if ((*players[index]).GetState().Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
			{
				(*controller).BACK = true;
			}
			//dpad
			if ((*players[index]).GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
			{
				(*controller).DPAD_UP = true;
			}
			if ((*players[index]).GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
			{
				(*controller).DPAD_DOWN = true;
			}
			if ((*players[index]).GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
			{
				(*controller).DPAD_LEFT = true;
			}
			if ((*players[index]).GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
			{
				(*controller).DPAD_RIGHT = true;
			}
			//sticks//left
			if (abs((*players[index]).GetState().Gamepad.sThumbLX) > abs(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
			{
				(*controller).sThumbLX = (*players[index]).GetState().Gamepad.sThumbLX;
			}
			if (abs((*players[index]).GetState().Gamepad.sThumbLY) > abs(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
			{
				(*controller).sThumbLY = (*players[index]).GetState().Gamepad.sThumbLY;
			}
				//right
			if (abs((*players[index]).GetState().Gamepad.sThumbRX) > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
			{
				(*controller).sThumbRX = (*players[index]).GetState().Gamepad.sThumbRX;
			}
			if (abs((*players[index]).GetState().Gamepad.sThumbRY) > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
			{
				(*controller).sThumbRY = (*players[index]).GetState().Gamepad.sThumbRY;
			}

		}
		(*controller).connected = (*players[index]).IsConnected();
	}

	return controller_inputs;
}
