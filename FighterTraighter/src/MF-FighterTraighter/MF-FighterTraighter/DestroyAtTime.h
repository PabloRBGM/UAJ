#pragma once
#include "HitboxData.h"
#include "PhysicsTransform.h"

class DestroyAtTime : public HitboxData
{
public:
	DestroyAtTime(double damage, int time, int hitstun, Vector2D knockback, bool guardbreaker, int id, Entity* e, bool mHit = false) :
		HitboxData(damage, time, hitstun, knockback, guardbreaker, id, e, mHit) {
	}
	virtual void onHit(b2Fixture* other) {
		if(!multiHit_){	//we can do sth with the damage to stop the hitbox from doing constant damage to do it at some frames
			entity_->getComponent<PhysicsTransform>(ecs::Transform)->changeMask(entity_->getState()->NONE);
		}
		//else damaged controlled by the 
	}

	virtual void update() {
		HitboxData::update();
		if (destroy_)	//destroy it when his time is 0, hitbox died, we destroy the entity too
			entity_->getState()->getEntityManager().removeEntity(entity_);
	}
	virtual ~DestroyAtTime() {}
};

