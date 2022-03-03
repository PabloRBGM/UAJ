#include "MainMenu.h"
#include "InventorySelection.h"
#include "Fight.h"
#include "OptionsMenu.h"
#include "Training.h"
#include "AIGameState.h"
#include "CharacterSelection.h"
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
#include "UITransform.h"

#include "SkillSelection.h"

MainMenu::MainMenu(App* app) : GameState(app)
{
#ifdef _DEBUG
	cout << "Menu principal" << endl;
#endif 
	init();
}

MainMenu::~MainMenu()
{

}

void MainMenu::init()
{
	GameState::init();



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



	// Image
	Entity* image = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::CollageCharacters),
		Vector2D(-50, 0),
		Vector2D(app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h / 2),
		Vector2D(900, 900 / 2),
		900, 900, 0);




	// Position variables
	const double leftOffset = 100;
	const double buttonInitPos = -160;
	const double buttonSeparation = 115;
	const double textOffset = 5;
	const double textSize = 85;



	// Logo
	Entity* logo = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Logo),
		Vector2D(leftOffset, 160),
		Vector2D(0, 0),
		Vector2D(0, 91 * 1.5 / 2),
		320 * 1.5, 91 * 1.5, 0);



	// 1v1 button
	tuple < Entity*, Entity*> pvp = UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Button), app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black),
		Vector2D(leftOffset, buttonInitPos),
		Vector2D(0, app_->getWindowManager()->getCurResolution().h / 2), 
		Vector2D(0, 50),
		340, 100, 0, nullptr, GoPvP, "Versus", textSize, TextComponent::TextAlignment::Left);
	std::get<1>(pvp)->getComponent<UITransform>(ecs::Transform)->setPosition(leftOffset + 35, buttonInitPos + textOffset);


	// vsAI button
	tuple < Entity*, Entity*> arcade = UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Button), app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black),
		Vector2D(leftOffset, buttonInitPos + buttonSeparation),
		Vector2D(0, app_->getWindowManager()->getCurResolution().h / 2),
		Vector2D(0, 50),
		340, 100, 0, nullptr, GoVsAI, "Arcade", textSize, TextComponent::TextAlignment::Left);
	std::get<1>(arcade)->getComponent<UITransform>(ecs::Transform)->setPosition(leftOffset + 35, -40);



	// Options button
	tuple < Entity*, Entity*> options = UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Button), app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black),
		Vector2D(leftOffset, buttonInitPos + 2 * buttonSeparation),
		Vector2D(0, app_->getWindowManager()->getCurResolution().h / 2),
		Vector2D(0, 50),
		370, 100, 0, nullptr, GoOptions, "Options", textSize, TextComponent::TextAlignment::Left);
	std::get<1>(options)->getComponent<UITransform>(ecs::Transform)->setPosition(leftOffset + 35, buttonInitPos + 2 * buttonSeparation + textOffset);



	// Exit button
	tuple < Entity*, Entity*> exit = UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Button), app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black),
		Vector2D(leftOffset, buttonInitPos + 3 * buttonSeparation),
		Vector2D(0, app_->getWindowManager()->getCurResolution().h / 2),
		Vector2D(0, 50),
		300, 100, 0, nullptr, Leave, "Leave", textSize, TextComponent::TextAlignment::Left);
	std::get<1>(exit)->getComponent<UITransform>(ecs::Transform)->setPosition(leftOffset + 35, buttonInitPos + 3 * buttonSeparation + textOffset);


	// Navigation
	Entity* navEnt = entManager_.addEntity();
	NavigationController* nav = navEnt->addComponent<NavigationController>(1, 4);
	nav->SetElementInPos(std::get<0>(pvp)->getComponent<UIElement>(ecs::UIElement), 0, 0);
	nav->SetElementInPos(std::get<0>(arcade)->getComponent<UIElement>(ecs::UIElement), 0, 1);
	nav->SetElementInPos(std::get<0>(options)->getComponent<UIElement>(ecs::UIElement), 0, 2);
	nav->SetElementInPos(std::get<0>(exit)->getComponent<UIElement>(ecs::UIElement), 0, 3);




	app_->getAudioMngr()->playMusic(app_->getAssetsManager()->getMusic(AssetsManager::MENU_PRINCIPAL), true);
}

void MainMenu::handleInput()
{
	if (app_->getInputManager()->pressedStart()) {
		app_->getGameManager()->pressedStart();
	}
	else
		GameState::handleInput();
	
}

void MainMenu::GoPvP(App* app)
{
	//app->getStateMachine()->pushState(new SkillSelection(app));
	app->getAudioMngr()->playMusic(app->getAssetsManager()->getMusic(AssetsManager::FIGHT_1), true);
#ifdef _DEBUG
	std::cout << app->getStateMachine()->getCurrentState()->getb2World()->GetBodyCount() << std::endl;
#endif 
		

	app->getStateMachine()->pushState(new CharacterSelection(app,2));
#ifdef _DEBUG
	std::cout << app->getStateMachine()->getCurrentState()->getb2World()->GetBodyCount() << std::endl;
#endif 
}


void MainMenu::GoVsAI(App* app)
{
	app->getAudioMngr()->playMusic(app->getAssetsManager()->getMusic(AssetsManager::FIGHT_1), true);

	app->getStateMachine()->pushState(new CharacterSelection(app,1));
}

void MainMenu::GoOptions(App* app)
{
	app->getStateMachine()->pushState(new OptionsMenu(app));
}

void MainMenu::Leave(App* app)
{
	app->Exit();
}
