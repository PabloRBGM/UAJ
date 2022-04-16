#include "PlayerAttacks.h"
#include "PlayerController.h"
#include "UITimer.h"

#include "Tracker.h"
#include "AttackEvent.h"
#include "AbilityEvent.h"
#include "PlayerData.h"
#include <chrono>
#include "Fight.h"

PlayerAttacks::PlayerAttacks(HID* hid, AnimationChain* highFist, AnimationChain* airHighFist, AnimationChain* lowFist, AnimationChain* airLowFist, 
	AnimationChain* highKick, AnimationChain* airHighKick, AnimationChain* lowKick, AnimationChain* airLowKick, AnimationChain* testGB): inputSt_(hid),
	CharacterAttacks(highFist, airHighFist, lowFist, airLowFist, highKick, airHighKick, lowKick, airLowKick, testGB)
{
}

void PlayerAttacks::handleInput() {
	PlayerState* currState = entity_->getComponent<PlayerState>(ecs::PlayerState);
	Transform* tr = entity_->getComponent<Transform>(ecs::Transform);

	PlayerController* ctrl = entity_->getComponent<PlayerController>(ecs::CharacterController);
	
	int playerNum = entity_->getComponent<PlayerData>(ecs::PlayerData)->getPlayerNumber();
	bool logEvents = dynamic_cast<Fight*>(app_->getStateMachine()->getCurrentState()) != nullptr;

	if (!disabled_) {
		if (currState->isAbleToAttack()) {
			if (currState->isGrounded()) {
				if (inputSt_->ButtonPressed(HID::RightPad_Down)) {

					activeAttack_ = attacksList[0];
					if (currState->isMoving()) tr->setSpeed(0, tr->getSpeed().getY());
					else if (currState->isCrouch()) ctrl->uncrouch();
					currState->goAttack(0);

					if (logEvents) {
						TrackerEvent* even = new AttackEvent(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(),
							Characters((int)app_->getGameManager()->getPlayerInfo(playerNum + 1).character), Attacks::NormalPunch, Players(playerNum));

						Tracker::instance()->trackEvent(even);
					}
				}
				else if (inputSt_->ButtonPressed(HID::RightPad_Right)) {
					activeAttack_ = attacksList[1];
					if (currState->isMoving()) tr->setSpeed(0, tr->getSpeed().getY());
					else if (currState->isCrouch()) ctrl->uncrouch();
					currState->goAttack(1);

					if (logEvents) {
						TrackerEvent* even = new AttackEvent(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(),
							Characters((int)app_->getGameManager()->getPlayerInfo(playerNum + 1).character), Attacks::NormalKick, Players(playerNum));

						Tracker::instance()->trackEvent(even);
					}
				}
				else if (inputSt_->ButtonPressed(HID::RightPad_Left)) {
					activeAttack_ = attacksList[2];
					if (currState->isMoving()) tr->setSpeed(0, tr->getSpeed().getY());
					else if (currState->isCrouch()) ctrl->uncrouch();
					currState->goAttack(2);

					if (logEvents) {
						TrackerEvent* even = new AttackEvent(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(),
							Characters((int)app_->getGameManager()->getPlayerInfo(playerNum + 1).character), Attacks::HeavyPunch, Players(playerNum));

						Tracker::instance()->trackEvent(even);
					}
				}
				else if (inputSt_->ButtonPressed(HID::RightPad_Up)) {
					activeAttack_ = attacksList[3];
					if (currState->isMoving()) tr->setSpeed(0, tr->getSpeed().getY());
					else if (currState->isCrouch()) ctrl->uncrouch();
					currState->goAttack(3);

					if (logEvents) {
						TrackerEvent* even = new AttackEvent(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(),
							Characters((int)app_->getGameManager()->getPlayerInfo(playerNum + 1).character), Attacks::Heavykick, Players(playerNum));

						Tracker::instance()->trackEvent(even);
					}
				}
				else if (inputSt_->ButtonPressed(HID::RightTrigger)) {
					activeAttack_ = attacksList[8];
					if (currState->isMoving()) tr->setSpeed(0, tr->getSpeed().getY());
					else if (currState->isCrouch()) ctrl->uncrouch();
					currState->goAttack(4);

					if (logEvents) {
						TrackerEvent* even = new AttackEvent(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(),
							Characters((int)app_->getGameManager()->getPlayerInfo(playerNum + 1).character), Attacks::GuardBreaker, Players(playerNum));

						Tracker::instance()->trackEvent(even);
					}
				}
				else if (inputSt_->ButtonPressed(HID::LeftBumper)) {
					if (abilityList[0] != nullptr && cooldowns[0] == 0) {
						activeAttack_ = abilityList[0];
						tr->setSpeed(0, tr->getSpeed().getY());
						if (currState->isCrouch()) ctrl->uncrouch();
						currState->goCasting();

						if (logEvents) {
							TrackerEvent* even = new AbilityEvent(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(),
								Characters((int)app_->getGameManager()->getPlayerInfo(playerNum + 1).character), 
								Abilities((int)app_->getGameManager()->getPlayerInfo(playerNum + 1).abilities[0]), 
								Players(playerNum));

							Tracker::instance()->trackEvent(even);
						}
					}
				}		
				else if (inputSt_->ButtonPressed(HID::RightBumper)) {
					if (abilityList[1] != nullptr && cooldowns[1] == 0) {
						activeAttack_ = abilityList[1];
						tr->setSpeed(0, tr->getSpeed().getY());
						if (currState->isCrouch()) ctrl->uncrouch();
						currState->goCasting();

						if (logEvents) {
							TrackerEvent* even = new AbilityEvent(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(),
								Characters((int)app_->getGameManager()->getPlayerInfo(playerNum + 1).character),
								Abilities((int)app_->getGameManager()->getPlayerInfo(playerNum + 1).abilities[1]),
								Players(playerNum));

							Tracker::instance()->trackEvent(even);
						}
					}
				}
			}
			else {
				if (inputSt_->ButtonPressed(HID::RightPad_Down)) {
					activeAttack_ = attacksList[4];
					tr->setSpeed(tr->getSpeed().getX() * 0.65, tr->getSpeed().getY());
					currState->goAttack(0);

					if (logEvents) {
						TrackerEvent* even = new AttackEvent(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(),
							Characters((int)app_->getGameManager()->getPlayerInfo(playerNum + 1).character), Attacks::AirNormalPunch, Players(playerNum));

						Tracker::instance()->trackEvent(even);
					}
				}
				else if (inputSt_->ButtonPressed(HID::RightPad_Right)) {
					activeAttack_ = attacksList[5];
					tr->setSpeed(tr->getSpeed().getX() * 0.65, tr->getSpeed().getY());
					currState->goAttack(1);

					if (logEvents) {
						TrackerEvent* even = new AttackEvent(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(),
							Characters((int)app_->getGameManager()->getPlayerInfo(playerNum + 1).character), Attacks::AirNormalKick, Players(playerNum));

						Tracker::instance()->trackEvent(even);
					}
				}
				else if (inputSt_->ButtonPressed(HID::RightPad_Left)) {
					activeAttack_ = attacksList[6];
					tr->setSpeed(tr->getSpeed().getX() * 0.65, tr->getSpeed().getY());
					currState->goAttack(2);

					if (logEvents) {
						TrackerEvent* even = new AttackEvent(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(),
							Characters((int)app_->getGameManager()->getPlayerInfo(playerNum + 1).character), Attacks::AirHeavyPunch, Players(playerNum));

						Tracker::instance()->trackEvent(even);
					}
				}
				else if (inputSt_->ButtonPressed(HID::RightPad_Up)) {
					activeAttack_ = attacksList[7];
					tr->setSpeed(tr->getSpeed().getX() * 0.65, tr->getSpeed().getY());
					currState->goAttack(3);

					if (logEvents) {
						TrackerEvent* even = new AttackEvent(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(),
							Characters((int)app_->getGameManager()->getPlayerInfo(playerNum + 1).character), Attacks::AirHeavyKick, Players(playerNum));

						Tracker::instance()->trackEvent(even);
					}
				}
			}
		}
	}
}
