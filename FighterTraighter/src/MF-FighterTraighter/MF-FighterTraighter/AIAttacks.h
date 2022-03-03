#pragma once
#include "CharacterAttacks.h"
#include "AILogic.h"

class AIAttacks : public CharacterAttacks {
public:
	AIAttacks(AnimationChain* highFist, AnimationChain* airHighFist, AnimationChain* lowFist, AnimationChain* airLowFist,
		AnimationChain* highKick, AnimationChain* airHighKick, AnimationChain* lowKick, AnimationChain* airLowKick, AnimationChain* testGB) :
		CharacterAttacks(highFist, airHighFist, lowFist, airLowFist, highKick, airHighKick, lowKick, airLowKick, testGB) {};
	~AIAttacks() {};
	virtual void init() override;
	virtual void handleInput();
private:
	AILogic* logic_;
};