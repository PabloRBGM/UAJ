#pragma once
#include "GameState.h"
#include "GameManager.h"
#include <vector>

class InventorySelection :
	public GameState
{
public:
	InventorySelection(App* app, int numPlayer=2) : GameState(app), numPlayer_(numPlayer) { init(); }
	~InventorySelection() {};
	void init() override;
	void handleInput() override;
private:
	bool checkAbility(GameManager::AbilityID newAb);
	std::vector<GameManager::AbilityID>	generatedAbs_1;

	int numPlayer_=2;

	void resolveHelpText(std::string& left, std::string& right, int player);
};

