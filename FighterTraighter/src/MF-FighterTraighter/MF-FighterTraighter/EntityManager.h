#pragma once
#include <list>
#include <vector>
#include "ecs.h"
class App;
class Entity;
class GameState;

class EntityManager
{
public:
	//constructor
	EntityManager(App* app, GameState* state) : app_(app), state_(state) { };
	//destructor
	virtual ~EntityManager();

	//add entity to the entity list
	Entity* addEntity();
	
	//remove the entity e from the list
	void removeEntity(Entity* e);

	//deletes all the entities of the list
	void empty();
	size_t size() {
		return list_.size();
	}
	//return the list
	std::list<Entity*>& getScene();

	Entity* getHandler(ecs::HandlerIdType handler) {
		return handlers_[handler];
	}

	void setHandler(Entity* e, ecs::HandlerIdType handler) {
		handlers_[handler] = e;
	}
private:
	App* app_ = nullptr;
	GameState* state_ = nullptr;
	std::list<Entity*> list_ = std::list<Entity*>(); // list of the entities
	std::vector<Entity*> handlers_ = std::vector<Entity*>(ecs::maxHandlers); // all the important entities
};