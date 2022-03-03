#include "InputManager.h"
#include "App.h"

InputManager::InputManager(App* app) : app_(app)
{
	for (int i = 0; i < mouseState_.size(); ++i) {
		mouseState_[i] = false;
	}
	clearState();
	keyboardState_ = SDL_GetKeyboardState(&numKeys_);
	lastKeyboardState_ = new Uint8[numKeys_];
	initControllers();
	///

}

void InputManager::update()
{
	clearState();
	// For later knowing if the mouse moved
	Vector2D tempMousePos = mousePos_;

	SDL_Event e;
	///Update control input
	for (int i = 0; i < numGamepads; i++) {
		for (int a = 0; a < SDL_CONTROLLER_AXIS_MAX; a++) {
			lastControllerInputs[i].axis[a] = controllerInputs[i].axis[a];
		}
		for (int b = 0; b < SDL_CONTROLLER_BUTTON_MAX; b++) {
			lastControllerInputs[i].buttons[b] = controllerInputs[i].buttons[b];
		}
	}
	///
	for (int i = 0; i < numKeys_; ++i) {
		lastKeyboardState_[i] = keyboardState_[i];
	}

	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			app_->Exit();
			break;
		case SDL_KEYDOWN:
			keyboardEvent_ = true;
			if (read)
			{
				lstKey = e.key.keysym.scancode;

			}
			break;
		case SDL_KEYUP:

			keyboardEvent_ = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouseEvent_ = true;
			onMouseChange(e, true);
			break;
		case SDL_MOUSEBUTTONUP:
			mouseEvent_ = true;
			onMouseChange(e, false);
			break;
		case SDL_MOUSEMOTION:
			onMouseMotion(e);

			break;
		case SDL_CONTROLLERDEVICEADDED:
#ifdef _DEBUG
			std::cout << "DEVICEADDED cdevice.which = " << e.cdevice.which << std::endl;
#endif 
			break;

			// If a controller button is pressed
		case SDL_CONTROLLERBUTTONDOWN:
			controllerEvent_ = true;
			// Cycle through the controllers
			for (int i = 0; i < numGamepads; i++) {
				// Looking for the button that was pressed
				if (e.cbutton.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(connectedControllers[i]))) {
					// So the relevant state can be updated
					controllerInputs[i].buttons[e.cbutton.button] = true;
					if (read)
					{
						lstButton = SDL_GameControllerGetStringForButton((SDL_GameControllerButton)e.cbutton.button);
					}
				}
			}
			break;

			// Do the same for releasing a button
		case SDL_CONTROLLERBUTTONUP:
			controllerEvent_ = true;
			for (int i = 0; i < numGamepads; i++) {
				if (e.cbutton.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(connectedControllers[i]))) {
					controllerInputs[i].buttons[e.cbutton.button] = false;

				}
			}
			break;

			// And something similar for axis motion
		case SDL_CONTROLLERAXISMOTION:

			for (int i = 0; i < numGamepads; i++) {
				if (e.cbutton.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(connectedControllers[i]))) {
					if (abs(controllerInputs[i].axis[e.caxis.axis] - e.caxis.value) > 15000)
					{
						axisEvent_ = true;
						if (read && e.caxis.axis > 3)
						{
							lstButton = SDL_GameControllerGetStringForAxis((SDL_GameControllerAxis)e.caxis.axis);

						}

					}

					controllerInputs[i].axis[e.caxis.axis] = e.caxis.value;
				}
			}
			break;
		}
	}

	// After mouse has updated its position, update the mouse movement
	mouseMovementInFrame_ = mousePos_ - tempMousePos;
}



InputManager::~InputManager()
{
	delete[] lastKeyboardState_;
}

void InputManager::clearState()
{
	mouseEvent_ = false;
	keyboardEvent_ = false;
	controllerEvent_ = false;
	axisEvent_ = false;
}
void InputManager::initControllers()
{
	int nJoysticks = SDL_NumJoysticks();
	if (nJoysticks > 0) {

		numGamepads = 0;

		// Count how many controllers there are
		for (int i = 0; i < nJoysticks; i++)
			if (SDL_IsGameController(i))
				numGamepads++;
		if (numGamepads > 0)
		{
			for (int i = 0; i < numGamepads; i++)
			{
				// Open the controller and add it to our list
				SDL_GameController* pad = SDL_GameControllerOpen(i);
				if (SDL_GameControllerGetAttached(pad) == 1)
				{
					connectedControllers.push_back(pad);

					gControllerHaptic.push_back(SDL_HapticOpenFromJoystick(SDL_GameControllerGetJoystick(pad)));

					if (gControllerHaptic.back() == NULL)
					{
						printf("Warning: Controller does not support haptics! SDL Error: %s\n", SDL_GetError());
					}
					else
					{
						//Get initialize rumble
						if (SDL_HapticRumbleInit(gControllerHaptic.back()) < 0)
						{
							printf("Warning: Unable to initialize rumble! SDL Error: %s\n", SDL_GetError());
						}
					}
				}
				else {
#ifdef _DEBUG

					std::cout << "SDL_GetError() = " << SDL_GetError() << std::endl;
#endif 
				}
			}
		}
		SDL_GameControllerEventState(SDL_ENABLE);

	}
	controllerInputs.resize(numGamepads);
	lastControllerInputs.resize(numGamepads);
	for (int i = 0; i < numGamepads; i++) {
		for (int a = 0; a < SDL_CONTROLLER_AXIS_MAX; a++) {
			controllerInputs[i].axis[a] = 0;
			lastControllerInputs[i].axis[a] = 0;
		}
		for (int b = 0; b < SDL_CONTROLLER_BUTTON_MAX; b++) {
			controllerInputs[i].buttons[b] = false;
			lastControllerInputs[i].buttons[b] = false;
		}
	}
}
///
