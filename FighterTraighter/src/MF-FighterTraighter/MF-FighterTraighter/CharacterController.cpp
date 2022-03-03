#include "CharacterController.h"

void CharacterController::init()
{
	transform_ = entity_->getComponent<PhysicsTransform>(ecs::Transform);
}

void CharacterController::TryStopCrouch(PlayerState* currState)
{
	if (currState->isCrouch())
		uncrouch();
}

void CharacterController::TryStopGuarding(PlayerState* currState)
{
	if (currState->isGuarding())
		currState->goGuardingLeaving(14);
}

void CharacterController::TryStopMoving(PlayerState* currState, Vector2D& speed)
{
	if (currState->isMoving())
	{
		transform_->setSpeed(0, speed.getY());
		if (currState->isGrounded()) currState->goIdle();
		else { currState->goJumping(); };
	}
}

void CharacterController::TryMovingRight(PlayerState* currState, Vector2D& speed)
{
	if (currState->isAbletoMove()) {
		speed = Vector2D(movSpeed, speed.getY());
		transform_->setSpeed(speed);
		if (currState->isGrounded())
			currState->goMoving();
		else
			currState->goJumping();
	}
}

void CharacterController::TryMovingLeft(PlayerState* currState, Vector2D& speed)
{
	if (currState->isAbletoMove()) {
		speed = Vector2D(-movSpeed, speed.getY());
		transform_->setSpeed(speed);
		if (currState->isGrounded())
			currState->goMoving();
		else
			currState->goJumping();
	}
}

void CharacterController::TryCrouching(PlayerState* currState, Vector2D& speed)
{
	if (currState->canCrouch()) {
		if (currState->isMoving())
			transform_->setSpeed(0, speed.getY());
		crouch();
	}
}

void CharacterController::TryJumping(PlayerState* currState)
{
	if (currState->canJump())
	{
		jump();
	}
}

void CharacterController::TryGuarding(PlayerState* currState, Vector2D& speed)
{
	if (currState->canGuard())
	{
		if (currState->isCrouch()) uncrouch();
		else if (currState->isMoving()) transform_->setSpeed(0, speed.getY());
		if (!currState->isGuarding()) currState->goGuardingTransition(6);
	}
}

void CharacterController::crouch()
{
	entity_->getComponent<PlayerState>(ecs::PlayerState)->goCrouch();

	float height = transform_->getHeight();
	transform_->setColliderHeight(height * 0.6, Vector2D(0, height / 5));
}

void CharacterController::uncrouch()
{
	entity_->getComponent<PlayerState>(ecs::PlayerState)->goIdle();
	transform_->setColliderHeight(transform_->getHeight(), Vector2D(0, 0));
}

void CharacterController::jump()
{	

}
