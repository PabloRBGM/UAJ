#include "F10RData.h"
#include "AbilityFactory.h"
#include "DestroyAtTime.h"
#include "PlayerParticleSystem.h"
F10RData::F10RData(double width, double height, double rotation, double jump_impulse, Vector2D ini_pos, double speed, double ini_health, double attack, double defense, int playerNumber):
	PlayerData(width, height, rotation, jump_impulse, ini_pos, speed, ini_health, attack, defense, playerNumber) {
	animLength_ = { {4, true, 12}, {3, true, 15}, {2, true, 3}, {1, true, 15}, {2, false, 4}, {4, false, 10}, {6, false, 10}, {5, false, 12},
	{6, false, 14}, {5, false, 10}, {5, false, 9}, {5, false, 10}, {6, false, 12}, {2, true, 15}, {2, false, 10}, {2, false, 4}, {2, false, 10},
	{2, false, 3}, {2, true, 12}, {2, false, 7}, {3, false, 7}, {6, false, 12}, {3, true, 10} };
}

void F10RData::init()
{
	std::vector<Move*> vecMov;

	vecMov.push_back(new Move(30, nullptr, NP1, entity_));
	vecMov.push_back(new Move(23, nullptr, nullptr, entity_));
	normal_punch_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(29, nullptr, HP1, entity_));
	vecMov.push_back(new Move(44, nullptr, nullptr, entity_));
	hard_punch_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(20, nullptr, NK1, entity_));
	vecMov.push_back(new Move(33, nullptr, nullptr, entity_));
	normal_kick_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(40, nullptr, HK1, entity_));
	vecMov.push_back(new Move(55, nullptr, nullptr, entity_));
	hard_kick_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(24, nullptr, ANP1, entity_));
	vecMov.push_back(new Move(30, nullptr, nullptr, entity_));
	air_normal_punch_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(30, nullptr, AHP1, entity_));
	vecMov.push_back(new Move(24, nullptr, nullptr, entity_));
	air_hard_punch_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(27, nullptr, ANK1, entity_));
	vecMov.push_back(new Move(30, nullptr, nullptr, entity_));
	air_normal_kick_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(28, nullptr, AHK1, entity_));
	vecMov.push_back(new Move(40, nullptr, nullptr, entity_));
	air_hard_kick_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(30, nullptr, GB, entity_));
	vecMov.push_back(new Move(50, nullptr, nullptr, entity_));
	guard_breaker_ = new AnimationChain(vecMov);
	vecMov.clear();
}

void F10RData::NP1(Entity* ent)
{
#ifdef _DEBUG
	std::cout << "Nibble" << endl;
#endif // _DEBUG

	double hitbox_X = np1.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += np1.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, np1.position.getY() }, np1.width, np1.height, np1.time, pD->getAttack()* np1.damage, np1.hitstun, 
		{ (double)orientation_ * np1.knockBack.getX(), np1.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::HIT2), false);

}

PlayerData::CallbackData F10RData::np1 = PlayerData::CallbackData{
	{ 125, -35 },
	{ 50, 0 },
	80,
	95,
	5,
	2,
	45 };

void F10RData::HP1(Entity* ent)
{
#ifdef _DEBUG
	std::cout << "Do it for the vine" << endl;
#endif // _DEBUG

	double hitbox_X = np1.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1) hitbox_X += hp1.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, hp1.position.getY() }, hp1.width, hp1.height, hp1.time, pD->getAttack() * hp1.damage, hp1.hitstun,
		{ (double)orientation_ * hp1.knockBack.getX(), hp1.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());

	double partX = pT->getWidth() * 3 / 4 - 20;
	if(orientation_ == -1) partX = pT->getWidth() / 4 - hp1.width + 20;
	Vector2D pos = Vector2D(partX, 285);

	ent->getComponent<PlayerParticleSystem>(ecs::PlayerParticleSystem)->addNewParticle(ent->getApp()->getAssetsManager()->getTexture(AssetsManager::F10RHp),
		pos, Vector2D(hp1.width, hp1.height), hp1.time, PlayerParticleSystem::DeletionMethod::OnHit);
	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::HIT), false);

}

