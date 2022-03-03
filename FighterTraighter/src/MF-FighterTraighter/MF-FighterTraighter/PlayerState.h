#pragma once
#include "Component.h"
#include "PhysicsTransform.h"
#include "Entity.h"

class PlayerState : public Component
{
public:
	enum Status : uint8_t {
		Idle,
		Moving,
		JumpingTransition,
		Jumping,
		Crouching,
		AttackingNP,
		AttackingHP,
		AttackingNK,
		AttackingHK,
		AttackingANP,
		AttackingAHP,
		AttackingANK,
		AttackingAHK,
		Hit,
		HitAirborne,
		Landing,
		HitLading,
		//KnockedTheFuckDown,
		GuardingTransition,
		Guarding,
		GuardingStun,
		GuardingLeaving,
		Guardbreaking,
		Casting,
		Stunned,
		Dead,
	};

	PlayerState() : Component(ecs::PlayerState), playerStatus_(Idle) {};
	~PlayerState() {};

	//POSITION CHECK
	bool isGrounded() {
		return playerStatus_ != Jumping && playerStatus_ != AttackingANP && playerStatus_ != AttackingANK && playerStatus_ != AttackingAHP
			&& playerStatus_ != AttackingAHK && playerStatus_ != HitAirborne && playerStatus_ != JumpingTransition;
	};
	bool isAirborne() {
		return playerStatus_ == Jumping || playerStatus_ == HitAirborne || playerStatus_ == AttackingANP || playerStatus_ == AttackingANK || playerStatus_ == AttackingAHP
			|| playerStatus_ == AttackingAHK;
	};

	//IDLE
	void goIdle() { playerStatus_ = Idle; };
	bool isIdle() { return playerStatus_ == Idle; };

	//MOVEMENT
	bool isMoving() { return playerStatus_ == Moving; };
	bool isAbletoMove() { return playerStatus_ == Idle || playerStatus_ == Moving /*|| playerStatus_ == Jumping*/; };
	void goMoving() { playerStatus_ = Moving; };

	//CROUCHING
	void goCrouch() { playerStatus_ = Crouching; };
	bool canCrouch() { return playerStatus_ == Idle || playerStatus_ == Moving; };
	bool isCrouch() { return playerStatus_ == Crouching; };

	//ATTACKING
	bool isAttacking() {
		return playerStatus_ == AttackingNP || playerStatus_ == AttackingNK || playerStatus_ == AttackingHK || playerStatus_ == AttackingHP ||
			playerStatus_ == AttackingANP || playerStatus_ == AttackingANK || playerStatus_ == AttackingAHP || playerStatus_ == AttackingAHK ||
			playerStatus_ == Guardbreaking || playerStatus_ == Casting;
	};
	bool isAbleToAttack() { return (playerStatus_ == Idle) || (playerStatus_ == Jumping) || (playerStatus_ == Crouching) || (playerStatus_ == Moving); }; //Y si te est�s moviendo? Deber�a pararte...
	void goAttack(int attackId){
		if (playerStatus_ == Jumping) { 
			switch (attackId)
			{
			case 0:
				playerStatus_ = AttackingANP;
				break;
			case 1:
				playerStatus_ = AttackingAHP;
				break;
			case 2:
				playerStatus_ = AttackingANK;
				break;
			case 3:
				playerStatus_ = AttackingAHK;
				break;
			default:
				break;
			}
		}
		else { 
			switch (attackId)
			{
			case 0:
				playerStatus_ = AttackingNP;
				break;
			case 1:
				playerStatus_ = AttackingHP;
				break;
			case 2:
				playerStatus_ = AttackingNK;
				break;
			case 3:
				playerStatus_ = AttackingHK;
				break;
			case 4:
				playerStatus_ = Guardbreaking;
				break;
			default:
				break;
			}
		}

	}

	//ABILITIES
	void goCasting() {
		
		playerStatus_ = Casting;
		holdingFrames_ = -1;
	}
	bool isCasting() { return playerStatus_ == Casting; }

