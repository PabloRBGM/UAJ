#include "ControlsMenu.h"

#include "Fight.h"
#include "OptionsMenu.h"
#include "Training.h"

#include "InputManager.h"

#include "Entity.h"

#include "RenderImage.h"
#include "Transform.h"
#include "Button.h"
#include "TextComponent.h"
#include "NavigationController.h"

#include "Font.h"

#include "App.h"
#include "UIFactory.h"
#include "RenderAnimation.h"

#include "KeyboardHID.h"
#include "GamepadHID.h"

ControlsMenu::ControlsMenu(App* app) : GameState(app)
{
#ifdef _DEBUG
	cout << "MovementsMenu" << endl;
#endif 
	init();
}

ControlsMenu::~ControlsMenu()
{

}

void ControlsMenu::init()
{
	GameState::init();
#ifdef _DEBUG
	cout << "init" << endl;
#endif	
	// Background
	Entity* background = entManager_.addEntity();
	background->addComponent<Transform>(Vector2D(), Vector2D(), app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h, 0);
	background->addComponent<RenderAnimation>(app_->getAssetsManager()->getTexture(AssetsManager::BackgroundFight), 20);

	tuple<Entity*, Entity*> back = UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Button), app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black),
		Vector2D(15, 10), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, 0), Vector2D(7, 0), 100, 60, 0, GoBack, nullptr, "<-", 60);
	initString();
	for (int i = 0; i < players.size(); i++)
	{
		GetPlayerCrtl(i);
		initStringPlayer(i);
	}


	Entity* nav = entManager_.addEntity();
	NavigationController* ctrl = nav->addComponent<NavigationController>(2, 17);
	ctrl->SetElementInPos(std::get<0>(back)->getComponent<UIElement>(ecs::UIElement), 0, 0);
	ctrl->SetElementInPos(std::get<0>(back)->getComponent<UIElement>(ecs::UIElement), 1, 0);
	


	for (int i = 0; i < 16; i++)
	{
		std::tuple<Entity*, Entity*> Key = UIFactory::createButtonControl(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Button),
			app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), Vector2D(500, i * 45.0 - 350),
			Vector2D(0, app_->getWindowManager()->getCurResolution().h / 2),
			Vector2D(0, 50),
			250, 50, 0, ChangeControl, players[0].predet[i], 50, TextComponent::Center, i, players[0].control,1);
		ctrl->SetElementInPos(std::get<0>(Key)->getComponent<UIElement>(ecs::UIElement), 0, i + 1);

		std::tuple<Entity*, Entity*> Button = UIFactory::createButtonControl(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Button),
			app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), Vector2D(800, i * 45.0 - 350),
			Vector2D(0, app_->getWindowManager()->getCurResolution().h / 2),
			Vector2D(0, 50),
			250, 50, 0, ChangeControl, players[1].predet[i], 50, TextComponent::Center, i, players[1].control,2);
		ctrl->SetElementInPos(std::get<0>(Button)->getComponent<UIElement>(ecs::UIElement), 1, i + 1);
	}
	Entity* keyboard = entManager_.addEntity();
	keyboard->addComponent<Transform>(Vector2D(510, 60), Vector2D(0, app_->getWindowManager()->getCurResolution().h / 2), 400, 400, 0);
	keyboard->addComponent<TextComponent>("Player One", app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), 60);

	Entity* controller = entManager_.addEntity();
	controller->addComponent<Transform>(Vector2D(775, 60), Vector2D(0, app_->getWindowManager()->getCurResolution().h / 2), 400, 400, 0);
	controller->addComponent<TextComponent>("Player Two", app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), 60);


	for (int i = 0; i < 16; i++)
	{
		Entity* text = entManager_.addEntity();
		text->addComponent<Transform>(Vector2D(60, 145.0 + i * 45), Vector2D(0, app_->getWindowManager()->getCurResolution().h / 2), 50, 50, 0);
		text->addComponent<TextComponent>(texto[i], app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), 50);
	}
}

void ControlsMenu::GoBack(App* app) {
	app->getStateMachine()->popState();

}

void ControlsMenu::ChangeControl(App* app, int index, int control,int player) {
	if (control == 0)
	{
		dynamic_cast<KeyboardHID*>(app->getGameManager()->getPlayerInfo(player).hid)->changeKey(index, app->getInputManager()->lastKey());

	}
	else
	{
		dynamic_cast<GamepadHID*>(app->getGameManager()->getPlayerInfo(player).hid)->change(index);

	}
}
//left, right, up, down, hit1, hit2, hit3, hit4, ab1, ab2, block, guardbreak

void ControlsMenu::initString()
{


	
	texto[0] = "Start";
	texto[1] = "Select";
	texto[2] = "LEFT";
	texto[3] = "UP";
	texto[4] = "RIGHT";
	texto[5] = "DOWN";
	texto[6] = "NORMAL KICK";
	texto[7] = "STRONG KICK";
	texto[8] = "NORMAL PUNCH";
	texto[9] = "STRONG PUNCH";
	texto[10] = "ABILITY ONE";
	texto[11] = "ABILITY TWO";
	texto[12] = "CLICK LEFTJOY";
	texto[13] = "CLICK RIGHTJOY";
	texto[14] = "GUARD";
	texto[15] = "GUARDBREAK";


}

void ControlsMenu::initStringPlayer(int plynum)
{

	if(players[plynum].control==1)
	{

		for (int i = 0; i < 16; i++)
		{
			players[plynum].predet[i] = dynamic_cast<GamepadHID*>(app_->getGameManager()->getPlayerInfo(plynum+1).hid)->getControl().at(i);
		}
		
	}
	else 
	{
		for (int i = 0; i < 16; i++)
		{
			players[plynum].predet[i] = SDL_GetScancodeName(dynamic_cast<KeyboardHID*>(app_->getGameManager()->getPlayerInfo(plynum+1).hid)->getkeys().at(i));
		}
	}

}

void ControlsMenu::GetPlayerCrtl(int player)
{
	if (dynamic_cast<KeyboardHID*>(app_->getGameManager()->getPlayerInfo(player+1).hid)!=nullptr)
	{
		
		players[player ].control = 0;
	}
	else 
	{
		players[player ].control = 1;

	}

}


void ControlsMenu::handleInput()
{
	if (app_->getInputManager()->pressedStart()) {

		app_->getGameManager()->pressedStart();
	}
	GameState::handleInput();
}
