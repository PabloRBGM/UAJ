#pragma once

#include <SDL.h>
#include "App.h"
#include "ecs.h"
class Entity;
class GameState;
class Component
{

public:
	//constructor
	Component(ecs::CmpId id);
	//destructor
	virtual ~Component();

	//set for the entity, app and state
	inline void setEntity(Entity* entity) { entity_ = entity; }
	inline void setApp(App* app) { app_ = app; }
	inline void setState(GameState* state) { state_ = state; }

	//return the ID
	ecs::CmpId getID() { return id_; }

	//methods that other components will override
	virtual void init() {} // get required pointers at runtime
	virtual void handleInput() {} // gets called before update, use for input
	virtual void update() {} // main update of the component
	virtual void render() {} // render textures


protected:
	Entity* entity_;
	App* app_;
	GameState* state_;
	ecs::CmpId id_;
};

