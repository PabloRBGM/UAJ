#include "LastHit_Wins.h"
#include "Health.h"
#include "HitboxData.h"
#include "Bullet.h"
#include "TrainingController.h"

//The punching bag can only be hit by other players or projectiles 
//created by them
void LastHit_Wins::onHit(b2Fixture* other)
{
	HitboxData* other_data = static_cast<HitboxData*>(other->GetUserData());
	PlayerData* player = other_data->entity_->getComponent<PlayerData>(ecs::PlayerData);
	if(player != nullptr)
		last_hit = other_data->entity_->getComponent<PlayerData>(ecs::PlayerData)->getPlayerNumber();
	else 
		last_hit = other_data->entity_->getComponent<Bullet>(ecs::Bullet)->getPlayerNumber();
	//Damage
	Health* h = entity_->getComponent<Health>(ecs::Health);
	h->LoseLife(other_data->damage_);
	// Punching Bag dies
	if (h->getHealth() == 0) {
		entity_->getState()->getEntityManager().getHandler(ecs::Controller)->getComponent<TrainingController>(ecs::TrainingController)->PlayerWins(last_hit);
	}
}

//If anybody hits the punching bag, the winner will be choosed randomly
int LastHit_Wins::timeout_Winner() {
	if (last_hit == -1)
		return entity_->getApp()->getRandGen()->nextInt(0, 2);
	return last_hit;
}