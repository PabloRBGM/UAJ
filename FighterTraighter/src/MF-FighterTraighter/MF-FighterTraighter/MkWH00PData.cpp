#include "MkWH00PData.h"
#include "AbilityFactory.h"
#include "DestroyAtTime.h"

MkWH00PData::MkWH00PData(double width, double height, double rotation, double jump_impulse, Vector2D ini_pos, double speed, double ini_health, double attack, double defense, int playerNumber) :
	PlayerData(width, height, rotation, jump_impulse, ini_pos, speed, ini_health, attack, defense, playerNumber) {
	animLength_ = { {4, true, 12}, {4, true, 15}, {2, true, 3}, {1, true, 15}, {4, false, 2}, {12, false, 10}, {7, false, 10}, {9, false, 8},
	{15, false, 7}, {7, false, 13}, {9, false, 10}, {10, false, 7}, {5, false, 15}, {2, true, 15}, {2, false, 10}, {3, false, 4}, {2, false, 10}, 
	{2, false, 3}, {4, true, 12}, {2, false, 7}, {2, false, 7}, {8, false, 8}, {8, true, 10} };
}

void MkWH00PData::init() {
	std::vector<Move*> vecMov;

	vecMov.push_back(new Move(27, nullptr, NP1, entity_));
	vecMov.push_back(new Move(40, nullptr, nullptr, entity_));
	normal_punch_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(29, nullptr, HP1, entity_));
	vecMov.push_back(new Move(33, nullptr, nullptr, entity_));
	hard_punch_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(25, nullptr, NK1, entity_));
	vecMov.push_back(new Move(20, nullptr, NK2, entity_));
	vecMov.push_back(new Move(35, nullptr, nullptr, entity_));
	normal_kick_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(35, nullptr, HK1, entity_));
	vecMov.push_back(new Move(15, nullptr, HK2, entity_));
	vecMov.push_back(new Move(45, nullptr, nullptr, entity_));
	hard_kick_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(32, nullptr, ANP1, entity_));
	vecMov.push_back(new Move(25, nullptr, ANP2, entity_));
	vecMov.push_back(new Move(35, nullptr, nullptr, entity_));
	air_normal_punch_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(45, nullptr, AHP1, entity_));
	vecMov.push_back(new Move(45, nullptr, nullptr, entity_));
	air_hard_punch_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(27, nullptr, ANK1, entity_));
	vecMov.push_back(new Move(22, nullptr, ANK2, entity_));
	vecMov.push_back(new Move(39, nullptr, nullptr, entity_));
	air_normal_kick_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(32, nullptr, AHK1, entity_));
	vecMov.push_back(new Move(55, nullptr, nullptr, entity_));
	air_hard_kick_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(30, nullptr, GB, entity_));
	vecMov.push_back(new Move(50, nullptr, nullptr, entity_));
	guard_breaker_ = new AnimationChain(vecMov);
	vecMov.clear();
}
void MkWH00PData::NP1(Entity* ent)
{
#ifdef _DEBUG
	std::cout << "Uppercut" << endl;
#endif 
	double hitbox_X = np1.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += np1.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, np1.position.getY() }, np1.width, np1.height, np1.time, pD->getAttack() * np1.damage, np1.hitstun, { (double)orientation_ * np1.knockBack.getX(), np1.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::PUNCH), false);

}

PlayerData::CallbackData MkWH00PData::np1 = PlayerData::CallbackData{
	{ 100, -150 },
	{ 300, -360 },
	150,
	200,
	20,
	9,
	42
};

void MkWH00PData::HP1(Entity* ent)
{
#ifdef _DEBUG
	std::cout << "Hostia" << endl;
#endif 

	double hitbox_X = hp1.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += hp1.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, hp1.position.getY() }, hp1.width, hp1.height, hp1.time, pD->getAttack() * hp1.damage, hp1.hitstun, { (double)orientation_ * hp1.knockBack.getX(), hp1.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::KICK), false);

}

PlayerData::CallbackData MkWH00PData::hp1 = PlayerData::CallbackData{
	{ 115, -85 },
	{ 40, 0 },
	125,
	150,
	17,
	15,
	55 };

