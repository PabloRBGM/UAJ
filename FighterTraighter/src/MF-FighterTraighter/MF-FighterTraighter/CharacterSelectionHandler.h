#pragma once
#include "Component.h"
#include "CharacterSelectionLogic.h"
class CharacterSelectionHandler :
	public Component
{
public:
	
	CharacterSelectionHandler(Entity* j1, Entity* j2, int endTimer = 60): Component(ecs::CharacterSelectionHandler), log1(j1), log2(j2), ent(nullptr), goTimer(endTimer){}
	virtual ~CharacterSelectionHandler() { }
	void init() override;
	void update() override;
private:
	bool j1_ = false, j2_ = false;

	Entity* log1;
	Entity* log2;
	Entity* ent;

	int goTimer = 0;
};

