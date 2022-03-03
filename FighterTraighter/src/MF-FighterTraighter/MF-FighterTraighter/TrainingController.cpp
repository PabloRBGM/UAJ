#include "TrainingController.h"

#include "SacoManager.h"
#include "UITransform.h"
#include "TextComponent.h"
#include "PlayerController.h"
#include "PlayerAttacks.h"

//Gets the info from the onHit of the punching bag and shows it 
void TrainingController::init() {	
	SacoManager* sM = state_->getEntityManager().getHandler(ecs::Saco)->getComponent<SacoManager>(ecs::SacoManager);
	string startInfoTxt = sM->getInfoText();
	displayMessage(startInfoTxt);
	disablePlayers(true);
	
}


void TrainingController::update()
{
	if (showInitialMessage) {	//initial message timer
		if (ini_timer > 0) {
			--ini_timer;
		}
		else {
			ini_timer = 0;
			app_->getStateMachine()->getCurrentState()->getEntityManager().removeEntity(msgEnt);
			showInitialMessage = false;
			disablePlayers(false);
			state_->getEntityManager().getHandler(ecs::Saco)->getComponent<SacoManager>(ecs::SacoManager)->startTimer();
		}
	}
	if (playerWins_ != -1) {	//end message timer
		if (end_timer > 0) {
			--end_timer;
		}
		else {
			end_timer = 0;
			app_->getGameManager()->trainingEnded(playerWins_);
		}
	}
}

void TrainingController::PlayerWins(int playerNumber)
{
	if (playerWins_ != -1) return;

	string txt = "Player " + to_string(playerNumber == 0 ? 1 : 2) + " wins!";
	displayMessage(txt);
	disablePlayers(true);
	
	playerWins_ = playerNumber;
	end_timer = roundEndTime_;
}


void TrainingController::disablePlayers(bool mode) {
	state_->getEntityManager().getHandler(ecs::Player1)->getComponent<CharacterController>(ecs::CharacterController)->setDisabled(mode);
	state_->getEntityManager().getHandler(ecs::Player1)->getComponent<CharacterAttacks>(ecs::CharacterAttacks)->setDisabled(mode);
	state_->getEntityManager().getHandler(ecs::Player2)->getComponent<CharacterController>(ecs::CharacterController)->setDisabled(mode);
	state_->getEntityManager().getHandler(ecs::Player2)->getComponent<CharacterAttacks>(ecs::CharacterAttacks)->setDisabled(mode);
}

void TrainingController::displayMessage(string msg) {
	SDL_Rect wSize = app_->getWindowManager()->getCurResolution();
	msgEnt = state_->getEntityManager().addEntity();
	msgEnt->addComponent<UITransform>(Vector2D(), Vector2D(wSize.w / 2, wSize.h / 2), Vector2D(), Vector2D());
	msgEnt->addComponent<TextComponent>(msg, app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), 150, TextComponent::Center);
}
