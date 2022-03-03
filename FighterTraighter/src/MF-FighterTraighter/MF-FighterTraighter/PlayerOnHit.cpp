#include "PlayerOnHit.h"
#include "Health.h"
#include "PhysicsTransform.h"
#include "PlayerState.h"
#include "HitboxData.h"
#include "PlayerAttacks.h"
#include "PlayerController.h"
#include "MkWH00PData.h"
#include "PlayerParticleSystem.h"
#include "PlayerData.h"
void PlayerOnHit::onHit(b2Fixture* fixture)
{
	HitboxData* hBox_data = static_cast<HitboxData*>(fixture->GetUserData());

	//cout << "Hago " << hBox_data->damage_ << " de damage en PlayerOnHit" << endl;
	PhysicsTransform* pT = entity_->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerState* currState = entity_->getComponent<PlayerState>(ecs::PlayerState);
	PlayerData* pD = entity_->getComponent<PlayerData>(ecs::PlayerData);
	Health* helth = entity_->getComponent<Health>(ecs::Health);
	double startHealth = helth->getHealth();

	PlayerParticleSystem* pSystem = entity_->getComponent<PlayerParticleSystem>(ecs::PlayerParticleSystem);
	if (!currState->isProtected()) {
		if (!hBox_data->guardBreaker_) {
			if (currState->isAttacking() && !hBox_data->multiHit_) entity_->getComponent<PlayerAttacks>(ecs::CharacterAttacks)->interruptAttack();
			if (currState->isCrouch() && !hBox_data->multiHit_) entity_->getComponent<PlayerController>(ecs::CharacterController)->uncrouch();
			if (hBox_data->doesDamage()) {
				helth->LoseLife(hBox_data->damage_);
				//pD->getPlayerNumber()
				//entity_->getApp()->getAudioMngr()->playSFX(entity_->getApp()->getAssetsManager()->getSFX(AssetsManager::MKWOP_1), false);
				entity_->getApp()->getAudioMngr()->playSFX(pD->getDmgSound(), false);
				if (!hBox_data->guardBreaker_ && !hBox_data->multiHit_) {//if isnt a guardBreaker go to hitstun
					if (hBox_data->knockBack_.getY() >= 0)	//vertical knockback, goes to airborne hitstun
						currState->goHitsun(hBox_data->hitstun_);
					else
						currState->goHitstunAirborne();
				}

				pT->getBody()->ApplyLinearImpulse(b2Vec2(hBox_data->knockBack_.getX(), hBox_data->knockBack_.getY()), pT->getBody()->GetWorldCenter(), true);
			}
		}
#ifdef _DEBUG
		cout << "Hago X:" << hBox_data->knockBack_.getX() << " Y: " << hBox_data->knockBack_.getY() << endl;
#endif
	}
	else {
		if (hBox_data->guardBreaker_) {
			currState->goHitsun(hBox_data->hitstun_);
			helth->LoseLife(hBox_data->damage_ );
			pT->getBody()->ApplyLinearImpulse(b2Vec2(hBox_data->knockBack_.getX(), hBox_data->knockBack_.getY()), pT->getBody()->GetWorldCenter(), true);

		}
		else {		
			currState->goGuardingStun(hBox_data->hitstun_ * 0.75);
			helth->LoseLife(hBox_data->damage_ * 0.1);
			pT->getBody()->ApplyLinearImpulse(b2Vec2((hBox_data->knockBack_.getX() + hBox_data->knockBack_.getX()) * 0.015, 0), pT->getBody()->GetWorldCenter(), true);
		}
#ifdef _DEBUG
		cout << "He bloqueado dano pero estoy en hitstun" << endl;
#endif

	}

	if (startHealth > helth->getHealth()) {
		SDL_Delay((startHealth - helth->getHealth()) * 5);
	}

	// he died
	if (helth->getHealth() == 0) {
		entity_->getState()->getEntityManager().getHandler(ecs::Controller)->getComponent<FightController>(ecs::FightController)->PlayerLost(entity_->getComponent<PlayerData>(ecs::PlayerData)->getPlayerNumber());
		currState->goHitsun(600);
	}

	pSystem->removeDeletionMethodParticles(PlayerParticleSystem::DeletionMethod::OnHit);
}

