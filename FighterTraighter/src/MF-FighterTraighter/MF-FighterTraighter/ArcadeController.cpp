#include "ArcadeController.h"
#include "Entity.h"
#include "UITransform.h"
#include "TextComponent.h"
#include "PlayerController.h"
#include "PlayerAttacks.h"
#include "AIController.h"
#include "AIAttacks.h"
#include "AIGameState.h"
#include "InventorySelection.h"

void ArcadeController::end()
{
	if (playerLost_ != 0) {
		app_->getStateMachine()->popState();
		app_->getGameManager()->increasePlayerRounds(1);
		
		app_->getStateMachine()->pushState(new InventorySelection(app_,1));
	}
	else
		app_->getGameManager()->AIWin();

}

void ArcadeController::disablePlayers(bool mode) {
	state_->getEntityManager().getHandler(ecs::Player1)->getComponent<CharacterController>(ecs::CharacterController)->setDisabled(mode);
	state_->getEntityManager().getHandler(ecs::Player1)->getComponent<CharacterAttacks>(ecs::CharacterAttacks)->setDisabled(mode);
	state_->getEntityManager().getHandler(ecs::Player2)->getComponent<AIController>(ecs::CharacterController)->setDisabled(mode);
	state_->getEntityManager().getHandler(ecs::Player2)->getComponent<AIAttacks>(ecs::CharacterAttacks)->setDisabled(mode);
}