PlayerData::CallbackData F10RData::hp1 = PlayerData::CallbackData{
	{ 0, 35 },
	{ 375, -175 },
	325,
	70,
	15,
	9,
	22 };

void F10RData::NK1(Entity* ent)
{
#ifdef _DEBUG
	std::cout << "Kik in the Kök" << endl;
#endif // _DEBUG

	double hitbox_X = nk1.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += nk1.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, nk1.position.getY() }, nk1.width, nk1.height, nk1.time, pD->getAttack() * nk1.damage, nk1.hitstun,
		{ (double)orientation_ * nk1.knockBack.getX(), nk1.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::KICK), false);

}

PlayerData::CallbackData F10RData::nk1 = PlayerData::CallbackData{
	{ 125, 95 },
	{ 500, -200 },
	80,
	100,
	15,
	6,
	31 };

void F10RData::HK1(Entity* ent)
{
#ifdef _DEBUG
	std::cout << "Filia" << endl;
#endif // _DEBUG

	GameState* currentState = ent->getApp()->getStateMachine()->getCurrentState();
	Texture* texture = ent->getApp()->getAssetsManager()->getTexture(AssetsManager::F10RHk);
	PhysicsTransform* phtr = ent->getComponent<PhysicsTransform>(ecs::Transform);

	uint16 mask;
	int orientation_ = ent->getComponent<Transform>(ecs::Transform)->getOrientation();

	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	if (pD->getPlayerNumber() == 0) {
		mask = currentState->PLAYER_2 | currentState->P_BAG;
	}
	else {
		mask = currentState->PLAYER_1 | currentState->P_BAG;
	}

	double projX = phtr->getPosition().getX() + (phtr->getWidth() * 3 / 4) + (hk1.width / 2) + hk1.position.getX();
	if (orientation_ == -1) projX = phtr->getPosition().getX() + (phtr->getWidth() * 1 / 4) - (hk1.width / 2) - hk1.position.getX();

	Vector2D pos = Vector2D(projX, phtr->getPosition().getY() + hk1.position.getY());
	DestroyAtTime* dT = new DestroyAtTime(hk1.damage * pD->getAttack(), hk1.time, hk1.hitstun, { (double)orientation_ * hk1.knockBack.getX(), hk1.knockBack.getY() }, false, ent->getComponent<PlayerData>(ecs::PlayerData)->getPlayerNumber(), ent);

	AbilityFactory::instanceEntitywHitbox(ent, hk1.width, hk1.height, pos,{ 0, -8 }, mask, ent->getState(), ent->getApp(), texture, orientation_, dT);
	
	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::PUNCH2), false);


//AbilityFactory::createProyectile(ent, hk1.width, hk1.height, pos, { 0, -8 }, hk1.damage, hk1.hitstun, { (double)orientation_ * hk1.knockBack.getX(), hk1.knockBack.getY() },
		//hk1.time, mask, ent->getState(), ent->getApp(), texture, false);
}

PlayerData::CallbackData F10RData::hk1 = PlayerData::CallbackData{
	{ 450, 700 },
	{ 1.8, -6 },
	120,
	210,
	20,
	14,
	39 };

void F10RData::ANP1(Entity* ent)
{
#ifdef _DEBUG
	std::cout << "Pollen" << endl;
#endif // _DEBUG

	double hitbox_X = anp1.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += anp1.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, anp1.position.getY() }, anp1.width, anp1.height, anp1.time, pD->getAttack() * anp1.damage, anp1.hitstun,
		{ (double)orientation_ * anp1.knockBack.getX(), anp1.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::ATAQUE), false);

}

PlayerData::CallbackData F10RData::anp1 = PlayerData::CallbackData{
	{ -100, -180 },
	{ 500, -270 },
	350,
	350,
	15,
	5,
	12 };