void MkWH00PData::NK1(Entity* ent)
{
#ifdef _DEBUG
	std::cout << "Rodilla 1" << endl;
#endif 

	double hitbox_X = nk1.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += nk1.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, nk1.position.getY() }, nk1.width, nk1.height, nk1.time, pD->getAttack() * nk1.damage, nk1.hitstun, { (double)orientation_ * nk1.knockBack.getX(), nk1.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::ATAQUE), false);


}

PlayerData::CallbackData MkWH00PData::nk1 = PlayerData::CallbackData{
	{ 105, 90 },
	{ 25, -25 },
	95,
	130,
	20,
	9,
	42};

void MkWH00PData::NK2(Entity* ent)
{
#ifdef _DEBUG
	std::cout << "Rodilla 2" << endl;
#endif 
	double hitbox_X = nk2.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += nk2.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, nk2.position.getY() }, nk2.width, nk2.height, nk2.time, pD->getAttack() * nk2.damage, nk2.hitstun, { (double)orientation_ * nk2.knockBack.getX(), nk2.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::ATAQUE2), false);

}

PlayerData::CallbackData MkWH00PData::nk2 = PlayerData::CallbackData{
	{ 133, 100 },
	{ 500, -150 },
	110,
	125,
	17,
	6,
	35 };

void MkWH00PData::HK1(Entity* ent)
{
#ifdef _DEBUG
	std::cout << "Falcon stomp" << endl;
#endif 
	double hitbox_X1 = hk1.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1) {
		hitbox_X1 += hk1.width;
	}
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X1, hk1.position.getY() }, hk1.width, hk1.height, hk1.time, pD->getAttack() * hk1.damage, hk1.hitstun, { (double)orientation_ * hk1.knockBack.getX(), hk1.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::KICK), false);

}

PlayerData::CallbackData MkWH00PData::hk1 = PlayerData::CallbackData{
	{ 115, 95 },
	{ 50, 500 },
	110,
	170,
	17,
	17,
	50 };

void MkWH00PData::HK2(Entity* ent)
{
#ifdef _DEBUG
	std::cout << "S(C)ockwave" << endl;
#endif // _DEBUG

	GameState* currentState = ent->getApp()->getStateMachine()->getCurrentState();
	Texture* texture = ent->getApp()->getAssetsManager()->getTexture(AssetsManager::MkHk);
	PhysicsTransform* phtr = ent->getComponent<PhysicsTransform>(ecs::Transform);

	uint16 mask;
	int orientation_ = ent->getComponent<Transform>(ecs::Transform)->getOrientation();

	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	if (pD->getPlayerNumber() == 0) {
		mask = currentState->PLAYER_2;
	}
	else {
		mask = currentState->PLAYER_1;
	}

	double projX = phtr->getPosition().getX() + (phtr->getWidth() * 3 / 4) + (hk2.width / 2) + hk2.position.getX();
	if (orientation_ == -1) projX = phtr->getPosition().getX() + (phtr->getWidth() * 1 / 4) - (hk2.width / 2) - hk2.position.getX();

	Vector2D pos = Vector2D(projX, phtr->getPosition().getY() + hk2.position.getY());
	DestroyAtTime* dT = new DestroyAtTime(hk2.damage, hk2.time, hk2.hitstun, { (double)orientation_ * hk2.knockBack.getX(), hk2.knockBack.getY() }, false, pD->getPlayerNumber(), ent);
	/*AbilityFactory::createProyectile(ent, hk2.width, hk2.height, pos, { 0, -0.7 }, hk2.damage, hk2.hitstun, { (double)orientation_ * hk2.knockBack.getX(), hk2.knockBack.getY() },
		hk1.time, mask, ent->getState(), ent->getApp(), texture, false);*/
	AbilityFactory::instanceEntitywHitbox(ent, hk2.width, hk2.height, pos, { 0, -0.5 }, mask, ent->getState(), ent->getApp(), texture, orientation_, dT);

}

PlayerData::CallbackData MkWH00PData::hk2 = PlayerData::CallbackData{
	{ -75, 500 },
	{ 7.5, -4.5 },
	375,
	55,
	20,
	5,
	40 };

