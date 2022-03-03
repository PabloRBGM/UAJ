#include "MockingbirdData.h"
#include "PlayerParticleSystem.h"

MockingbirdData::MockingbirdData(double width, double height, double rotation, double jump_impulse, Vector2D ini_pos, double speed, double ini_health, double attack, double defense, int playerNumber) :
	PlayerData(width, height, rotation, jump_impulse, ini_pos, speed, ini_health, attack, defense, playerNumber)
{
	animLength_ = { {4, true, 12}, {6, true, 10}, {2, true, 3}, {2, true, 15}, {2, false, 2}, {4, false, 10}, {4, false, 10}, {6, false, 8},
	{5, false, 10}, {3, false, 7}, {6, false, 7}, {3, false, 7}, {5, false, 11}, {2, true, 15}, {1, false, 10}, {1, true, 4}, {1, false, 10},
	{2, false, 3}, {2, true, 12}, {2, false, 7}, {3, false, 15}, {2, false, 15}, {2, false, 10} };
}

void MockingbirdData::init()
{
	std::vector<Move*> vecMov;

	vecMov.push_back(new Move(20, nullptr, NP1, entity_));
	vecMov.push_back(new Move(14, nullptr, nullptr, entity_));
	normal_punch_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(18, nullptr, HP1, entity_));
	vecMov.push_back(new Move(36, nullptr, nullptr, entity_));
	hard_punch_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(20, nullptr, NK1, entity_));
	vecMov.push_back(new Move(32, nullptr, nullptr, entity_));
	normal_kick_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(30, nullptr, HK1, entity_));
	vecMov.push_back(new Move(6, nullptr, nullptr, entity_));
	hard_kick_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(9, nullptr, ANP1, entity_));
	vecMov.push_back(new Move(34, nullptr, nullptr, entity_));
	air_normal_punch_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(12, nullptr, AHP1, entity_));
	vecMov.push_back(new Move(6, nullptr, AHP1, entity_));
	vecMov.push_back(new Move(19, nullptr, AHP2, entity_));
	vecMov.push_back(new Move(20, nullptr, nullptr, entity_));
	air_hard_punch_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(10, nullptr, ANK1, entity_));
	vecMov.push_back(new Move(24, nullptr, nullptr, entity_));
	air_normal_kick_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(18, nullptr, AHK1, entity_));
	vecMov.push_back(new Move(40, nullptr, nullptr, entity_));
	air_hard_kick_ = new AnimationChain(vecMov);
	vecMov.clear();

	vecMov.push_back(new Move(35, nullptr, GB, entity_));
	vecMov.push_back(new Move(40, nullptr, nullptr, entity_));
	guard_breaker_ = new AnimationChain(vecMov);
	vecMov.clear();
}

void MockingbirdData::NP1(Entity* ent)
{
#ifdef _DEBUG
	std::cout << "stab" << endl;
#endif 
	double hitbox_X = np1.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += np1.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, np1.position.getY() }, np1.width, np1.height, np1.time, pD->getAttack() * np1.damage, np1.hitstun, { (double)orientation_ * np1.knockBack.getX(), np1.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::DASH), false);

}

PlayerData::CallbackData MockingbirdData::np1 = PlayerData::CallbackData{
	{ 125, -75 },
	{50, 0},
	120,
	90,
	10,
	2,
	25
};

void MockingbirdData::HP1(Entity* ent)
{
#ifdef _DEBUG
 
	std::cout << "pipe" << endl;
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

PlayerData::CallbackData MockingbirdData::hp1 = PlayerData::CallbackData{
	{ 125, -200 },
	{ 700, 0 },
	150,
	250,
	5,
	6,
	36
};

void MockingbirdData::NK1(Entity* ent)
{
#ifdef _DEBUG
	std::cout << "shoot" << endl;
#endif 
	double hitbox_X = nk1.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += nk1.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, nk1.position.getY() }, nk1.width, nk1.height, nk1.time, pD->getAttack() * nk1.damage, nk1.hitstun, { (double)orientation_ * nk1.knockBack.getX(), nk1.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::NORMALPUNCH), false);

}

PlayerData::CallbackData MockingbirdData::nk1 = PlayerData::CallbackData{
	{ 125, -90 },
	{100, 0},
	270,
	75,
	5,
	3,
	12
};

void MockingbirdData::HK1(Entity* ent)
{
#ifdef _DEBUG
	std::cout << "knees" << endl;
#endif 
	double hitbox_X = hk1.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += hk1.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, hk1.position.getY() }, hk1.width, hk1.height, hk1.time, pD->getAttack() * hk1.damage, hk1.hitstun, { (double)orientation_ * hk1.knockBack.getX(), hk1.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::LANZAR4), false);

}

