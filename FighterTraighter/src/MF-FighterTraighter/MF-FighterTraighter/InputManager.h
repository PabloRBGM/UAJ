#pragma once
#include "SDL.h"
#include <array>
#include "Vector2D.h"
#include <memory>
#include <vector>
#include <SDL_gamecontroller.h>
#include <iostream>
class App;

class InputManager
{
public:
	enum MouseButton : Uint8 {
		Left = 0,
		Right = 1,
		Middle = 2
	};
	struct GamePad {
		bool buttons[SDL_CONTROLLER_BUTTON_MAX];
		int axis[SDL_CONTROLLER_AXIS_MAX];
	};
	InputManager(App* app);
	InputManager(InputManager&) = delete;
	InputManager& operator= (InputManager&) = delete;

	void update();

	// Keyboard
	inline bool isKeyUp(SDL_Scancode code) {
		return keyboardState_[code] == 0;
	};
	inline bool isKeyUp(SDL_Keycode code) {
		return isKeyUp(SDL_GetScancodeFromKey(code));
	};
	inline bool isKeyDown(SDL_Scancode code) {
		return keyboardState_[code] == 1;
	};
	inline bool isKeyDown(SDL_Keycode code) {
		return isKeyDown(SDL_GetScancodeFromKey(code));
	};
	inline bool KeyPressed(SDL_Scancode code) {
		return lastKeyboardState_[code] == 0 && keyboardState_[code] == 1;
	};
	inline bool KeyPressed(SDL_Keycode code) {
		return KeyPressed(SDL_GetScancodeFromKey(code));
	}
	// if pressed or released a key this frame
	inline bool keyboardEvent() {
		return keyboardEvent_;
	}

	// Mouse
	inline bool isMouseButtonPressed(MouseButton button) {
		return mouseState_[button];
	};
	inline double getMousePosX() {
		return mousePos_.getX();
	};
	inline double getMousePosY() {
		return mousePos_.getY();
	};
	inline const Vector2D& getMousePos() {
		return mousePos_;
	};
	inline const Vector2D& getMouseMovement() {
		return mouseMovementInFrame_;
	}
	// if pressed or released a mouse button this frame
	inline bool mouseEvent() {
		return mouseEvent_;
	}

	// Controller

	bool isControllerPressed(int controllerID, std::string* button)
	{
		std::string a = button->c_str();
		if (a == "lefttrigger" || a == "righttrigger")
		{
			return getControllerAxis(controllerID, SDL_GameControllerGetAxisFromString(button->c_str())) > 0.2 ? true : false;
		}
		else
		{
			return isControllerButtonHeld(controllerID, SDL_GameControllerGetButtonFromString(button->c_str()));
		}


	}
	bool isControllerButtonPressed(int controllerID, SDL_GameControllerButton button)
	{
		// SMELLS A LOT
		if (controllerID < 0 || controllerID > numGamepads || !GamepadConnected()) return false;

		return controllerInputs[controllerID].buttons[button] && !lastControllerInputs[controllerID].buttons[button];
	}
	bool isControllerButtonHeld(int controllerID, SDL_GameControllerButton button)
	{
		// SMELLS
		if (controllerID < 0 || controllerID > numGamepads || !GamepadConnected()) return false;

		return controllerInputs[controllerID].buttons[button] && lastControllerInputs[controllerID].buttons[button];
	}
	bool isControllerButtonUp(int controllerID, SDL_GameControllerButton button)
	{
		// SMELLS
		if (controllerID < 0 || controllerID > numGamepads || !GamepadConnected()) return false;

		return !controllerInputs[controllerID].buttons[button] && lastControllerInputs[controllerID].buttons[button];
	}
	float getControllerAxis(int controllerID, SDL_GameControllerAxis axis)
	{
		if (controllerID < 0 || controllerID > numGamepads || !GamepadConnected()) return 0.0;
		return controllerInputs[controllerID].axis[axis] / 32768.0f;
	}
	inline bool GamepadConnected() { return numGamepads > 0; }
	inline int NumGamepadConnected() { return numGamepads ; }
	// if pressed or released a controller button this frame
	inline bool controllerEvent() {
		return controllerEvent_;
	}
	inline bool axisEvent() {
		return axisEvent_;
	}

