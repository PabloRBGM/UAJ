#include "PlayerAttacks.h"
#include "PlayerController.h"
#include "UITimer.h"

PlayerAttacks::PlayerAttacks(HID* hid, AnimationChain* highFist, AnimationChain* airHighFist, AnimationChain* lowFist, AnimationChain* airLowFist, 
	AnimationChain* highKick, AnimationChain* airHighKick, AnimationChain* lowKick, AnimationChain* airLowKick, AnimationChain* testGB): inputSt_(hid),
	CharacterAttacks(highFist, airHighFist, lowFist, airLowFist, highKick, airHighKick, lowKick, airLowKick, testGB)
{
}

void PlayerAttacks::handleInput() {
	PlayerState* currState = entity_->getComponent<PlayerState>(ecs::PlayerState);
	Transform* tr = entity_->getComponent<Transform>(ecs::Transform);

	PlayerController* ctrl = entity_->getComponent<PlayerController>(ecs::CharacterController);
	if (!disabled_) {
		if (currState->isAbleToAttack()) {
			if (currState->isGrounded()) {
				if (inputSt_->ButtonPressed(HID::RightPad_Down)) {

					activeAttack_ = attacksList[0];
					if (currState->isMoving()) tr->setSpeed(0, tr->getSpeed().getY());
					else if (currState->isCrouch()) ctrl->uncrouch();
					currState->goAttack(0);
				}
				else if (inputSt_->ButtonPressed(HID::RightPad_Right)) {
					activeAttack_ = attacksList[1];
					if (currState->isMoving()) tr->setSpeed(0, tr->getSpeed().getY());
					else if (currState->isCrouch()) ctrl->uncrouch();
					currState->goAttack(1);
				}
				else if (inputSt_->ButtonPressed(HID::RightPad_Left)) {
					activeAttack_ = attacksList[2];
					if (currState->isMoving()) tr->setSpeed(0, tr->getSpeed().getY());
					else if (currState->isCrouch()) ctrl->uncrouch();
					currState->goAttack(2);
				}
				else if (inputSt_->ButtonPressed(HID::RightPad_Up)) {
					activeAttack_ = attacksList[3];
					if (currState->isMoving()) tr->setSpeed(0, tr->getSpeed().getY());
					else if (currState->isCrouch()) ctrl->uncrouch();
					currState->goAttack(3);
				}
				else if (inputSt_->ButtonPressed(HID::RightTrigger)) {
					activeAttack_ = attacksList[8];
					if (currState->isMoving()) tr->setSpeed(0, tr->getSpeed().getY());
					else if (currState->isCrouch()) ctrl->uncrouch();
					currState->goAttack(4);
				}else if (inputSt_->ButtonPressed(HID::LeftBumper)) {
					if (abilityList[0] != nullptr && cooldowns[0] == 0) {
						activeAttack_ = abilityList[0];
						tr->setSpeed(0, tr->getSpeed().getY());
						if (currState->isCrouch()) ctrl->uncrouch();
						currState->goCasting();
					}
				}		
				else if (inputSt_->ButtonPressed(HID::RightBumper)) {
					if (abilityList[1] != nullptr && cooldowns[1] == 0) {
						activeAttack_ = abilityList[1];
						tr->setSpeed(0, tr->getSpeed().getY());
						if (currState->isCrouch()) ctrl->uncrouch();
						currState->goCasting();
					}
				}
			}
			else {
				if (inputSt_->ButtonPressed(HID::RightPad_Down)) {
					activeAttack_ = attacksList[4];
					tr->setSpeed(tr->getSpeed().getX() * 0.65, tr->getSpeed().getY());
					currState->goAttack(0);
				}
				else if (inputSt_->ButtonPressed(HID::RightPad_Right)) {
					activeAttack_ = attacksList[5];
					tr->setSpeed(tr->getSpeed().getX() * 0.65, tr->getSpeed().getY());
					currState->goAttack(1);
				}
				else if (inputSt_->ButtonPressed(HID::RightPad_Left)) {
					activeAttack_ = attacksList[6];
					tr->setSpeed(tr->getSpeed().getX() * 0.65, tr->getSpeed().getY());
					currState->goAttack(2);
				}
				else if (inputSt_->ButtonPressed(HID::RightPad_Up)) {
					activeAttack_ = attacksList[7];
					tr->setSpeed(tr->getSpeed().getX() * 0.65, tr->getSpeed().getY());
					currState->goAttack(3);
				}
			}
		}
	}
}
