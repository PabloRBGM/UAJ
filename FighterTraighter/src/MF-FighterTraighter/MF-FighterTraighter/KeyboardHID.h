#pragma once
#include "HID.h"
#include <SDL.h>
class KeyboardHID :
	public HID
{
public:
	KeyboardHID(InputManager* input) : inputM_(input) {}

	inline void changeKey(int index, SDL_Scancode newKey) {
		bool usado = false;
		for (int i = 0; i < keys_.size(); i++)
		{
			if (keys_[i] == newKey)
			{
				usado = true;
				SDL_Scancode aux = keys_[i];
				keys_[i] = keys_[index];
				keys_[index] = aux;
				break;
			}
		}
		if (!usado)
		{
			keys_[index] = newKey;

		}
	}
	std::vector<SDL_Scancode>& getkeys()
	{
		return keys_;
	}
	void updateInput();
protected:
	// order: buttons + axes(joysticks have two keys)
	std::vector<SDL_Scancode> keys_ = { SDL_SCANCODE_ESCAPE, SDL_SCANCODE_RETURN, // 2
		SDL_SCANCODE_LEFT, SDL_SCANCODE_UP, SDL_SCANCODE_RIGHT, SDL_SCANCODE_DOWN, // 6
		SDL_SCANCODE_E, SDL_SCANCODE_R, SDL_SCANCODE_W, SDL_SCANCODE_Q, SDL_SCANCODE_2, // 11
		SDL_SCANCODE_3, SDL_SCANCODE_RETURN, SDL_SCANCODE_SPACE, SDL_SCANCODE_SPACE, SDL_SCANCODE_T, SDL_SCANCODE_LEFT, // 17
		SDL_SCANCODE_RIGHT, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_J, SDL_SCANCODE_L, // 22
		SDL_SCANCODE_I, SDL_SCANCODE_K }; // 24	//Default value maybe?
	InputManager* inputM_;
};