	//JUMPING
	void goJumping() { playerStatus_ = Jumping; };
	void goJumpingTrans( int frames ) { playerStatus_ = JumpingTransition; holdingFrames_ = frames; };
	bool isJumpingTrans() { return playerStatus_ == JumpingTransition; }
	bool isJumping() { return playerStatus_ == Jumping; };
	bool isJumpingOrAirAttacking() {
		return playerStatus_ == Jumping || playerStatus_ == AttackingAHP || playerStatus_ == AttackingANP || playerStatus_ == AttackingANK
			|| playerStatus_ == AttackingAHK;
	};
	bool canJump() { return playerStatus_ == Idle || playerStatus_ == Crouching || playerStatus_ == Moving; }

	//LANDING
	void goLanding(int frames) {
		playerStatus_ = Landing;
		holdingFrames_ = frames;
		Vector2D speed(0,0);

		entity_->getComponent<PhysicsTransform>(ecs::Transform)->setSpeed(speed);
		entity_->getComponent<PhysicsTransform>(ecs::Transform)->getBody()->SetLinearDamping(10);//friction
	}

	void goHitLanding(int frames) {
		playerStatus_ = HitLading;
		holdingFrames_ = frames;
		entity_->getComponent<PhysicsTransform>(ecs::Transform)->setSpeed(0, 0);
	}

	//GUARDING
	bool canGuard() {
		return playerStatus_ == Idle || playerStatus_ == Moving || playerStatus_ == Crouching;
	}
  	void goGuarding() {
		playerStatus_ = Guarding;
	}
	void goGuardingTransition(int frames) {
		playerStatus_ = GuardingTransition;
		holdingFrames_ = frames;
	}
	void goGuardingLeaving(int frames) {
		playerStatus_ = GuardingLeaving;
		holdingFrames_ = frames;
	}
	void goGuardingStun(int frames) {
		playerStatus_ = GuardingStun;
		holdingFrames_ = frames;
	}
	bool isGuarding() {
		return playerStatus_ == Guarding;
	}
	bool isGuardingTransition() {
		return playerStatus_ == GuardingTransition;
	}
	bool isGuardingLeaving() {
		return playerStatus_ == GuardingLeaving;
	}
	bool isGuardingStun() {
		return playerStatus_ == GuardingStun;
	}
	bool isProtected() {
		return playerStatus_ == Guarding || playerStatus_ == GuardingStun;
	}

	//HITSTUN
	bool isHitstun() { return playerStatus_ == Hit || playerStatus_ == HitAirborne; }
	void goHitsun(int frames) {
		entity_->getComponent<PhysicsTransform>(ecs::Transform)->setSpeed(0, 0);
		if (isGrounded()) {
			playerStatus_ = Hit;
		}
		else {
			playerStatus_ = HitAirborne;
		}
		holdingFrames_ = frames;
	}
	void goHitstunAirborne() {
		entity_->getComponent<PhysicsTransform>(ecs::Transform)->setSpeed(0, 0);
		playerStatus_ = HitAirborne;
		holdingFrames_ = -1;
		entity_->getComponent<PhysicsTransform>(ecs::Transform)->getBody()->SetLinearDamping(0);//friction

	}
	void releaseHitstun() {
		if (playerStatus_ == Hit) {
			playerStatus_ = Idle;
		}
		else {
			playerStatus_ = Jumping;
		}
	}

	//Holding frames
	int getHoldingFrames() {
		return holdingFrames_;
	}

	//Update
	virtual void update() override {
		if (holdingFrames_ > 0) {
			holdingFrames_--;
			//cout << holdingFrames_ << endl;
		}else if (holdingFrames_ == 0) {
			holdingFrames_ = -1;
			if (isGuardingTransition()) goGuarding();
			else if (isGuardingStun()) goGuarding();
			else if (isGrounded() || isGuardingLeaving()) goIdle();
			else if (isJumpingTrans()) goJumping();
			else if (isHitstun()) releaseHitstun();
			else goJumping();
		}
		//if (playerStatus_ == Jumping) std::cout << "AA";
		//if (playerStatus_ == Guarding) std::cout << "GGG" << endl;
	};

	//Animation?
	int getState() {
		return playerStatus_;
	}

private:
	Status playerStatus_;
	int holdingFrames_ = -1;
};
