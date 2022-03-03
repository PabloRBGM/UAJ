#include "AIGameState.h"
#include "CharFactory.h"
#include "PhysicsTransform.h"
#include "AILogic.h"
#include "PlayerAttacks.h"
#include "F10RData.h"
#include "AIHID.h"
#include "AIController.h"
#include "AIAttacks.h"
#include "PlayerOnHit.h"
#include "Health.h"
#include "PlayerAnimation.h"
#include "ArcadeController.h"
#include "AbilityFactory.h"
#include "UIFactory.h"
#include "RenderAnimation.h"
#include "Shake.h"
#include "Camera.h"
#include "UIHealthbar.h"
#include "UITransform.h"

void AIGameState::init()
{
	GameState::init();
	doStep = true;

	//delete app_->getGameManager()->getPlayerInfo(2).hid;
	//*app_->getGameManager()->getPlayerInfo(2).hid = AIHID();

	// Background
	Entity* bg = entManager_.addEntity();
	bg->addComponent<Transform>(Vector2D(), Vector2D(), app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h, 0);
	bg->addComponent<RenderAnimation>(app_->getAssetsManager()->getTexture(AssetsManager::BackgroundFloor), 20);
	bg->addComponent<Shake>();

	entManager_.setHandler(bg, ecs::Camara);

	// Floor
	Entity* floor = entManager_.addEntity();
	PhysicsTransform* FpT = floor->addComponent<PhysicsTransform>(Vector2D(960, 1200), Vector2D(0, 0), 1920, 450, 0, world, BOUNDARY, EVERYTHING, 2);
	floor->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::TextureNames::floorIA));
	FpT->changeFriction(3);
	addHurtbox(FpT->getMainFixture());
	//Walls
	Entity* wall1 = entManager_.addEntity();
	PhysicsTransform* W1pT = wall1->addComponent<PhysicsTransform>(Vector2D(-50, 540), Vector2D(0, 0), 100, 1080, 0, world, WALLS, EVERYTHING, 2);
	W1pT->changeFriction(0);
	Entity* wall2 = entManager_.addEntity();
	PhysicsTransform* W2pT = wall2->addComponent<PhysicsTransform>(Vector2D(1970, 540), Vector2D(0, 0), 100, 1080, 0, world, WALLS, EVERYTHING, 2);
	W2pT->changeFriction(0);

	Entity* player1 = CharFactory::addCharacterToGame(app_, this, 1, world, &app_->getGameManager()->getPlayerInfo(1),
		PLAYER_1, PLAYER_2 | WALLS | BOUNDARY | BULLET, 0);
	entManager_.setHandler(player1, ecs::Player1);

	const GameManager::PlayerInfo& p1_info = app_->getGameManager()->getPlayerInfo(1);
	player1->getComponent<CharacterAttacks>(ecs::CharacterAttacks)
		->setAbility(AbilityFactory::GiveAbility(p1_info.abilities[p1_info.ability1Index], player1), 0);
	player1->getComponent<CharacterAttacks>(ecs::CharacterAttacks)
		->setAbility(AbilityFactory::GiveAbility(p1_info.abilities[p1_info.ability2Index], player1), 1);
	entManager_.setHandler(player1, ecs::Player1);
	//Entity* AI1 = CharFactory::addAICharacterToGame(app_, this, 1, world, GameManager::F10R, 5, Vector2D(350, 450),
	//	PLAYER_1, PLAYER_2 | WALLS | BOUNDARY | BULLET, 0);
	//entManager_.setHandler(AI1, ecs::Player1);



	GameManager::CharacterID AICharacter = GameManager::CharacterID(app_->getRandGen()->nextInt(GameManager::F10R, GameManager::Aisha));
	Entity* AI2 = CharFactory::addAICharacterToGame(app_, this, -1, world, AICharacter, 5, Vector2D(350, 450),
		PLAYER_2, PLAYER_1 | WALLS | BOUNDARY | BULLET, 1);
	entManager_.setHandler(AI2, ecs::Player2);

	// Position variables
	const double abilityIconY = -190;
	const double ability1X = 105 + 30;
	const double ability2X = 280 + 30;
	const double windowWidth = app_->getWindowManager()->getCurResolution().w;
	const double abilityIconSize = 125;



	// Visual abilities player1
	Entity* imageability1 = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture((AssetsManager::TextureNames)(AssetsManager::_abilityIcon_start + p1_info.abilities[p1_info.ability1Index] + 1)),
		Vector2D(ability1X, abilityIconY),
		Vector2D(0, app_->getWindowManager()->getCurResolution().h),
		Vector2D(abilityIconSize / 2, abilityIconSize / 2),
		abilityIconSize, abilityIconSize, 0);

	Entity* ability1 = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Mark1),
		Vector2D(ability1X, abilityIconY),
		Vector2D(0, app_->getWindowManager()->getCurResolution().h),
		Vector2D(abilityIconSize / 2, abilityIconSize / 2),
		abilityIconSize, abilityIconSize, 0);


	Entity* imageability2 = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture((AssetsManager::TextureNames)(AssetsManager::_abilityIcon_start + p1_info.abilities[p1_info.ability2Index] + 1)),
		Vector2D(ability2X, abilityIconY),
		Vector2D(0, app_->getWindowManager()->getCurResolution().h),
		Vector2D(abilityIconSize / 2, abilityIconSize / 2),
		abilityIconSize, abilityIconSize, 0);

	Entity* ability2 = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Mark2),
		Vector2D(ability2X, abilityIconY),
		Vector2D(0, app_->getWindowManager()->getCurResolution().h),
		Vector2D(abilityIconSize / 2, abilityIconSize / 2),
		abilityIconSize, abilityIconSize, 0);

	Entity* timerab1 = entManager_.addEntity();
	timerab1->addComponent<UITransform>(Vector2D(ability1X, abilityIconY - 50.0),
		Vector2D(0, app_->getWindowManager()->getCurResolution().h),
		Vector2D(abilityIconSize, abilityIconSize / 2),
		Vector2D(abilityIconSize * 2, abilityIconSize));
	timerab1->addComponent<TextComponent>("", app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), 45, TextComponent::Center);
	timerab1->addComponent<UITimer>(UITimer::Seconds)->setInvisible(true);

	Entity* timerab2 = entManager_.addEntity();
	timerab2->addComponent<UITransform>(Vector2D(ability2X, abilityIconY - 50.0),
		Vector2D(0, app_->getWindowManager()->getCurResolution().h),
		Vector2D(abilityIconSize, abilityIconSize / 2),
		Vector2D(abilityIconSize * 2, abilityIconSize));
	timerab2->addComponent<TextComponent>("", app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), 45, TextComponent::Center);
	timerab2->addComponent<UITimer>(UITimer::Seconds)->setInvisible(true);

	Entity* timerspl1 = entManager_.addEntity();
	timerspl1->addComponent<AbilitiesTimerFunction>(timerab1->getComponent<UITimer>(ecs::UITimer), timerab2->getComponent<UITimer>(ecs::UITimer), player1);



	Entity* gameController = entManager_.addEntity();
	gameController->addComponent<ArcadeController>(240, 180);
	entManager_.setHandler(gameController, ecs::Controller);
	// Background camera
	bg->addComponent<Camera>(player1->getComponent<Transform>(ecs::Transform), AI2->getComponent<Transform>(ecs::Transform));

	// Healthbar Player1
	Entity* healthbarBack1 = entManager_.addEntity();
	healthbarBack1->addComponent<UITransform>(Vector2D(460, 50), Vector2D(0, 0), Vector2D(365, 20), Vector2D(730, 40));
	healthbarBack1->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::HealthbarBack));
	Entity* healthbar1 = entManager_.addEntity();
	healthbar1->addComponent<UITransform>(Vector2D(460, 50), Vector2D(0, 0), Vector2D(365, 20), Vector2D(730, 40));
	healthbar1->addComponent<UIHealthbar>(player1->getComponent<Health>(ecs::Health), app_->getAssetsManager()->getTexture(AssetsManager::Healthbar), true);
	// Player1 icon
	Entity* character1 = entManager_.addEntity();
	character1->addComponent<UITransform>(Vector2D(70, 70), Vector2D(), Vector2D(70, 70), Vector2D(140, 140));
	RenderImage* charIcon1 = character1->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::CharacterSelection));
	switch (app_->getGameManager()->getPlayerInfo(1).character) {
	case GameManager::Aisha: charIcon1->setFrame(0, 0); break;
	case GameManager::Mockingbird: charIcon1->setFrame(3, 0); break;
	case GameManager::MKWh00p: charIcon1->setFrame(2, 0); break;
	case GameManager::F10R: charIcon1->setFrame(1, 0); break;
	default: break;
	}




	string text = "Round " + to_string(app_->getGameManager()->getPlayerRounds(1)+1);
	Entity* textWinner = entManager_.addEntity();
	textWinner->addComponent<UITransform>(Vector2D(0, 50), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, 30), Vector2D(200, 50), Vector2D(400, 100));
	textWinner->addComponent<TextComponent>(text, app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black),40, TextComponent::Center);



	// Healthbar Player2
	Entity* healthbarBack2 = entManager_.addEntity();
	healthbarBack2->addComponent<UITransform>(Vector2D(-460, 50), Vector2D(app_->getWindowManager()->getCurResolution().w, 0), Vector2D(365, 20), Vector2D(730, 40));
	healthbarBack2->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::HealthbarBack));
	Entity* healthbar2 = entManager_.addEntity();
	healthbar2->addComponent<UITransform>(Vector2D(-460, 50), Vector2D(app_->getWindowManager()->getCurResolution().w, 0), Vector2D(365, 20), Vector2D(730, 40));
	healthbar2->addComponent<UIHealthbar>(AI2->getComponent<Health>(ecs::Health), app_->getAssetsManager()->getTexture(AssetsManager::Healthbar));
	Entity* character2 = entManager_.addEntity();
	character2->addComponent<UITransform>(Vector2D(-70, 70), Vector2D(app_->getWindowManager()->getCurResolution().w, 0), Vector2D(70, 70), Vector2D(140, 140));
	RenderImage* charIcon2 = character2->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::CharacterSelection));
	switch (AICharacter) {
	case GameManager::Aisha: charIcon2->setFrame(0, 0); break;
	case GameManager::Mockingbird: charIcon2->setFrame(3, 0); break;
	case GameManager::MKWh00p: charIcon2->setFrame(2, 0); break;
	case GameManager::F10R: charIcon2->setFrame(1, 0); break;
	default: break;
	}

}

void AIGameState::handleInput()
{
	if (app_->getInputManager()->pressedStart()) {
		app_->getGameManager()->pressedStart();
	}
	else GameState::handleInput();
}
