#pragma once
#include "Component.h"
#include "AnimationChain.h"
#include <vector>
#include "PlayerState.h"
#include "PlayerData.h"
#include "HID.h"
#include "AbilitiesTimerFunction.h"
#include "PlayerParticleSystem.h"

class CharacterAttacks : public Component
{
public:
	CharacterAttacks(AnimationChain* highFist, AnimationChain* airHighFist, AnimationChain* lowFist, AnimationChain* airLowFist,
		AnimationChain* highKick, AnimationChain* airHighKick, AnimationChain* lowKick, AnimationChain* airLowKick, AnimationChain* testGB);
	virtual ~CharacterAttacks();
	virtual void init() override {};
	virtual void update() override {
		if (activeAttack_ != nullptr) {

			if (activeAttack_->update()) {
				activeAttack_->reset();
				if (!isAbility(activeAttack_) && !isMultiplierTimed) resetOneTimeMultiplier();	//This should ONLY reset OneTimeMultipliers, but I'm sure errors will end up popping up and making me look lika big doo doo head >:/
				activeAttack_ = nullptr;
				if (entity_->getComponent<PlayerState>(ecs::PlayerState)->isGrounded()) {
					entity_->getComponent<PlayerState>(ecs::PlayerState)->goIdle();
				}
				else {
					entity_->getComponent<PlayerState>(ecs::PlayerState)->goJumping();
				}
			}
			//else if (entity_->getComponent<PlayerState>(ecs::PlayerState)->isHitstun()) interruptAttack(); <-- Esto es in�til (nunca va a estar atacando y ser hitstun)
		}

		for (int i = 0; i < cooldowns.size(); ++i) {
			if (cooldowns[i] > 0) --cooldowns[i];
		}

		if (multiplierTimer_ > 0) {
			multiplierTimer_--;
		}
		else if (multiplierTimer_ == 0) {
			entity_->getComponent<PlayerData>(ecs::PlayerData)->setAttack(1);
			multiplierTimer_ = -1;
		}
	};
	virtual void handleInput() {};

	void setAbility(AnimationChain* newAbility, int index);
	void interruptAttack();
	inline void goOnCooldown(int id, int cool) {
		cooldowns[id] = cool;
		setTimeCool(id, cool);
		activeTimer(id, true);
	}
	void setTimeCool(int ind, int cool);
	void activeTimer(int ind, bool act);
	bool IsTimerActive(int ind);
	int getTimeCool(int ind);
	int getAbilityIndex();
	int getAbilityCooldown(int index) {
#ifdef _DEBUG
		//cout << cooldowns[index] <<endl; 
#endif 
		return cooldowns[index];
	}

	void setMultiplier(double mul, bool timed, int timer = -1) {
		entity_->getComponent<PlayerData>(ecs::PlayerData)->setAttack(mul);
		isMultiplierTimed = timed;
		if (timed) multiplierTimer_ = timer;
		else timer = -1;
	}

	void resetOneTimeMultiplier() {
		entity_->getComponent<PlayerData>(ecs::PlayerData)->setAttack(1);
		entity_->getComponent<PlayerParticleSystem>(ecs::PlayerParticleSystem)->removeDeletionMethodParticles(PlayerParticleSystem::DeletionMethod::OnAttack);
	}

	bool isAbility(AnimationChain* anim) {
		int i = 0;
		bool is = false;
		while (i < abilityList.size() && !is) {
			if (abilityList[i] == anim) is = true;
			++i;
		}
		return is;
	}

	inline void setDisabled(bool d) { disabled_ = d; }

protected:
	std::vector<AnimationChain*> attacksList;	//pointer to the attack that you can use
	std::vector<AnimationChain*> abilityList = std::vector<AnimationChain*>(2);	//pointer to the abilities 
	std::vector<int> cooldowns = std::vector<int>(2);
	AnimationChain* activeAttack_ = nullptr;

	int multiplierTimer_ = -1;
	bool isMultiplierTimed = false;
	int timeCool0 = 0;
	int timeCool1 = 0;
	bool actTimer0 = false;
	bool actTimer1 = false;

	bool disabled_ = false;
};