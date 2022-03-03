#include "AIController.h"
#include "AILogic.h"

AIController::~AIController()
{
}

void AIController::init()
{
	CharacterController::init();
	logic = entity_->getComponent<AILogic>(ecs::AILogic);
}

void AIController::handleInput()
{
	Vector2D speed(transform_->getSpeed());
	PlayerState* currState = entity_->getComponent<PlayerState>(ecs::PlayerState);

	if (logic->getMovingState() == AILogic::blocking)
	{
		TryGuarding(currState, speed);
	}
	else if (logic->getMovingState() == AILogic::jumping)
	{
		TryJumping(currState);
	}
	else if (logic->getMovingState() == AILogic::crouching)
	{
		TryCrouching(currState, speed);
	}
	else if (logic->getMovingState() == AILogic::movingLeft)
	{
		TryMovingLeft(currState, speed);
	}
	else if (logic->getMovingState() == AILogic::movingRight)
	{
		TryMovingRight(currState, speed);
	}

	// If these keys aren't active
	if (logic->getMovingState() != AILogic::movingLeft && logic->getMovingState() != AILogic::movingRight) {
		TryStopMoving(currState, speed);
	}
	if (logic->getMovingState() != AILogic::blocking) {
		TryStopGuarding(currState);
	}
	if (logic->getMovingState() != AILogic::crouching) {
		TryStopCrouch(currState);
	}
}

void AIController::jump()
{
	TryStopCrouch(entity_->getComponent<PlayerState>(ecs::PlayerState));
	transform_->getBody()->ApplyLinearImpulse(b2Vec2(0, jumpImpulse), transform_->getBody()->GetWorldCenter(), true);
	transform_->getBody()->SetLinearDamping(0);
	entity_->getComponent<PlayerState>(ecs::PlayerState)->goJumpingTrans(7);
}
