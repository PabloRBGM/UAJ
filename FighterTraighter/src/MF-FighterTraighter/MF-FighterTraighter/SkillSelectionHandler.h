#pragma once
#include "Component.h"
class SkillSelectionHandler :
	public Component
{
public:
	SkillSelectionHandler(Entity* j1, Entity* j2) : Component(ecs::CharacterSelectionLogic), j1_(j1), j2_(j2) {}
	~SkillSelectionHandler() {}
	void init() override;
	void update() override;
	void render() override;
	void handleInput() override;
private:
	Entity* j1_;
	Entity* j2_;
	bool pressed_1 = false;
	bool pressed_2 = false;

	GameManager::AbilityID selectedAb;
	int winner;
};

