#pragma once
#include "GameState.h"
#include "Texture.h"
#include <vector>
class App;

class EndMenu : public GameState
{
public:
	//constructor
	EndMenu(App* app, int playerWin);
	//destructor
	virtual ~EndMenu();

	//methods overrided from GameState where we create the entitys
	void init() override;
	void handleInput() override;

	//Callbacks for the buttons
	
	static void GoMainMenu(App* app);
private:
	int winner;
};