PlayerData::CallbackData MockingbirdData::hk1 = PlayerData::CallbackData{
	{ 125, 100 },
	{ 250, -850 },
	200,
	150,
	12,
	4,
	31
};



void MockingbirdData::ANP1(Entity* ent)
{
#ifdef _DEBUG
	std::cout << "chop" << endl;
#endif 
	double hitbox_X = anp1.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += anp1.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, anp1.position.getY() }, anp1.width, anp1.height, anp1.time, pD->getAttack() * anp1.damage, anp1.hitstun, { (double)orientation_ * anp1.knockBack.getX(), anp1.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::HIT2), false);

}

PlayerData::CallbackData MockingbirdData::anp1 = PlayerData::CallbackData{
	{ 125, -75 },
	{ 80, 0 },
	160,
	180,
	12,
	2,
	20
};

void MockingbirdData::AHP1(Entity* ent)
{
#ifdef _DEBUG
	std::cout << "stab" << endl;
#endif 
	double hitbox_X = ahp1.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += ahp1.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, ahp1.position.getY() }, ahp1.width, ahp1.height, ahp1.time, pD->getAttack() * ahp1.damage, ahp1.hitstun, { (double)orientation_ * ahp1.knockBack.getX(), ahp1.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::KNIFE), false);

}

PlayerData::CallbackData MockingbirdData::ahp1 = PlayerData::CallbackData{
	{ 125, -40 },
	{10, 0},
	150,
	75,
	5,
	2,
	10
};

void MockingbirdData::AHP2(Entity* ent)
{
#ifdef _DEBUG
	std::cout << "staab" << endl;
#endif 
	double hitbox_X = ahp2.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += ahp2.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, ahp2.position.getY() }, ahp2.width, ahp2.height, ahp2.time, pD->getAttack() * ahp2.damage, ahp2.hitstun, { (double)orientation_ * ahp2.knockBack.getX(), ahp2.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::KNIFE), false);

}

PlayerData::CallbackData MockingbirdData::ahp2 = PlayerData::CallbackData{
	{ 125, -30 },
	{20, 0},
	150,
	75,
	8,
	3,
	12
};

void MockingbirdData::ANK1(Entity* ent)
{
#ifdef _DEBUG
 	std::cout << "slash" << endl;
#endif	
	double hitbox_X = ank1.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += ank1.width;
	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, ank1.position.getY() }, ank1.width, ank1.height, ank1.time, pD->getAttack() * ank1.damage, ank1.hitstun, { (double)orientation_ * ank1.knockBack.getX(), ank1.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());
	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::KNIFE), false);

}

PlayerData::CallbackData MockingbirdData::ank1 = PlayerData::CallbackData{
	{ 125, 70 },
	{ 10, -150 },
	250,
	85,
	15,
	2,
	8
};

void MockingbirdData::AHK1(Entity* ent)
{
#ifdef _DEBUG
	std::cout << "petard" << endl;
#endif 
	double hitbox_X = ahk1.position.getX();
	PhysicsTransform* pT = ent->getComponent<PhysicsTransform>(ecs::Transform);
	PlayerData* pD = ent->getComponent<PlayerData>(ecs::PlayerData);
	int orientation_ = pT->getOrientation();
	if (orientation_ == -1)
		hitbox_X += ahk1.width;

	ent->getApp()->getStateMachine()->getCurrentState()->addHitbox(
		{ (double)orientation_ * hitbox_X, ahk1.position.getY() }, ahk1.width, ahk1.height, ahk1.time, pD->getAttack() * ahk1.damage, ahk1.hitstun, { (double)orientation_ * ahk1.knockBack.getX(), ahk1.knockBack.getY() }, pT->getBody(), pD->getPlayerNumber(), ent, pT->getCategory(), pT->getMask());

	double partX = pT->getWidth() * 3 / 4 - 20;
	if (orientation_ == -1) partX = pT->getWidth() / 4 - 200 + 20;
	Vector2D pos = Vector2D(partX, 200);

	ent->getComponent<PlayerParticleSystem>(ecs::PlayerParticleSystem)->addNewParticle(ent->getApp()->getAssetsManager()->getTexture(AssetsManager::MockAHK),
		pos, Vector2D(200, 200), 20, PlayerParticleSystem::DeletionMethod::OnHit);
		
	ent->getApp()->getAudioMngr()->playSFX(ent->getApp()->getAssetsManager()->getSFX(AssetsManager::ROCAS), false);

}

PlayerData::CallbackData MockingbirdData::ahk1 = PlayerData::CallbackData{
	{ 125, -40 },
	{100, 1000},
	200,
	200,
	20,
	8,
	30
};

void MockingbirdData::GB(Entity* ent)
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
}
PlayerData::CallbackData MockingbirdData::gb = PlayerData::CallbackData{
	{ 125, -75 },
	{ -80, -50 },
	250,
	150,
	10,
	0,
	85 };