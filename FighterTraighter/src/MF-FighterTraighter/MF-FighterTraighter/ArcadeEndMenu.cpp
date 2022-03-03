#include "ArcadeEndMenu.h"

#include "InputManager.h"

#include "Entity.h"
#include "RenderImage.h"
#include "TextComponent.h"
#include "NavigationController.h"
#include "Font.h"
#include "App.h"
#include "UIFactory.h"
#include "RenderAnimation.h"
#include "UITransform.h"
#include "SkillSelection.h"

ArcadeEndMenu::ArcadeEndMenu(App* app, int numRound): GameState(app), numRound_(numRound)
{

#ifdef _DEBUG
	cout << "Menu Final" << endl;
#endif 
	init();
}

ArcadeEndMenu::~ArcadeEndMenu()
{
}

void ArcadeEndMenu::init()
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


	//UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::FlorArtwork),
		//Vector2D(-125, -125), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, app_->getWindowManager()->getCurResolution().h / 2 - 175), Vector2D(115, 115), 230, 230, 0);


	
	string text = "You win "+  to_string(numRound_) +" rounds";
	//text2 = "PLAYER 1 IS A NOOB";
	

	//// Image
	//Entity* image = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::CollageCharacters),
	//	Vector2D(-50, 0),
	//	Vector2D(app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h / 2),
	//	Vector2D(900, 900 / 2),
	//	900, 900, 0);

	Entity* textWinner = entManager_.addEntity();
	textWinner->addComponent<UITransform>(Vector2D(0, 120), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, 200), Vector2D(450, 50), Vector2D(900, 450));
	textWinner->addComponent<TextComponent>(text, app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), 200, TextComponent::Center);

	

	// Position variables
	const double leftOffset = 250;
	//const double buttonInitPos = -160;
	const double buttonSeparation = 115;
	//const double textOffset = 5;
	const double textSize = 85;



	// Logo
	Entity* logo = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Logo),
		Vector2D(app_->getWindowManager()->getCurResolution().w / 2 - leftOffset, 160),
		Vector2D(0, 0),
		Vector2D(0, 91 * 1.5 / 2),
		320 * 1.5, 91 * 1.5, 0);



	// 1v1 button
	tuple < Entity*, Entity*> menu_button = UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Button), app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black),
		Vector2D(-buttonSeparation, 0),
		Vector2D(app_->getWindowManager()->getCurResolution().w / 2 - 150.0, app_->getWindowManager()->getCurResolution().h - 100.0),
		Vector2D(0, 50),
		480, 100, 0, nullptr, GoMainMenu, "Go to menu", textSize, TextComponent::TextAlignment::Left);
	//std::get<1>(pvp)->getComponent<UITransform>(ecs::Transform)->setPosition(leftOffset + 35, 0);
	std::get<1>(menu_button)->getComponent<UITransform>(ecs::Transform)->setPosition(-85, 0);


	// Navigation
	Entity* navEnt = entManager_.addEntity();
	NavigationController* nav = navEnt->addComponent<NavigationController>(1, 1);
	nav->SetElementInPos(std::get<0>(menu_button)->getComponent<UIElement>(ecs::UIElement), 0, 0);
	app_->getAudioMngr()->playMusic(app_->getAssetsManager()->getMusic(AssetsManager::MENU_OPCIONES), true);
}

void ArcadeEndMenu::handleInput()
{
	if (app_->getInputManager()->pressedStart()) {
		app_->getAudioMngr()->stopMusic();
		app_->getAudioMngr()->playMusic(app_->getAssetsManager()->getMusic(AssetsManager::MENU_PRINCIPAL), true);
		app_->getGameManager()->GoBackToMain();
	}
	else
		GameState::handleInput();
}

void ArcadeEndMenu::GoMainMenu(App* app)
{
	app->getAudioMngr()->playMusic(app->getAssetsManager()->getMusic(AssetsManager::MENU_PRINCIPAL), true);
	app->getGameManager()->GoBackToMain();
}
