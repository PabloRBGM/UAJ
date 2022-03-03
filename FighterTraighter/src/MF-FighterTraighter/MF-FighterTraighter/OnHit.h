#pragma once
#include "Component.h"
#include "Entity.h"

class OnHit : public Component
{
public:
	OnHit() : Component(ecs::OnHit) {}
	~OnHit() {}
	//the first is the hitbox which do damage and the second is the player who receive damage
	virtual void onHit(b2Fixture* fixture) {}		//redefine in every entity that use this component

};

