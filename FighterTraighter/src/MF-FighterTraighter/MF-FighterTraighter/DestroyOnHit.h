#pragma once
#include "HitboxData.h"
#include "PhysicsTransform.h"
class DestroyOnHit:  public HitboxData
{
public:
	DestroyOnHit(int damage, int time, int hitstun, Vector2D knockback, bool guardbreaker, int id, Entity* e, bool mHit = false) :
		HitboxData(damage, time, hitstun, knockback, guardbreaker, id, e, mHit){}

	virtual void onHit(b2Fixture* other) {
		HitboxData::onHit(other);
		entity_->getState()->getEntityManager().removeEntity(entity_);
	}

	virtual void update() {
		HitboxData::update();
		if(destroy_)	//destroy it when his time is 0, hitbox died, we destroy the entity too
			entity_->getState()->getEntityManager().removeEntity(entity_);
	}
	virtual ~DestroyOnHit() {}
};