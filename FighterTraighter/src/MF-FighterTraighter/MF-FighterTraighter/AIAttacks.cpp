#include "AIAttacks.h"
#include "AIController.h"

void AIAttacks::init()
{
	logic_ = entity_->getComponent<AILogic>(ecs::AILogic);
}

void AIAttacks::handleInput()
{
	PlayerState* currState = entity_->getComponent<PlayerState>(ecs::PlayerState);
	Transform* tr = entity_->getComponent<Transform>(ecs::Transform);
	AIController* ctrl = entity_->getComponent<AIController>(ecs::CharacterController);

	if (!disabled_) {
		if (currState->isAbleToAttack()) {
			if (currState->isGrounded()) {
				if (logic_->getMovingState() == AILogic::attacking) {
					int randAtt = app_->getRandGen()->nextInt(0, 6);
					if (randAtt < 4) {
						activeAttack_ = attacksList[randAtt];
						if (currState->isMoving()) tr->setSpeed(0, tr->getSpeed().getY());
						else if (currState->isCrouch()) ctrl->uncrouch();
						currState->goAttack(randAtt);
					}
					else {
						if (abilityList[randAtt - 4] != nullptr && cooldowns[randAtt - 4] == 0) {
							activeAttack_ = abilityList[randAtt - 4];
							tr->setSpeed(0, tr->getSpeed().getY());
							if (currState->isCrouch()) ctrl->uncrouch();
							currState->goCasting();
						}
					}
				}
			}
			else {
				if (logic_->getMovingState() == AILogic::attacking) {
					int randAtt = app_->getRandGen()->nextInt(0, 4);
					activeAttack_ = attacksList[randAtt + 4];
					tr->setSpeed(tr->getSpeed().getX() * 0.65, tr->getSpeed().getY());
					currState->goAttack(randAtt);
				}
			}
		}
	}
}
