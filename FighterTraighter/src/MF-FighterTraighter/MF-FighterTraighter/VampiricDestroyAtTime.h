#pragma once
#include "DestroyAtTime.h"
#include "Health.h"

class VampiricDestroyAtTime : public DestroyAtTime
{
public:
	VampiricDestroyAtTime(double damage, int time, int hitstun, Vector2D knockback, bool guardbreaker, int id, Entity* e, double healAmount, bool mHit = false) :
		DestroyAtTime(damage, time, hitstun, knockback, guardbreaker, id, e, mHit), healAmount_(healAmount) {
	}
	virtual void onHit(b2Fixture* other) {
		DestroyAtTime::onHit(other);
		UserData* data = static_cast<UserData*>(other->GetUserData());
		if (data) {
			if (data->entity_ == data->entity_->getState()->getEntityManager().getHandler(ecs::Player1)) {
				Health* playerHealth = data->entity_->getState()->getEntityManager().getHandler(ecs::Player2)->getComponent<Health>(ecs::Health);
				playerHealth->GainLife((playerHealth->getMaxHealth() - playerHealth->getHealth()) * healAmount_);

				PhysicsTransform* phTr = data->entity_->getComponent<PhysicsTransform>(ecs::Transform);
				int width = 250;
				int projX = (phTr->getWidth() / 4);
				Vector2D pos = Vector2D(projX, 0);

				data->entity_->getState()->getEntityManager().getHandler(ecs::Player2)->getComponent<PlayerParticleSystem>(ecs::PlayerParticleSystem)->addNewParticle(data->entity_->getApp()->getAssetsManager()->getTexture(AssetsManager::Vs2), 
					pos, Vector2D(width, 500), 35, PlayerParticleSystem::DeletionMethod::None);
			}
			else if(data){
				Health* playerHealth = data->entity_->getState()->getEntityManager().getHandler(ecs::Player1)->getComponent<Health>(ecs::Health);
				playerHealth->GainLife((playerHealth->getMaxHealth() - playerHealth->getHealth()) * healAmount_);

				PhysicsTransform* phTr = data->entity_->getComponent<PhysicsTransform>(ecs::Transform);
				int width = 250;
				int projX = (phTr->getWidth() / 4);
				Vector2D pos = Vector2D(projX, 0);

				data->entity_->getState()->getEntityManager().getHandler(ecs::Player1)->getComponent<PlayerParticleSystem>(ecs::PlayerParticleSystem)->addNewParticle(data->entity_->getApp()->getAssetsManager()->getTexture(AssetsManager::Vs2),
					pos, Vector2D(width, 500), 35, PlayerParticleSystem::DeletionMethod::None);
			}
		}
	}
	virtual ~VampiricDestroyAtTime() {}
private:
	double healAmount_;
};