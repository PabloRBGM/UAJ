#pragma once
#include "DestroyAtTime.h"
class FollowPlayer : public DestroyAtTime
{
public:
	FollowPlayer(double damage, int time, int hitstun, Vector2D knockback, bool guardbreaker, int id, Entity* e, bool mHit = false) :
		DestroyAtTime(damage, time, hitstun, knockback, guardbreaker, id, e, mHit) {
	}
	//virtual void onHit(b2Fixture* other) {
	//	if (!multiHit_) {	//we can do sth with the damage to stop the hitbox from doing constant damage to do it at some frames
	//		entity_->getComponent<PhysicsTransform>(ecs::Transform)->changeMask(entity_->getState()->NONE);
	//	}
	//	//else damaged controlled by the 
	//}

	virtual void update() {
		PhysicsTransform* pt= entity_->getComponent<PhysicsTransform>(ecs::Transform);
		PhysicsTransform* ptPlayer;
	
		if (id_ == 0) {
			ptPlayer= entity_->getApp()->getStateMachine()->getCurrentState()->getEntityManager().getHandler(ecs::Player1)
				->getComponent<PhysicsTransform>(ecs::Transform);
		}
		else {
			ptPlayer = entity_->getApp()->getStateMachine()->getCurrentState()->getEntityManager().getHandler(ecs::Player2)
				->getComponent<PhysicsTransform>(ecs::Transform);
		}
		if (oldPos.getX() != ptPlayer->getPosition().getX()) {
			pt->setSpeed(ptPlayer->getSpeed());

		}
		else {
			pt->setSpeed(Vector2D(0, 0));
		}
		
		oldPos = ptPlayer->getPosition();


		
		DestroyAtTime::update();

	}
	virtual ~FollowPlayer() {}
protected: 
	Vector2D oldPos= Vector2D(0, 0);
};

