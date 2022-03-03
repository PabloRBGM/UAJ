#pragma once

#include "GameState.h"
#include "Texture.h"
#include <vector>
class App;

class ControlsMenu:public GameState
{
public:
	//constructor
	ControlsMenu(App* app);
	//destructor
	virtual ~ControlsMenu();

	//methods overrided from GameState where we create the entitys
	void init() override;
	void handleInput() override;
	void initString();
	void initStringPlayer(int plynum);
	void GetPlayerCrtl(int player);
	//callback
	static void GoBack(App* app);
	static void ChangeControl(App* app, int index, int control,int player);

	std::vector<std::tuple<Entity*, Entity*> >botones;
	int index;
	string Player1[16];
	string Player2[16];
	string texto[16];
	struct Player
	{
		string predet[16];
		int control;
	};
	
	std::vector<Player>players=std::vector<Player>(2);
};

