#pragma once
#include "Component.h"
#include "PlayerData.h"
class Health : public Component
{
public:

	//constructor
	Health(double health) :Component(ecs::Health), maxHealth_(health), health_(health){};
	virtual ~Health() {}
	
	// lose damage life (life-=damage) and check if life<0 to be dead
	bool LoseLife( double  damage);

	// add cuantity
	void GainLife(unsigned int cuantity);
	
	//set health_=newhealth
	void setLife(int newhealth);
	
	//return the current health(health_)
	int getLife();
	inline int getMaxHealth() { return maxHealth_; }

	double getHealth() { return health_; }

	void setMultiplier(double mul, bool timed, int timer = -1) {
		entity_->getComponent<PlayerData>(ecs::PlayerData)->setDefense(mul);
		isMultiplierTimed = timed;
		if (timed) multiplierTimer_ = timer;
		else timer = -1;
	}

	virtual void update() override {
		if (multiplierTimer_ > 0) {
			multiplierTimer_--;
		}
		else if (multiplierTimer_ == 0) {
			entity_->getComponent<PlayerData>(ecs::PlayerData)->setDefense(1);
			multiplierTimer_ = -1;
		}
	}

private:
	double health_; //current health
	int maxHealth_; //max health

	int multiplierTimer_ = -1;
	bool isMultiplierTimed = false;
};

