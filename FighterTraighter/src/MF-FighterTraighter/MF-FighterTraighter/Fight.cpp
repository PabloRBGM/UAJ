#include "Fight.h"
#include "FloorOnHit.h"
#include "UITransform.h"
#include "UIFactory.h"
#include "Health.h"
#include "UIHealthbar.h"
#include "UIRoundRenderer.h"
#include "AbilityFactory.h"
#include "RenderAnimation.h"
#include "Bullet.h"
#include "CharFactory.h"
#include "AbilitiesTimerFunction.h"
#include "FightController.h"

#include "Camera.h"
#include "Shake.h"
Fight::Fight(App* app) : GameState(app)
{
	init();
}

void Fight::init()
{
	GameState::init();
	doStep = true;



	// Background
	Entity* bg = entManager_.addEntity();
	bg->addComponent<Transform>(Vector2D(), Vector2D(), app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h, 0);
	bg->addComponent<RenderAnimation>(app_->getAssetsManager()->getTexture(AssetsManager::BackgroundFight), 20);
	bg->addComponent<Shake>();
	entManager_.setHandler(bg, ecs::Camara);



	// Floor
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



	//Player 1
	Entity* player1 = CharFactory::addCharacterToGame(app_, this, 1, world, &app_->getGameManager()->getPlayerInfo(1), PLAYER_1, PLAYER_2 | WALLS | BOUNDARY | BULLET, 0);
	//Giving abilites
	const GameManager::PlayerInfo& p1_info = app_->getGameManager()->getPlayerInfo(1);
	//////HABILIDAD A CHOLON
	/*player1->getComponent<CharacterAttacks>(ecs::CharacterAttacks)
		->setAbility(AbilityFactory::GiveAbility(GameManager::AbilityID::KnockDown, player1), 0);
	player1->getComponent<CharacterAttacks>(ecs::CharacterAttacks)
		->setAbility(AbilityFactory::GiveAbility(GameManager::AbilityID::NadoKick, player1), 1);*/
	player1->getComponent<CharacterAttacks>(ecs::CharacterAttacks)
		->setAbility(AbilityFactory::GiveAbility(p1_info.abilities[p1_info.ability1Index], player1), 0);
	player1->getComponent<CharacterAttacks>(ecs::CharacterAttacks)
		->setAbility(AbilityFactory::GiveAbility(p1_info.abilities[p1_info.ability2Index], player1), 1);
	entManager_.setHandler(player1, ecs::Player1);

	//Player 2
	Entity* player2 = CharFactory::addCharacterToGame(app_, this, -1, world, &app_->getGameManager()->getPlayerInfo(2), PLAYER_2, PLAYER_1 | WALLS | BOUNDARY | BULLET, 1);
	//Giving abilites
	const GameManager::PlayerInfo& p2_info = app_->getGameManager()->getPlayerInfo(2);

	player2->getComponent<CharacterAttacks>(ecs::CharacterAttacks)
		->setAbility(AbilityFactory::GiveAbility(p2_info.abilities[p2_info.ability1Index], player2), 0);
	player2->getComponent<CharacterAttacks>(ecs::CharacterAttacks)
		->setAbility(AbilityFactory::GiveAbility(p2_info.abilities[p2_info.ability2Index], player2), 1);
	entManager_.setHandler(player2, ecs::Player2);



	// Position variables
	const double abilityIconY = -190.0;
	const double ability1X = 105.0 + 30.0;
	const double ability2X = 280.0 + 30.0;
	const double windowWidth = app_->getWindowManager()->getCurResolution().w;
	const double abilityIconSize = 125.0;



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



	// Visual abilities player2
	Entity* imageability1p2 = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture((AssetsManager::TextureNames)(AssetsManager::_abilityIcon_start + p2_info.abilities[p2_info.ability1Index] + 1)),
		Vector2D(-ability2X, abilityIconY),
		Vector2D(app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h),
		Vector2D(abilityIconSize / 2, abilityIconSize / 2),
		abilityIconSize, abilityIconSize, 0);

	Entity* ability1p2 = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Mark1),
		Vector2D(-ability2X, abilityIconY),
		Vector2D(app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h),
		Vector2D(abilityIconSize / 2, abilityIconSize / 2),
		abilityIconSize, abilityIconSize, 0);

	Entity* imageability2p2 = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture((AssetsManager::TextureNames)(AssetsManager::_abilityIcon_start + p2_info.abilities[p2_info.ability2Index] + 1)),
		Vector2D(-ability1X, abilityIconY),
		Vector2D(app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h),
		Vector2D(abilityIconSize / 2, abilityIconSize / 2),
		abilityIconSize, abilityIconSize, 0);

	Entity* ability2p2 = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Mark2),
		Vector2D(-ability1X, abilityIconY),
		Vector2D(app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h),
		Vector2D(abilityIconSize / 2, abilityIconSize / 2),
		abilityIconSize, abilityIconSize, 0);

	Entity* timerab1p2 = entManager_.addEntity();
	timerab1p2->addComponent<UITransform>(Vector2D(-ability2X, abilityIconY - 50.0),
		Vector2D(app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h),
		Vector2D(abilityIconSize, abilityIconSize / 2),
		Vector2D(abilityIconSize * 2, abilityIconSize));
	timerab1p2->addComponent<TextComponent>("", app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), 45, TextComponent::Center);
	timerab1p2->addComponent<UITimer>(UITimer::Seconds)->setInvisible(true);

	Entity* timerab2p2 = entManager_.addEntity();
	timerab2p2->addComponent<UITransform>(Vector2D(-ability1X, abilityIconY - 50.0),
		Vector2D(app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h),
		Vector2D(abilityIconSize, abilityIconSize / 2),
		Vector2D(abilityIconSize * 2, abilityIconSize));
	timerab2p2->addComponent<TextComponent>("", app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), 45, TextComponent::Center);
	timerab2p2->addComponent<UITimer>(UITimer::Seconds)->setInvisible(true);

	Entity* timerspl2 = entManager_.addEntity();
	timerspl2->addComponent<AbilitiesTimerFunction>(timerab1p2->getComponent<UITimer>(ecs::UITimer), timerab2p2->getComponent<UITimer>(ecs::UITimer), player2);



	// Background camera
	bg->addComponent<Camera>(player1->getComponent<Transform>(ecs::Transform), player2->getComponent<Transform>(ecs::Transform));



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



	// Healthbar Player2
	Entity* healthbarBack2 = entManager_.addEntity();
	healthbarBack2->addComponent<UITransform>(Vector2D(-460, 50), Vector2D(app_->getWindowManager()->getCurResolution().w, 0), Vector2D(365, 20), Vector2D(730, 40));
	healthbarBack2->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::HealthbarBack));
	Entity* healthbar2 = entManager_.addEntity();
	healthbar2->addComponent<UITransform>(Vector2D(-460, 50), Vector2D(app_->getWindowManager()->getCurResolution().w, 0), Vector2D(365, 20), Vector2D(730, 40));
	healthbar2->addComponent<UIHealthbar>(player2->getComponent<Health>(ecs::Health), app_->getAssetsManager()->getTexture(AssetsManager::Healthbar));
	Entity* character2 = entManager_.addEntity();
	character2->addComponent<UITransform>(Vector2D(-70, 70), Vector2D(app_->getWindowManager()->getCurResolution().w, 0), Vector2D(70, 70), Vector2D(140, 140));
	RenderImage* charIcon2 = character2->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::CharacterSelection));
	switch (app_->getGameManager()->getPlayerInfo(2).character) {
	case GameManager::Aisha: charIcon2->setFrame(0, 0); break;
	case GameManager::Mockingbird: charIcon2->setFrame(3, 0); break;
	case GameManager::MKWh00p: charIcon2->setFrame(2, 0); break;
	case GameManager::F10R: charIcon2->setFrame(1, 0); break;
	default: break;
	}



	// Round counters
	std::vector<Entity*> leftCounter;
	std::vector<Entity*> rightCounter;
	for (int i = 0; i < app_->getGameManager()->getTotalRounds() / 2 + 1; ++i) {
		Entity* roundCounter1 = entManager_.addEntity();
		roundCounter1->addComponent<UITransform>(Vector2D(-173.0 - i * 40.0, 93), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, 0), Vector2D(18, 18), Vector2D(36, 36));
		roundCounter1->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::RoundCounter));
		leftCounter.push_back(roundCounter1);
		Entity* roundCounter2 = entManager_.addEntity();
		roundCounter2->addComponent<UITransform>(Vector2D(173.0 + i * 40.0, 93), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, 0), Vector2D(18, 18), Vector2D(36, 36));
		roundCounter2->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::RoundCounter));
		rightCounter.push_back(roundCounter2);
	}



	// Controller
	Entity* gameController = entManager_.addEntity();
	gameController->addComponent<UIRoundRenderer>(leftCounter)->setRoundsWon(app_->getGameManager()->getPlayerRounds(1));
	gameController->addComponent<UIRoundRenderer>(rightCounter)->setRoundsWon(app_->getGameManager()->getPlayerRounds(2));
	gameController->addComponent<FightController>(240, 180);
	entManager_.setHandler(gameController, ecs::Controller);



	//Timer Ent
	Entity* timer = entManager_.addEntity();
	timer->addComponent<UITransform>(Vector2D(0, 75), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, 0), Vector2D(200, 50), Vector2D(400, 100));
	timer->addComponent<TextComponent>("0000", app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), 45, TextComponent::Center);
	timer->addComponent<UITimer>(UITimer::Minutes, true, 240000, [gameController, timer, player1, player2]() { //4 minutes timer
		gameController->getComponent<FightController>(ecs::FightController)
			->PlayerLost(player1->getComponent<Health>(ecs::Health)->getHealth() > player2->getComponent<Health>(ecs::Health)->getHealth() ? 1 : 0);
		});
}

void Fight::handleInput()
{
	if (app_->getInputManager()->pressedStart()) {
		app_->getGameManager()->pressedStart();
	}
	else
		GameState::handleInput();
}
Fight::~Fight()
{
}
