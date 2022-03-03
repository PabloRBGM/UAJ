#pragma once
#include "GameState.h"
#include "Texture.h"
#include <vector>
class App;

class MainMenu : public GameState
{
public:
	//constructor
	MainMenu(App* app);
	//destructor
	virtual ~MainMenu();

	//methods overrided from GameState where we create the entitys
	void init() override;
	void handleInput() override;

	//Callbacks for the buttons
	//1 player mode vs AI
	static void GoPvP(App* app);
	//1vs1 mode
	static void GoVsAI(App* app);
	//options state to change resolution, volume or brightness
	static void GoOptions(App* app);
	//quit the game
	static void Leave(App* app);
};
