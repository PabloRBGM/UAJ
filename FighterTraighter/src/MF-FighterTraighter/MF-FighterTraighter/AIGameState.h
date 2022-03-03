#pragma once
#include "GameState.h"
#include "App.h"
class AIGameState :
	public GameState
{
public:
	AIGameState(App* app,int round=0): GameState(app), round_(round) { init(); }
	void init() override;
	void handleInput() override;
	virtual ~AIGameState() {};
protected:
	int round_ = 0;
};

