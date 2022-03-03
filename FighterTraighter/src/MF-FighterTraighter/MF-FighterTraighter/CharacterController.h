#pragma once
#include "Component.h"
#include "PhysicsTransform.h"
#include "PlayerState.h"
class CharacterController :
	public Component
{
public:
	CharacterController(float jImpulse, double speed) : Component(ecs::CharacterController), jumpImpulse(jImpulse), movSpeed(speed) {}
	virtual ~CharacterController() {}

	void init() override;

	void TryStopCrouch(PlayerState* currState);
	void TryStopGuarding(PlayerState* currState);
	void TryStopMoving(PlayerState* currState, Vector2D& speed);
	void TryMovingRight(PlayerState* currState, Vector2D& speed);
	void TryMovingLeft(PlayerState* currState, Vector2D& speed);
	void TryCrouching(PlayerState* currState, Vector2D& speed);
	void TryJumping(PlayerState* currState);
	void TryGuarding(PlayerState* currState, Vector2D& speed);

	virtual void crouch();
	virtual void uncrouch();
	virtual void jump();

	float getJumpImpulse() { return jumpImpulse; }
	double getMovSpeed() { return movSpeed; }

	
	inline void setDisabled(bool d) { disabled_ = d; }
protected:
	PhysicsTransform* transform_ = nullptr;
	float jumpImpulse = 0;
	double movSpeed = 1;

	bool disabled_ = false;
};

