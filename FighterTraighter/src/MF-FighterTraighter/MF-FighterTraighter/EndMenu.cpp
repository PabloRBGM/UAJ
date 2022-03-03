#include "EndMenu.h"

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

EndMenu::EndMenu(App* app, int playerWin) : GameState(app), winner(playerWin)
{
#ifdef _DEBUG
	cout << "Menu Final" << endl;
#endif 
	init();
}

EndMenu::~EndMenu()
{

}

void EndMenu::init()
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

	string text;
	string text2;

	if (winner == 0) {
		text = "¡PLAYER 1 WINS! ¡YOU ARE A MONSTER!";
		text2 = "PLAYER 2 IS A NOOB";
	}
	else {
		text = "¡PLAYER 2 WINS! ¡YOU ARE A MONSTER!";
		text2 = "PLAYER 1 IS A NOOB";
	}
		
	//// Image
	//Entity* image = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::CollageCharacters),
	//	Vector2D(-50, 0),
	//	Vector2D(app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h / 2),
	//	Vector2D(900, 900 / 2),
	//	900, 900, 0);

	Entity* textWinner = entManager_.addEntity();
	textWinner->addComponent<UITransform>(Vector2D(0, 120), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, 200), Vector2D(450, 50), Vector2D(900, 250));
	textWinner->addComponent<TextComponent>(text, app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), 100, TextComponent::Center);

	Entity* textLoser = entManager_.addEntity();
	textLoser->addComponent<UITransform>(Vector2D(0, 120), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, 500), Vector2D(450, 50), Vector2D(900, 250));
	textLoser->addComponent<TextComponent>(text2, app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), 150, TextComponent::Center);

	// Position variables
	const double leftOffset = 250;
	//const double buttonInitPos = -160;
	const double buttonSeparation = 115;
	//const double textOffset = 5;
	const double textSize = 85;



	// Logo
	Entity* logo = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Logo),
		Vector2D(app_->getWindowManager()->getCurResolution().w / 2-leftOffset, 160),
		Vector2D(0, 0),
		Vector2D(0, 91 * 1.5 / 2),
		320 * 1.5, 91 * 1.5, 0);



	// 1v1 button
	tuple < Entity*, Entity*> menu_button = UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Button), app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black),
		Vector2D(-buttonSeparation, 0),
		Vector2D(app_->getWindowManager()->getCurResolution().w/2-150.0, app_->getWindowManager()->getCurResolution().h -100.0),
		Vector2D(0, 50),
		480, 100, 0, nullptr, GoMainMenu, "Go to menu", textSize, TextComponent::TextAlignment::Left);
	//std::get<1>(pvp)->getComponent<UITransform>(ecs::Transform)->setPosition(leftOffset + 35, 0);
	std::get<1>(menu_button)->getComponent<UITransform>(ecs::Transform)->setPosition(- 85, 0);


	// Navigation
	Entity* navEnt = entManager_.addEntity();
	NavigationController* nav = navEnt->addComponent<NavigationController>(1, 1);
	nav->SetElementInPos(std::get<0>(menu_button)->getComponent<UIElement>(ecs::UIElement), 0, 0);
	app_->getAudioMngr()->playMusic(app_->getAssetsManager()->getMusic(AssetsManager::MENU_OPCIONES), true);
}

void EndMenu::handleInput()
{
	if (app_->getInputManager()->pressedStart()) {
		app_->getAudioMngr()->stopMusic();
		app_->getAudioMngr()->playMusic(app_->getAssetsManager()->getMusic(AssetsManager::MENU_PRINCIPAL), true);
		app_->getGameManager()->GoBackToMain();
	}
	else
		GameState::handleInput();

}

void EndMenu::GoMainMenu(App* app)
{
	app->getAudioMngr()->playMusic(app->getAssetsManager()->getMusic(AssetsManager::MENU_PRINCIPAL), true);

	app->getGameManager()->GoBackToMain();
}
