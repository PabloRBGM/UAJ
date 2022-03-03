#pragma once
#include "DestroyOnHit.h"
#include "PlayerData.h"
#include "BulletGravity.h"
#include "AbilityFactory.h"

//	Use this class to make an entity fall on the ground when it hits a player, and if
//	hits the ground it will destroy itself and spawn a new entity with features
//	especified in the parameters:
//	spawnData_		-> the data that the new entity will have and use on collisions
//	spawnTexture_	-> the texture of the new entity
//	spawnEntSize_	-> the size of the new entity
class Fall_SpawnOnHit : public DestroyOnHit
{
public:
	Fall_SpawnOnHit(int damage, int time, int hitstun, Vector2D knockback, bool guardbreaker, int id, Entity* e, HitboxData* spawnData, Texture* spawnTexture, const Vector2D& sentSize, bool mHit = false, bool render = false) :
		DestroyOnHit(damage, time, hitstun, knockback, guardbreaker, id, e, mHit), spawnData_(spawnData), spawnTex_(spawnTexture), spawnEntSize_(sentSize), render_(render) {}
	virtual void onHit(b2Fixture* other) {
		UserData* data = static_cast<UserData*>(other->GetUserData());
		if (data) {
			if (data->entity_->getComponent<PlayerData>(ecs::PlayerData)){	//other is player
				BulletGravity* bullet = entity_->getComponent<BulletGravity>(ecs::Bullet);
				//phTr->setSpeed(Vector2D(0, phTr->getSpeed().getY()));
				bullet->changeSpeed(Vector2D(0,bullet->getSpeed().getY()));
				entity_->getComponent<PhysicsTransform>(ecs::Transform)->changeMask(entity_->getState()->BOUNDARY);

			}
			else {	//collision with the floor(BOUNDARY)
				PhysicsTransform* pT = entity_->getComponent<PhysicsTransform>(ecs::Transform);
				uint16 mask;
				if (spawnData_ != nullptr) {
					if (spawnData_->id_ == 0) {
						mask = entity_->getState()->PLAYER_2;
					}
					else {
						mask = entity_->getState()->PLAYER_1;
					}
					Vector2D newPos = pT->getPosition();
					newPos.set(newPos.getX() + (0.5 * pT->getWidth()), newPos.getY() + (0.5 * pT->getHeight()));	//put the new entity on the ground
					Entity* smoke = AbilityFactory::instanceEntitywHitbox(spawnData_->entity_, spawnEntSize_.getX(), spawnEntSize_.getY(), newPos, Vector2D(0, 0), mask, spawnData_->entity_->getState(),
						spawnData_->entity_->getApp(), spawnTex_, pT->getOrientation(),
						spawnData_, false, render_);
					smoke->getComponent<PhysicsTransform>(ecs::Transform)->getMainFixture()->SetSensor(true);
				}
				DestroyOnHit::onHit(other);
				
			}
		}
	}
	virtual ~Fall_SpawnOnHit() {}
private:
	HitboxData* spawnData_ = nullptr;
	Texture* spawnTex_ = nullptr;
	Vector2D spawnEntSize_ = Vector2D(0,0);
	bool render_ = false;
};

