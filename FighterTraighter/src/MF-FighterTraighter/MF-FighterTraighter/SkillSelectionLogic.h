#pragma once
#include "Component.h"
#include "NavigationController.h"
class SkillSelectionLogic :
	public Component
{
public:
	SkillSelectionLogic(NavigationController* nav, int player, vector<GameManager::AbilityID> v);
	~SkillSelectionLogic();
	void init() override;
	void update() override;
	void render() override;
	void handleInput() override;

private:
	Entity* ent;

	int player_;
	NavigationController* nav_;
	
	GameManager::AbilityID op;

	vector<GameManager::AbilityID> v_;

};

