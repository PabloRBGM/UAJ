#include "GameManager.h"
#include "GameStateMachine.h"
#include "App.h"

#include "GameState.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "ControlsMenu.h"
#include "Fight.h"
#include "OptionsMenu.h"
#include "Training.h"
#include "Entity.h"
#include "CharacterSelection.h"
#include "KeyboardHID.h"
#include "GamepadHID.h"
#include "InventorySelection.h"
#include "AbilitySelection.h"
#include "SkillSelection.h"
#include "EndMenu.h"
#include "InventorySelection.h"
#include "AIGameState.h"
#include "ArcadeEndMenu.h"
GameManager::GameManager(App* app) : app_(app)
{
	app_->getStateMachine()->pushState(new MainMenu(app_));
	resetCharacters();

	// TODO: Move this elsewhere
	switch (app_->getInputManager()->NumGamepadConnected())
	{
	case 0:	player1_.hid = new KeyboardHID(app_->getInputManager());
		player2_.hid = new KeyboardHID(app_->getInputManager());//keyboard too
		break;
	case 1:
		player1_.hid = new KeyboardHID(app_->getInputManager());
		player2_.hid = new GamepadHID(app_->getInputManager(), 0);
		break;
	case 2:
		player1_.hid = new GamepadHID(app_->getInputManager(), 0);
		player2_.hid = new GamepadHID(app_->getInputManager(), 1);

		break;
	}
	

	
	//player1_.hid = new KeyboardHID(app_->getInputManager());
	//player1_.hid = new GamepadHID(app_->getInputManager(),0);
	
	//player1_.character = F10R;
	player1_.character = F10R;

	//player2_.hid = new KeyboardHID(app_->getInputManager());//keyboard too
	//player2_.hid = new GamepadHID(app_->getInputManager(), 0);
	player2_.character = F10R;
}

void GameManager::handleInput()
{
	player1_.hid->updateInput();
	player2_.hid->updateInput();
}

void GameManager::pressedStart()
{
	GameState* curState = app_->getStateMachine()->getCurrentState();
	if (dynamic_cast<MainMenu*>(curState)) { 
		app_->Exit(); 
	}

	else if (dynamic_cast<PauseMenu*>(curState)
		|| dynamic_cast<ControlsMenu*>(curState)
		|| dynamic_cast<OptionsMenu*>(curState)
		|| dynamic_cast<CharacterSelection*>(curState)) app_->getStateMachine()->popState();

	else if (dynamic_cast<Fight*>(curState)
		|| dynamic_cast<Training*>(curState)
		|| dynamic_cast<SkillSelection*>(curState)
		|| dynamic_cast<InventorySelection*>(curState)
		|| dynamic_cast<AIGameState*>(curState))
		app_->getStateMachine()->pushState(new PauseMenu(app_));
}

void GameManager::playerLost(int player)
{
	GameStateMachine* stateMachine = app_->getStateMachine();
	switch (player)
	{
	case -1:
		break;
	case 0:
		++playerRrounds_;
		break;
	case 1:
		++playerLrounds_;
		break;
	default:
		break;
	}
	if (((totalRounds_ / 2) < playerLrounds_) || ((totalRounds_ / 2) < playerRrounds_)) {
		int winner;
		//wins player1
 		if(playerLrounds_>playerRrounds_)
			winner=0;
		else winner=1;
		ResetRounds();
		GoToEndMenu(winner);
	}
	else {
		stateMachine->popState();
		stateMachine->pushState(new Training(app_));
		++currentRound_;
	}

}

void GameManager::AIWin(){
	//ir al menu donde se muestra la puntuacion
	//GoToEndMenu(1);
	app_->getStateMachine()->pushState(new ArcadeEndMenu(app_, playerLrounds_));

	//GoBackToMain();
}

void GameManager::ResetRounds()
{
	currentRound_ = 0;
	playerLrounds_ = 0;
	playerRrounds_ = 0;
}

//winner = 0; player1 wins
//winner = 1; player2 wins
void GameManager::trainingEnded(int winner)
{
	GameStateMachine* stateMachine = app_->getStateMachine();
	cout << "Player " << winner + 1 << " wins the training!" << endl;
	// Remove the current training mode
	stateMachine->popState();
	stateMachine->pushState(new SkillSelection(app_, winner + 1));
}


void GameManager::resetCharacters()
{
	player1_.character = F10R;
	player1_.abilities.clear();
	player1_.ability1Index = player1_.ability2Index = 0;

	player2_.character = F10R;
	player2_.abilities.clear();
	player2_.ability1Index = player2_.ability2Index = 0;
}

void GameManager::GoBackToMain()
{
	resetCharacters();
	ResetRounds();
	GameState* currState = app_->getStateMachine()->getCurrentState();
	while (dynamic_cast<MainMenu*>(currState) == nullptr) {
		app_->getStateMachine()->popState();
		currState = app_->getStateMachine()->getCurrentState();
	}
}

void GameManager::GoToEndMenu(int winner) {


	resetCharacters();
	ResetRounds();
	GameState* currState = app_->getStateMachine()->getCurrentState();
	while (dynamic_cast<MainMenu*>(currState) == nullptr) {
		app_->getStateMachine()->popState();
		currState = app_->getStateMachine()->getCurrentState();
	}
	app_->getStateMachine()->pushState(new EndMenu(app_, winner));

}
