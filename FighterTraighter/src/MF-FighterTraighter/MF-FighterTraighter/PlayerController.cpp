#include "PlayerController.h"
#include "Entity.h"
#include "Vector2D.h"
#include "PlayerState.h"
#include "PhysicsTransform.h"

//constructor
PlayerController::PlayerController(HID* hid, float jImpulse, double speed) : CharacterController(jImpulse, speed), inputSt_(hid)
{
}

//destructor
PlayerController::~PlayerController()
{
}

//handle input
void PlayerController::handleInput()
{
	Vector2D speed(transform_->getSpeed());
	PlayerState* currState = entity_->getComponent<PlayerState>(ecs::PlayerState);
	InputManager* input = app_->getInputManager();

	if (!disabled_)
	{
		if (inputSt_->ButtonDown(HID::LeftTrigger) > 0)
		{
			TryGuarding(currState, speed);
		}
		else if ((inputSt_->ButtonDown(HID::LeftPad_Up) || inputSt_->AxisInput(HID::LJoyY) < -verticalDeadzone))
		{
			TryJumping(currState);
		}
		else if ((inputSt_->ButtonDown(HID::LeftPad_Down) || inputSt_->AxisInput(HID::LJoyY) > verticalDeadzone))
		{
			TryCrouching(currState, speed);
		}
		else if (inputSt_->ButtonDown(HID::LeftPad_Left) || inputSt_->AxisInput(HID::LJoyX) < 0)
		{
			TryMovingLeft(currState, speed);
		}
		else if (inputSt_->ButtonDown(HID::LeftPad_Right) || inputSt_->AxisInput(HID::LJoyX) > 0)
		{
			TryMovingRight(currState, speed);
		}
	}

	// If these keys aren't active
	if (!(inputSt_->ButtonDown(HID::LeftPad_Left) || inputSt_->AxisInput(HID::LJoyX) < 0) &&
		!(inputSt_->ButtonDown(HID::LeftPad_Right) || inputSt_->AxisInput(HID::LJoyX) > 0) &&
		!(inputSt_->ButtonDown(HID::LeftPad_Up) || inputSt_->AxisInput(HID::LJoyY) < 0)) {
		TryStopMoving(currState, speed);
	}
	if (!inputSt_->ButtonDown(HID::LeftTrigger) > 0) {
		TryStopGuarding(currState);
	}
	if (!(inputSt_->ButtonDown(HID::LeftPad_Down) || inputSt_->AxisInput(HID::LJoyY) > 0)) {
		TryStopCrouch(currState);
	}
}




//Jump depending on the player input
void PlayerController::jump() {
	//uncrouch if the player is crouching and go to the jump transition state
	PlayerState* currState = entity_->getComponent<PlayerState>(ecs::PlayerState);
	TryStopCrouch(currState);
	currState->goJumpingTrans(7);
	//control the x speed of the jump with the input 
	if (inputSt_->ButtonDown(HID::LeftPad_Left) || inputSt_->AxisInput(HID::LJoyX) < 0)
		transform_->setSpeed(Vector2D(-movSpeed, transform_->getSpeed().getY()));

	else if ((inputSt_->ButtonDown(HID::LeftPad_Right) || inputSt_->AxisInput(HID::LJoyX) > 0))
		transform_->setSpeed(Vector2D(movSpeed, transform_->getSpeed().getY()));
	transform_->getBody()->SetLinearDamping(0);//0 friction in the air
	transform_->getBody()->ApplyLinearImpulse(b2Vec2(0, jumpImpulse), transform_->getBody()->GetWorldCenter(), true);
	entity_->getApp()->getAudioMngr()->playSFX(entity_->getApp()->getAssetsManager()->getSFX(AssetsManager::SALTO), false);

}