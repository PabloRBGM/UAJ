#pragma once
//A class to handle bodies / fixtures userData with inheritance
#include "Box2D/Box2D.h"
#include "Entity.h"

class UserData
{
public:
	UserData(Entity* e) : entity_(e) {};
	virtual ~UserData() {}	//this doesnt destroy the entity
	virtual void onHit(b2Fixture* other) {}

	virtual void update() {}//por si acaso
	//es public por comodidad y por ahora
	Entity* entity_ = nullptr;
};

