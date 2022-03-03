#include "WindowManager.h"
#include "App.h"
#include "SDLExceptions.h"

WindowManager::WindowManager(App* app) : app_(app) {
	int numResolutions = SDL_GetNumDisplayModes(0); // first display
	supportedResolutions_.reserve(numResolutions);
	SDL_DisplayMode curr;
	for (int i = 0; i < numResolutions; ++i) {
		SDL_DisplayMode mode;
		SDL_GetDisplayMode(0, i, &mode);
		supportedResolutions_.emplace_back(mode);
		if (&mode == &curr) currentResolution_ = i;
	}
	//window = SDL_CreateWindow("Fighter Traighter ver 1.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		//supportedResolutions_[currentResolution_].w, supportedResolutions_[currentResolution_].h, SDL_WINDOW_SHOWN)
	window = SDL_CreateWindow("Fighter Traighter 1.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1280, 720, SDL_WINDOW_SHOWN);
	if (!window) throw new SDLExceptions::SDLException("Unable to create window");
	SDL_GetCurrentDisplayMode(0, &initialDisplayMode_);
	//setFullscreen(true);
	//setResolution(currentResolution_);
}

// Sets the window in fullscreen
void WindowManager::setFullscreen(bool fullscreen)
{
	if (!fullscreen) {
		if (getFullscreen()) {
			SDL_SetWindowFullscreen(window, 0);
			SDL_SetWindowSize(window, 1280, 720);
		}
	}
	else if (!getFullscreen()) {
		//SDL_SetWindowDisplayMode(window, nullptr/*, &supportedResolutions_[currentResolution_]*/);
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		SDL_GetWindowSize(window, &windowWidth_, &windowHeight_);
		SDL_RenderSetLogicalSize(app_->getRenderer(), 1920/*supportedResolutions_[currentResolution_].w*/, 1080/*supportedResolutions_[currentResolution_].h*/);
	}

}

// Sets the current window resolution, if on fullscreen
void WindowManager::setResolution(int resIndex)
{
	if (getFullscreen()) {
		SDL_RenderSetLogicalSize(app_->getRenderer(), 1920/*supportedResolutions_[currentResolution_].w*/, 1080/*supportedResolutions_[currentResolution_].h*/);
		//SDL_SetWindowFullscreen(window, 0);
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		//SDL_SetWindowDisplayMode(window, nullptr/*, &supportedResolutions_[resIndex]*/);
		currentResolution_ = resIndex;
		SDL_GetWindowSize(window, &windowWidth_, &windowHeight_);	
	}
}

// Changes the brightness of the window (and whole screeen)
void WindowManager::setBrightness(float brightness)
{
	SDL_SetWindowBrightness(window, brightness); // si a alguien se le queda la pantalla oscura, que ponga aqu� un 1 y descomente lo de abajo
	//int b = 0;
	//int a = 1 / b;
	currentBrightness_ = brightness;
}