void MkWH00PData::ANP1(Entity* ent)
{
#ifdef _DEBUG
	std::cout << "Speeeee-" << endl;
#endif 
	double hitbox_X = anp1.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += anp1.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, anp1.position.getY() }, anp1.width, anp1.height, anp1.time, pD->getAttack() * anp1.damage, anp1.hitstun, { (double)orientation_ * anp1.knockBack.getX(), anp1.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::GANCHO), false);
	
}
PlayerData::CallbackData MkWH00PData::anp1 = PlayerData::CallbackData{
	{ -200, -50 },
	{ 10, -55 },
	420,
	130,
	35,
	5,
	16 };

void MkWH00PData::ANP2(Entity* ent)
{
#ifdef _DEBUG
 
	std::cout << "-eeeeeeen" << endl;
#endif
	double hitbox_X = anp2.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += anp2.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, anp2.position.getY() }, anp2.width, anp2.height, anp2.time, pD->getAttack() * anp2.damage, anp2.hitstun, { (double)orientation_ * anp2.knockBack.getX(), anp2.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
}
PlayerData::CallbackData MkWH00PData::anp2 = PlayerData::CallbackData{
	{ -200, -40 },
	{ 750, -500},
	420,
	130,
	35,
	8,
	30 };

void MkWH00PData::AHP1(Entity* ent)
{
#ifdef _DEBUG
	std::cout << "Get spiked son" << endl;
#endif 
	double hitbox_X = ahp1.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += ahp1.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, ahp1.position.getY() }, ahp1.width, ahp1.height, ahp1.time, pD->getAttack() * ahp1.damage, ahp1.hitstun, { (double)orientation_ * ahp1.knockBack.getX(), ahp1.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::PUNCH), false);

}
PlayerData::CallbackData MkWH00PData::ahp1 = PlayerData::CallbackData{
	{ 110, 50 },
	{ 250, 1000 },
	130,
	200,
	25,
	22,
	65 };

void MkWH00PData::ANK1(Entity* ent)
{
#ifdef _DEBUG
	std::cout << "Steppy" << endl;
#endif 
	double hitbox_X = ank1.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += ank1.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, ank1.position.getY() }, ank1.width, ank1.height, ank1.time, pD->getAttack() * ank1.damage, ank1.hitstun, { (double)orientation_ * ank1.knockBack.getX(), ank1.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::ATAQUE2), false);

}

PlayerData::CallbackData MkWH00PData::ank1 = PlayerData::CallbackData{
	{ 105, 135 },
	{ 5, 0 },
	145,
	120,
	17,
	4,
	15 };

void MkWH00PData::ANK2(Entity* ent)
{
#ifdef _DEBUG
	std::cout << "STEPPY!!!" << endl;
#endif 
	double hitbox_X = ank2.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += ank2.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, ank2.position.getY() }, ank2.width, ank2.height, ank2.time, pD->getAttack() * ank2.damage, ank2.hitstun, { (double)orientation_ * ank2.knockBack.getX(), ank2.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::ATAQUE2), false);

}
PlayerData::CallbackData MkWH00PData::ank2 = PlayerData::CallbackData{
	{ 105, 125 },
	{ 350, 0 },
	145,
	135,
	17,
	10,
	43 };

void MkWH00PData::AHK1(Entity* ent)
{
#ifdef _DEBUG
	std::cout << "Dropkick" << endl;
#endif 
	double hitbox_X = ahk1.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += ahk1.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, ahk1.position.getY() }, ahk1.width, ahk1.height, ahk1.time, pD->getAttack() * ahk1.damage, ahk1.hitstun, { (double)orientation_ * ahk1.knockBack.getX(), ahk1.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::KICK), false);

	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::ATAQUE), false);

}
PlayerData::CallbackData MkWH00PData::ahk1 = PlayerData::CallbackData{
	{ 50, -50 },
	{ 400, 0 },
	250,
	200,
	50,
	18,
	55 };

void MkWH00PData::GB(Entity* ent)
{
#ifdef _DEBUG
	std::cout << "BreakerGuard" << endl;
#endif 
	double hitbox_X = gb.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += gb.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, gb.position.getY() }, gb.width, gb.height, gb.time, pD->getAttack() * gb.damage, gb.hitstun, { (double)orientation_ * gb.knockBack.getX(), gb.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask(), true);
	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::GBMKW00P), false);

}
PlayerData::CallbackData MkWH00PData::gb = PlayerData::CallbackData{
	{ 70, -140 },
	{ 0, 0 },
	170,
	170,
	15,
	0,
	100};
