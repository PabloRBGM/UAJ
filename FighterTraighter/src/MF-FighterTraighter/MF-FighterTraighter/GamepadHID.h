#pragma once
#include "HID.h"
#include <SDL.h>
class GamepadHID :
	public HID
{
public:
	GamepadHID(InputManager* input, int id) : inputM_(input), gamepadID(id) {}
	std::vector<std::string>& getControl()
	{
		return mando;
	}
	inline void change(int index)
	{
		bool usado = false;
		std::string l = inputM_->lastcontrol();
		for (int i = 0; i < mando.size(); i++)
		{
			if (mando[i] == l)
			{
				usado = true;
				std::string aux = mando[i];
				mando[i] = mando[index];
				mando[index] = aux;
				break;
			}
		}
		if (!usado)
		{

			mando[index] = inputM_->lastcontrol();

		}


	}
	
	virtual void updateInput() override;
protected:
	float ApplyDeadZone(float input)
	{
		if (input > deadZoneAmount) {
			input -= deadZoneAmount;
		}
		else if (input < -deadZoneAmount) {
			input += deadZoneAmount;
		}
		else {
			input = 0;
		}
		return input / (1 - deadZoneAmount);
	}

	const float deadZoneAmount = 0.2; // 0 to 1
	int gamepadID;
	InputManager* inputM_;
	std::vector<std::string>mando = {
	"Start","Back","dpleft","dpup","dpright","dpdown","x","y","b","a","leftshoulder","rightshoulder","leftstick","rightstick","lefttrigger","righttrigger"
	};
	std::vector<SDL_GameControllerButton> buttons = { SDL_CONTROLLER_BUTTON_START,
		SDL_CONTROLLER_BUTTON_BACK, SDL_CONTROLLER_BUTTON_DPAD_LEFT, SDL_CONTROLLER_BUTTON_DPAD_UP,
		SDL_CONTROLLER_BUTTON_DPAD_RIGHT, SDL_CONTROLLER_BUTTON_DPAD_DOWN, SDL_CONTROLLER_BUTTON_X,
		SDL_CONTROLLER_BUTTON_Y, SDL_CONTROLLER_BUTTON_B, SDL_CONTROLLER_BUTTON_A, SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
		SDL_CONTROLLER_BUTTON_RIGHTSHOULDER, SDL_CONTROLLER_BUTTON_LEFTSTICK, SDL_CONTROLLER_BUTTON_RIGHTSTICK };
	std::vector<SDL_GameControllerAxis> axesButtons = { SDL_CONTROLLER_AXIS_LEFTX, SDL_CONTROLLER_AXIS_LEFTY,
		SDL_CONTROLLER_AXIS_RIGHTX, SDL_CONTROLLER_AXIS_RIGHTY, SDL_CONTROLLER_AXIS_TRIGGERLEFT, SDL_CONTROLLER_AXIS_TRIGGERRIGHT };
		
		};


