#pragma once
#include "GameState.h"
#include "GameManager.h"
#include <vector>

class SkillSelection: public GameState
{

public:
	SkillSelection(App* app, int winner) : GameState(app), winner_(winner) { init(); }
	void init() override;
	void handleInput() override;

private:
	int winner_;

	GameManager::AbilityID	op_;
	std::vector<GameManager::AbilityID>	generatedAbs_1, generatedAbs_2;
	bool checkAbility(GameManager::AbilityID newAb, int player);
};

