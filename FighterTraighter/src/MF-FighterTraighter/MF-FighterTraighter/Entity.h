#pragma once
#include <vector>

#include "Component.h"

class Entity
{

public:
	//constructor
	Entity();
	//destructor
	~Entity();

	//add Component
	template<typename T, typename ... TArgs>
	T* addComponent(TArgs ...args);
	
	//return the component id
	template<typename T>
	T* getComponent(ecs::CmpIdType id) {
		return static_cast<T*>(componentsArray_[id]);
	}

	//check if this entity has the component id
	bool hasComponent(int id) {
		return componentsArray_[id] != nullptr;
	}
	
	//handle input of the entity= every component handle input
	void handleInput() {
		for (auto& c : components_) {
			c->handleInput();
		}
	}

	//update of the entity= every component update
	void update() {
		for (auto& c : components_) {
			c->update();
		}
	}

	//render of the entity= every component render
	void render() {
		for (auto& c : components_) {
			c->render();
		}
	}

	//return the app
	inline App* getApp() const { return app_; }
	//set the reference of the app
	inline void setApp(App* app) { app_ = app; }

	//return the state
	inline GameState* getState() const { return state_; }
	//set the reference of the state
	inline void setState(GameState* state) { state_ = state; }
private:
	App* app_=nullptr;
	std::vector<std::unique_ptr<Component>> components_;
	std::array<Component*, ecs::_LastCmptId_> componentsArray_ = {}; // to prevent the vector from resizing, and delete automatically
	GameState* state_ = nullptr;
};

template<typename T, typename ...TArgs>
inline T* Entity::addComponent(TArgs ...args)
{
	T* t(new T(std::forward<TArgs>(args)...));
	std::unique_ptr<Component> c(t);
	components_.push_back(std::move(c));
	componentsArray_[t->getID()] = t;
	t->setEntity(this);
	t->setApp(app_);
	t->setState(state_);
	t->init();
	return t;
}
