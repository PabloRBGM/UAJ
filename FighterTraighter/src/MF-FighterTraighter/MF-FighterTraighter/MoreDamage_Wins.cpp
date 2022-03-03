#include "MoreDamage_Wins.h"
#include "Health.h"
#include "HitboxData.h"
#include "Bullet.h"
#include "TrainingController.h"

void MoreDamage_Wins::onHit(b2Fixture* other)
{
	HitboxData* other_data = static_cast<HitboxData*>(other->GetUserData());
	PlayerData* player = other_data->entity_->getComponent<PlayerData>(ecs::PlayerData);
	int playerId = -1;
	if (player != nullptr) 
		playerId = other_data->entity_->getComponent<PlayerData>(ecs::PlayerData)->getPlayerNumber();
	else
		playerId = other_data->entity_->getComponent<Bullet>(ecs::Bullet)->getPlayerNumber();
	if (playerId == 0)
		p1_damage += other_data->damage_;
	else
		p2_damage += other_data->damage_;
	//Damage
	Health* h = entity_->getComponent<Health>(ecs::Health);
	h->LoseLife(other_data->damage_);
	// Punching Bag dies
	if (h->getHealth() == 0) {
		// he died
		
		entity_->getState()->getEntityManager().getHandler(ecs::Controller)->getComponent<TrainingController>(ecs::TrainingController)->PlayerWins(computeWinner());

		//entity_->getApp()->getGameManager()->trainingEnded(computeWinner());
	}
}

//If anybody hits the punching bag, the winner will be choosed randomly
int MoreDamage_Wins::timeout_Winner() {	
	return computeWinner();
}

int MoreDamage_Wins::computeWinner() {
	int winner = 0;
	if (p1_damage == p2_damage)											
		winner = entity_->getApp()->getRandGen()->nextInt(0, 2);
	else if (p2_damage > p1_damage)
		winner = 1;
	return winner;
}