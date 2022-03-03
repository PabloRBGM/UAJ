#pragma once
#include "GameState.h"
#include "GameManager.h"

class AbilitySelection:public GameState
{
public:
	AbilitySelection(App* app, GameManager::PlayerInfo* pWin_) : GameState(app), pWin(pWin_) { init(); };
	~AbilitySelection() {};
	void init() override;
private:
	GameManager::PlayerInfo* pWin;
};

