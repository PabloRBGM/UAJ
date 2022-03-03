#pragma once
#include "CharacterController.h"
class AILogic;
class AIController :
	public CharacterController
{
public:
	AIController(float jImpulse, double speed) : CharacterController(jImpulse, speed) {}
	virtual ~AIController();

	void init() override;
	void handleInput() override;

	virtual void jump() override;

protected:
	AILogic* logic = nullptr;
};

