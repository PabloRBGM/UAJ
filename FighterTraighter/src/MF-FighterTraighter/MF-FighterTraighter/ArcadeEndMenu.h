#pragma once
#include "GameState.h"
#include "Texture.h"
#include <vector>
class App;

class ArcadeEndMenu : public GameState
{
public:
	//constructor
	ArcadeEndMenu(App* app, int numRound);
	//destructor
	virtual ~ArcadeEndMenu();

	//methods overrided from GameState where we create the entitys
	void init() override;
	void handleInput() override;

	//Callbacks for the buttons

	static void GoMainMenu(App* app);
protected:
	int numRound_;

};

