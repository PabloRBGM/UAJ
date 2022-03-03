#pragma once
#include "Component.h"
#include "PhysicsTransform.h"
#include "UITransform.h"
#include "TextComponent.h"
#include "UITimer.h"

class SacoManager : public Component
{
public:

	enum PunchingBagInteraction {
		LAST_HIT,
		MORE_DAMAGE,
		_last_interaction
	};
	//constructor
	SacoManager(int timeLimit) : Component(ecs::SacoManager), timeLimit_(timeLimit) {};
	
	//destructor
	~SacoManager() {};
	
	int getTimeLimit() {
		return timeLimit_;
	}
	string getInfoText() {
		return infoText;
	}

	void startTimer();
	//method overrided from Component
	virtual void init() override;
	virtual void update() override;
private:
	PhysicsTransform* transform_ = nullptr;
	string infoText = "";
	int timeLimit_;
	int startTime_=0;
	int currTime_ = 0;
	bool timerOn = false;

	static int rndInter;
};