void F10RData::AHP1(Entity* ent)
{
#ifdef _DEBUG
	std::cout << "Downward root" << endl;
#endif // _DEBUG

	GameState* currentState = ent->getApp()->getStateMachine()->getCurrentState();
	Texture* texture = ent->getApp()->getAssetsManager()->getTexture(AssetsManager::F10RHk);
	PhysicsTransform* phtr = ent->getComponent<PhysicsTransform>(ecs::Transform);

	uint16 mask;
	int orientation_ = ent->getComponent<Transform>(ecs::Transform)->getOrientation();

	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	if (pD->getPlayerNumber() == 0) {
		mask = currentState->PLAYER_2 | currentState->P_BAG;
	}
	else {
		mask = currentState->PLAYER_1 | currentState->P_BAG;
	}

	double projX = phtr->getPosition().getX() + (phtr->getWidth() * 3 / 4) + (ahp1.width / 2) + ahp1.position.getX();
	if (orientation_ == -1) projX = phtr->getPosition().getX() + (phtr->getWidth() * 1 / 4) - (ahp1.width / 2) - ahp1.position.getX();

	Vector2D pos = Vector2D(projX, phtr->getPosition().getY() + ahp1.position.getY());

	DestroyAtTime* dT = new DestroyAtTime(ahp1.damage * pD->getAttack(), ahp1.time, ahp1.hitstun, { (double)orientation_ * ahp1.knockBack.getX(), ahp1.knockBack.getY() }, false, ent->getComponent<PlayerData>(ecs::PlayerData)->getPlayerNumber(), ent);

	AbilityFactory::instanceEntitywHitbox(ent, ahp1.width, ahp1.height, pos, { (double)orientation_ * 2.7, 4 }, mask, ent->getState(), ent->getApp(), texture, orientation_, dT);
	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::FLOR_2), false);

	//AbilityFactory::createProyectile(ent, ahp1.width, ahp1.height, pos, { (double)orientation_* 1.4, 4 }, ahp1.damage, ahp1.hitstun, { (double)orientation_ * ahp1.knockBack.getX(), ahp1.knockBack.getY() },
		//ahp1.time, mask, ent->getState(), ent->getApp(), texture, false);
}

PlayerData::CallbackData F10RData::ahp1 = PlayerData::CallbackData{
	{ 0, 450 },
	{ 1, 3 },
	115,
	200,
	14,
	6,
	21 };

