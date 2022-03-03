#include "Training.h"
#include "Entity.h"
#include "PlayerController.h"
#include "RenderImage.h"
#include "PauseMenu.h"
#include "SacoManager.h"
#include "PunchingBagOnHit.h"
#include "FloorOnHit.h"
#include "UITransform.h"
#include "UITimer.h"
#include "UIHealthbar.h"
#include "CharFactory.h"
#include "RenderAnimation.h"
#include "TrainingController.h"
#include "Shake.h"
#include "Camera.h"

Training::Training(App* app) : GameState(app)
{
	init();
}

void Training::init()
{
	GameState::init();
	doStep = true;



	// Background
	Entity* bg = entManager_.addEntity();
	bg->addComponent<Transform>(Vector2D(), Vector2D(), app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h, 0);
	bg->addComponent<RenderAnimation>(app_->getAssetsManager()->getTexture(AssetsManager::BackgroundFight), 20);
	bg->addComponent<Shake>();
	entManager_.setHandler(bg, ecs::Camara);



	//Floor
	Entity* floor = entManager_.addEntity();
	PhysicsTransform* FpT = floor->addComponent<PhysicsTransform>(Vector2D(960, 1200), Vector2D(0, 0), 1920, 450, 0, world, BOUNDARY, EVERYTHING, 2);
	floor->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::TextureNames::floor));
	FpT->changeFriction(3);
	addHurtbox(FpT->getMainFixture());



	//Walls
	Entity* wall1 = entManager_.addEntity();
	PhysicsTransform* W1pT = wall1->addComponent<PhysicsTransform>(Vector2D(-50, 540), Vector2D(0, 0), 100, 1080, 0, world, WALLS, EVERYTHING, 2);
	W1pT->changeFriction(0);
	Entity* wall2 = entManager_.addEntity();
	PhysicsTransform* W2pT = wall2->addComponent<PhysicsTransform>(Vector2D(1970, 540), Vector2D(0, 0), 100, 1080, 0, world, WALLS, EVERYTHING, 2);
	W2pT->changeFriction(0);



	//Player1
	Entity* player1 = CharFactory::addCharacterToGame(app_, this, 1, world, &app_->getGameManager()->getPlayerInfo(1), PLAYER_1, BOUNDARY | P_BAG | WALLS, 0);
	entManager_.setHandler(player1, ecs::Player1);



	//Player2
	Entity* player2 = CharFactory::addCharacterToGame(app_, this, -1, world, &app_->getGameManager()->getPlayerInfo(2), PLAYER_2, BOUNDARY | P_BAG | WALLS, 1);
	entManager_.setHandler(player2, ecs::Player2);
	


	//Saco
	Entity* saco = entManager_.addEntity();
	PhysicsTransform* pBpT = saco->addComponent<PhysicsTransform>(Vector2D(app_->getWindowManager()->getCurResolution().w / 2, (double)app_->getWindowManager()->getCurResolution().h - 575), Vector2D(10, 10), 250, 900, 0, world, P_BAG, PLAYER_1 | PLAYER_2 | BULLET, 2);
	addHurtbox(pBpT->getMainFixture());
	pBpT->changeFriction(0);
	saco->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::saco2));
	Health* sacoHealth = saco->addComponent<Health>(165);
	SacoManager* sM = saco->addComponent<SacoManager>(20000);
	entManager_.setHandler(saco, ecs::Saco);
	

	// Background camera
	bg->addComponent<Camera>(player1->getComponent<Transform>(ecs::Transform), player2->getComponent<Transform>(ecs::Transform));



	//Timer Entity
	Entity* healthbarBack = entManager_.addEntity();
	healthbarBack->addComponent<UITransform>(Vector2D(0, 40), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, 0), Vector2D(850, 20), Vector2D(1700, 40));
	healthbarBack->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::HealthbarBack));
	Entity* healthbarL = entManager_.addEntity();
	healthbarL->addComponent<UITransform>(Vector2D(0, 40), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, 0), Vector2D(0, 20), Vector2D(850, 40));
	healthbarL->addComponent<UIHealthbar>(sacoHealth, app_->getAssetsManager()->getTexture(AssetsManager::HealthbarSaco));
	Entity* healthbarR = entManager_.addEntity();
	healthbarR->addComponent<UITransform>(Vector2D(0, 40), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, 0), Vector2D(850, 20), Vector2D(850, 40));
	healthbarR->addComponent<UIHealthbar>(sacoHealth, app_->getAssetsManager()->getTexture(AssetsManager::HealthbarSaco), true);



	// Character icons
	Entity* character1 = entManager_.addEntity();
	character1->addComponent<UITransform>(Vector2D(100, 70), Vector2D(), Vector2D(70, 70), Vector2D(140, 140));
	RenderImage* charIcon1 = character1->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::CharacterSelection));
	switch (app_->getGameManager()->getPlayerInfo(1).character) {
	case GameManager::Aisha: charIcon1->setFrame(0, 0); break;
	case GameManager::Mockingbird: charIcon1->setFrame(3, 0); break;
	case GameManager::MKWh00p: charIcon1->setFrame(2, 0); break;
	case GameManager::F10R: charIcon1->setFrame(1, 0); break;
	default: break; }
	Entity* character2 = entManager_.addEntity();
	character2->addComponent<UITransform>(Vector2D(-100, 70), Vector2D(app_->getWindowManager()->getCurResolution().w, 0), Vector2D(70, 70), Vector2D(140, 140));
	RenderImage* charIcon2 = character2->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::CharacterSelection));
	switch (app_->getGameManager()->getPlayerInfo(2).character) {
	case GameManager::Aisha: charIcon2->setFrame(0, 0); break;
	case GameManager::Mockingbird: charIcon2->setFrame(3, 0); break;
	case GameManager::MKWh00p: charIcon2->setFrame(2, 0); break;
	case GameManager::F10R: charIcon2->setFrame(1, 0); break;
	default: break; }



	// Controller
	Entity* gameController = entManager_.addEntity();
	gameController->addComponent<TrainingController>(180,180);
	entManager_.setHandler(gameController, ecs::Controller);
}

void Training::handleInput()
{
	if (app_->getInputManager()->pressedStart()) {
		app_->getGameManager()->pressedStart();
	}
	GameState::handleInput();
}

Training::~Training()
{
}