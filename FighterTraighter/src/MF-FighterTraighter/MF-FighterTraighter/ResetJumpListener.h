#pragma once
#include "Box2D/Box2D.h"
#include "PlayerState.h"
#include "CharacterAttacks.h"
#include "PlayerController.h"
#include "HitboxData.h"
//Handles collisions
//overlaps and kinematic interactions are handled 
//by the gameState hitbox system
class ResetJumpListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact) override {
	// if 1st fixture is the player, and 2nd fixture is the floor
		void* v_data = contact->GetFixtureA()->GetUserData();
		//if the fixture has some data
		if (v_data) {
			//if it has, it has to be a UserData class/subClass
			UserData* data = static_cast<UserData*>(v_data);

			if (data != nullptr) {
				PlayerState* currState = data->entity_->getComponent<PlayerState>(ecs::PlayerState);
				//if the entity is a player, handles the its landing
				if (currState != nullptr
				&& contact->GetFixtureB()->GetFilterData().categoryBits == 1	//if it collides with boundary (floor)
				&& currState->isAirborne()
				&& contact->GetFixtureA()->GetBody()->GetLinearVelocity().y >= 0) {
					data->entity_->getComponent<CharacterAttacks>(ecs::CharacterAttacks)->interruptAttack();
					currState->goLanding(11 + (currState->getHoldingFrames()) * 0.8);

				}
				
			}
		}
		//the same but with the other object
		v_data = contact->GetFixtureB()->GetUserData();
		if (v_data) {
			//if it has, it has to be a UserData subClass
			UserData* data = static_cast<UserData*>(v_data);
			//if its the player, it is an EntityData
			if (data != nullptr) {
				PlayerState* currState = data->entity_->getComponent<PlayerState>(ecs::PlayerState);
				//if the entity is a player, handles the its landing
				if (currState != nullptr
					&& contact->GetFixtureA()->GetFilterData().categoryBits == 1	//if it collides with boundary (floor)
					&& currState->isAirborne()
					&& contact->GetFixtureB()->GetBody()->GetLinearVelocity().y >= 0) {
					data->entity_->getComponent<CharacterAttacks>(ecs::CharacterAttacks)->interruptAttack();
					currState->goLanding(11 + (currState->getHoldingFrames()) * 0.8);

				}
				
			}
		}
	}


	/*void EndContact(b2Contact* contact) override {

	}*/
	

};