	inline bool pressedUp() {
		return(!read && (KeyPressed(SDL_SCANCODE_UP) || isControllerButtonPressed(0, SDL_CONTROLLER_BUTTON_DPAD_UP)
			|| (axisEvent() && getControllerAxis(0, SDL_CONTROLLER_AXIS_LEFTY) < -0.8f)));
	}
	inline bool pressedLeft() {
		return(!read && (KeyPressed(SDL_SCANCODE_LEFT) || isControllerButtonPressed(0, SDL_CONTROLLER_BUTTON_DPAD_LEFT)
			|| (axisEvent() && getControllerAxis(0, SDL_CONTROLLER_AXIS_LEFTX) < -0.8f)));
	}
	inline bool pressedDown() {
		return (!read && (KeyPressed(SDL_SCANCODE_DOWN) || isControllerButtonPressed(0, SDL_CONTROLLER_BUTTON_DPAD_DOWN)
			|| (axisEvent() && getControllerAxis(0, SDL_CONTROLLER_AXIS_LEFTY) > 0.8f)));
	}
	inline bool pressedRight() {
		return (!read && (KeyPressed(SDL_SCANCODE_RIGHT) || isControllerButtonPressed(0, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
			|| (axisEvent() && getControllerAxis(0, SDL_CONTROLLER_AXIS_LEFTX) > 0.8f)));
	}
	inline bool pressedAccept() {
		return (!read && (KeyPressed(SDL_SCANCODE_RETURN) || isControllerButtonPressed(0, SDL_CONTROLLER_BUTTON_A)));
	}
	inline bool pressedCancel() {
		return (!read && (KeyPressed(SDL_SCANCODE_X) || isControllerButtonPressed(0, SDL_CONTROLLER_BUTTON_B)));
	}
	inline bool pressedStart() {
		return (!read && (KeyPressed(SDL_SCANCODE_ESCAPE) || isControllerButtonPressed(0, SDL_CONTROLLER_BUTTON_START)
			|| isControllerButtonPressed(0, SDL_CONTROLLER_BUTTON_START)));
	}

	void readKey() { read = true; }
	void stopreadKey() { read = false; lstButton = ""; }
	bool reading() { return read; }
	SDL_Scancode lastKey()
	{
		return lstKey;
	}
	std::string lastcontrol()
	{

		return lstButton;
	}

	virtual ~InputManager();
	SDL_Haptic* getHaptic(int id)
	{
		return gControllerHaptic.at(id);
	}
private:
	void clearState();

	void initControllers();
	inline void onMouseMotion(SDL_Event& e) {
		mousePos_.set(e.motion.x, e.motion.y);
	};


	void onMouseChange(SDL_Event& e, bool state) {
		if (e.button.button == SDL_BUTTON_LEFT) {
			mouseState_[Left] = state;
		}
		else if (e.button.button == SDL_BUTTON_MIDDLE) {
			mouseState_[Middle] = state;
		}
		else if (e.button.button == SDL_BUTTON_RIGHT) {
			mouseState_[Right] = state;
		}
	};

	App* app_;
	const Uint8* keyboardState_;
	Uint8* lastKeyboardState_;
	int numKeys_;
	Vector2D mousePos_;
	std::array<bool, 3> mouseState_; // true = pressed
	Vector2D mouseMovementInFrame_;
	std::vector<SDL_GameController*> connectedControllers;
	std::vector<SDL_Haptic*>gControllerHaptic;
	std::vector<GamePad> controllerInputs;
	std::vector<GamePad> lastControllerInputs;
	int numGamepads;
	// if in this frame there has been an event
	bool mouseEvent_ = false; // click
	bool keyboardEvent_ = false; // press
	bool controllerEvent_ = false; // button
	bool axisEvent_ = false; //axis
	bool read = false;
	std::string lstButton;
	SDL_Scancode lstKey;
};