void F10RData::ANK1(Entity* ent)
{
#ifdef _DEBUG
	std::cout << "This one doesn't bounce actually" << endl;
#endif 

	GameState* currentState = ent->getApp()->getStateMachine()->getCurrentState();
	Texture* texture = ent->getApp()->getAssetsManager()->getTexture(AssetsManager::F10RHp);
	PhysicsTransform* phtr = ent->getComponent<PhysicsTransform>(ecs::Transform);

	uint16 mask;
	int orientation_ = ent->getComponent<Transform>(ecs::Transform)->getOrientation();

	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	if (pD->getPlayerNumber() == 0) {
		mask = currentState->PLAYER_2 | currentState->P_BAG;
	}
	else {
		mask = currentState->PLAYER_1 | currentState->P_BAG;
	}

	double projX1 = phtr->getPosition().getX() + (phtr->getWidth() * 3 / 4) + (ank1.width / 2) + ank1.position.getX();
	if (orientation_ == -1) projX1 = phtr->getPosition().getX() + (phtr->getWidth() * 1 / 4) - (ank1.width / 2) - ank1.position.getX();
	Vector2D pos1 = Vector2D(projX1, phtr->getPosition().getY() + ank1.position.getY());

	double projX2 = phtr->getPosition().getX() + (phtr->getWidth() * 3 / 4) + (ank1.width / 2) + ank1.position.getX() - 45;
	if (orientation_ == -1) projX2 = phtr->getPosition().getX() + (phtr->getWidth() * 1 / 4) - (ank1.width / 2) - ank1.position.getX() + 45;
	Vector2D pos2 = Vector2D(projX2, phtr->getPosition().getY() + ank1.position.getY() - 100);

	double projX3 = phtr->getPosition().getX() + (phtr->getWidth() * 3 / 4) + (ank1.width / 2) + ank1.position.getX() - 90;
	if (orientation_ == -1) projX3 = phtr->getPosition().getX() + (phtr->getWidth() * 1 / 4) - (ank1.width / 2) - ank1.position.getX() + 90;
	Vector2D pos3 = Vector2D(projX3, phtr->getPosition().getY() + ank1.position.getY() - 200);

	DestroyAtTime* dT1 = new DestroyAtTime(ank1.damage * pD->getAttack(), ank1.time, ank1.hitstun, { (double)orientation_ * ank1.knockBack.getX(), ank1.knockBack.getY() }, false, pD->getPlayerNumber(), ent);
	DestroyAtTime* dT2 = new DestroyAtTime(ank1.damage * pD->getAttack(), ank1.time, ank1.hitstun, { (double)orientation_ * ank1.knockBack.getX(), ank1.knockBack.getY() }, false, pD->getPlayerNumber(), ent);
	DestroyAtTime* dT3 = new DestroyAtTime(ank1.damage * pD->getAttack(), ank1.time, ank1.hitstun, { (double)orientation_ * ank1.knockBack.getX(), ank1.knockBack.getY() }, false, pD->getPlayerNumber(), ent);
	/*AbilityFactory::createProyectile(ent, ank1.width, ank1.height, pos, { (double)orientation_ * 2, 0 }, ank1.damage, ank1.hitstun, { (double)orientation_ * ank1.knockBack.getX(), ank1.knockBack.getY() },
		ank1.time, mask, ent->getState(), ent->getApp(), texture, false);*/
	AbilityFactory::instanceEntitywHitbox(ent, ank1.width, ank1.height, pos1, { (double)orientation_ * 2.8, 0 }, mask, ent->getState(), ent->getApp(), texture, orientation_, dT1);
	AbilityFactory::instanceEntitywHitbox(ent, ank1.width, ank1.height, pos2, { (double)orientation_ * 3.1, 0 }, mask, ent->getState(), ent->getApp(), texture, orientation_, dT2);
	AbilityFactory::instanceEntitywHitbox(ent, ank1.width, ank1.height, pos3, { (double)orientation_ * 3.4, 0 }, mask, ent->getState(), ent->getApp(), texture, orientation_, dT3);
	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::NORMALPUNCH), false);
}

PlayerData::CallbackData F10RData::ank1 = PlayerData::CallbackData{
	{ -50, 500 },
	{ 3.5, -1.5 },
	120,
	55,
	25,
	3,
	42 };

void F10RData::AHK1(Entity* ent)
{
#ifdef _DEBUG
	std::cout << "Bramble tackle" << endl;
#endif // _DEBUG

	double hitbox_X = ahk1.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += ahk1.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, ahk1.position.getY() }, ahk1.width, ahk1.height, ahk1.time, pD->getAttack() * ahk1.damage, ahk1.hitstun,
		{ (double)orientation_ * ahk1.knockBack.getX(), ahk1.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::KICK), false);

}

PlayerData::CallbackData F10RData::ahk1 = PlayerData::CallbackData{
	{ 65, -120 },
	{ 300, 160 },
	150,
	350,
	20,
	6,
	42 };

void F10RData::GB(Entity* ent)
{
#ifdef _DEBUG
	std::cout << "Breaker flower! UAAAAA! Fear my flower power!!!!!" << endl;
#endif // _DEBUG

	double hitbox_X = gb.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += gb.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, gb.position.getY() }, gb.width, gb.height, gb.time, pD->getAttack() * gb.damage, gb.hitstun,
		{ (double)orientation_ * gb.knockBack.getX(), gb.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask(), true);
	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::POWER2), false);

}

PlayerData::CallbackData F10RData::gb = PlayerData::CallbackData{
	{ 100, -45 },
	{ 0, 0 },
	150,
	180,
	20,
	0,
	100 };
