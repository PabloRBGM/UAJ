#include "PauseMenu.h"
#include "InputManager.h"
#include "MainMenu.h"
#include "OptionsMenu.h"

#include "Entity.h"

#include "RenderImage.h"
#include "Transform.h"
#include "Button.h"
#include "NavigationController.h"

#include "App.h"

#include "UIFactory.h"
#include "RenderAnimation.h"
#include "UITransform.h"

void PauseMenu::init()
{
	app_->getAudioMngr()->stopMusic();
	GameState::init();



#pragma region Background
	// Background
	Entity* bg = entManager_.addEntity();
	bg->addComponent<Transform>(Vector2D(), Vector2D(), app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h, 0);
	bg->addComponent<RenderAnimation>(app_->getAssetsManager()->getTexture(AssetsManager::BackgroundFight), 20);



	// Tint
	Entity* tint = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Tint),
		Vector2D(),
		Vector2D(),
		Vector2D(),
		app_->getWindowManager()->getCurResolution().h, app_->getWindowManager()->getCurResolution().h, 0);
#pragma endregion



	// Position variables
	const double leftOffset = 100;
	const double buttonInitPos = -160;
	const double buttonSeparation = 115;
	const double textOffset = 5;
	const double textSize = 85;
	const double buttonHeight = 100;



	// Logo
	Entity* logo = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Logo),
		Vector2D(leftOffset, 160),
		Vector2D(0, 0),
		Vector2D(0, 91 * 1.5 / 2),
		320 * 1.5, 91 * 1.5, 0);



	// Cool text
	UIFactory::createText(app_, this, 
		Vector2D(), 
		Vector2D(),
		Vector2D(), 
		app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), "Game is paused!", 80, TextComponent::Left, 500, 300, 9000);


	// Continue button
	std::tuple<Entity*, Entity*> continue_button = UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Button),
		app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), 
		Vector2D(leftOffset, buttonInitPos),
		Vector2D(0, app_->getWindowManager()->getCurResolution().h / 2),
		Vector2D(0, buttonHeight / 2),
		410, buttonHeight, 0, nullptr, Resume, "Continue", textSize);
	std::get<1>(continue_button)->getComponent<UITransform>(ecs::Transform)->setPosition(leftOffset + 35, buttonInitPos + textOffset);



	// Menu button
	std::tuple<Entity*, Entity*> menu_button = UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Button),
		app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), 
		Vector2D(leftOffset, buttonInitPos + buttonSeparation),
		Vector2D(0, app_->getWindowManager()->getCurResolution().h / 2),
		Vector2D(0, buttonHeight / 2),
		510, buttonHeight, 0, nullptr, GoMainMenu, "Go to menu", textSize);
	std::get<1>(menu_button)->getComponent<UITransform>(ecs::Transform)->setPosition(leftOffset + 35, buttonInitPos + buttonSeparation + textOffset);



	// Not implemented
	/*std::tuple<Entity*, Entity*> controls_button = UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Button),
		app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), Vector2D(100, 50),
		Vector2D(0, app_->getWindowManager()->getCurResolution().h / 2),
		Vector2D(0, 50),
		400, 100, 0, nullptr, ShowMeYourMoves, "Controls", 100);*/



	// Options button
	std::tuple<Entity*, Entity*> options_button = UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Button),
		app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), 
		Vector2D(leftOffset, buttonInitPos + buttonSeparation * 2),
		Vector2D(0, app_->getWindowManager()->getCurResolution().h / 2),
		Vector2D(0, buttonHeight / 2),
		370, buttonHeight, 0, nullptr, GoOptions, "Options", textSize);
	std::get<1>(options_button)->getComponent<UITransform>(ecs::Transform)->setPosition(leftOffset + 35, buttonInitPos + buttonSeparation * 2 + textOffset);




	// Navigation
	Entity* navEnt = entManager_.addEntity();
	NavigationController* nav = navEnt->addComponent<NavigationController>(1, 3);
	nav->SetElementInPos(std::get<0>(continue_button)->getComponent<UIElement>(ecs::UIElement), 0, 0);
	nav->SetElementInPos(std::get<0>(menu_button)->getComponent<UIElement>(ecs::UIElement), 0, 1);
	//nav->SetElementInPos(std::get<0>(controls_button)->getComponent<UIElement>(ecs::UIElement), 0, 2);
	nav->SetElementInPos(std::get<0>(options_button)->getComponent<UIElement>(ecs::UIElement), 0, 2);



	app_->getAudioMngr()->playMusic(app_->getAssetsManager()->getMusic(AssetsManager::MENU_OPCIONES), true);
}

void PauseMenu::handleInput()
{
	if (app_->getInputManager()->pressedStart()) {
		app_->getAudioMngr()->stopMusic();
		app_->getAudioMngr()->playMusic(app_->getAssetsManager()->getMusic(AssetsManager::FIGHT_1), true);
		app_->getGameManager()->pressedStart();
	}
	else
		GameState::handleInput();
}

void PauseMenu::Resume(App* app)
{
	app->getAudioMngr()->stopMusic();
	app->getAudioMngr()->playMusic(app->getAssetsManager()->getMusic(AssetsManager::FIGHT_1), true);
	app->getStateMachine()->popState();
}

void PauseMenu::GoMainMenu(App* app)
{
	app->getAudioMngr()->playMusic(app->getAssetsManager()->getMusic(AssetsManager::MENU_PRINCIPAL), true);
	app->getGameManager()->GoBackToMain();

}

void PauseMenu::ShowMeYourMoves(App* app)
{
#ifdef _DEBUG
	std::cout << "No implementado de momento" << endl;
#endif 
}

void PauseMenu::GoOptions(App* app)
{
	app->getStateMachine()->pushState(new OptionsMenu(app));
}
