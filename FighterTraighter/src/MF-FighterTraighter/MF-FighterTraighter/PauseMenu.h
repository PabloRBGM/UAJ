#pragma once
#include "GameState.h"
#include "Texture.h"
#include <string>

//callbacks para el menu de pausa
class PauseMenu: public GameState
{
private:

public:
	//constructor
	PauseMenu(App* app) : GameState(app) {init();};
	//destructor
	~PauseMenu() {}

	//method overrided from GameState where we create the objects that we use
	void init() override;
	void handleInput() override;
	
	//callbacks for the buttons
	//continue playing
	static void Resume(App* app);
	//go to main menu
	static void GoMainMenu(App* app);
	//show the controls
	static void ShowMeYourMoves(App* app);
	//go to options state
	static void GoOptions(App* app);
};

