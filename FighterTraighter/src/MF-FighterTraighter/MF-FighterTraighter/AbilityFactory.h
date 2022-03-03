#pragma once
#include "AnimationChain.h"
#include "GameManager.h"
#include <functional>
#include <map>

class HitboxData;
class RenderImage;
class AbilityFactory {
public:
	static AnimationChain* GiveAbility(GameManager::AbilityID id, Entity* e);

	//Megaton Grip
	static AnimationChain* GiveMegatonGrip(Entity* e);

	static void MG1(Entity* ent);
	static void MG2(Entity* ent);
	static void MGC(Entity* ent);

	//Seismic Shock
	static AnimationChain* GiveSeismicShock(Entity* e);

	static void SeismicS1(Entity* e);	//kick
	static void SeismicS2(Entity* ent);	//rock going up
	static void SeismicS3(Entity* ent);	//punches going down
	static void SeismicSC(Entity* ent);	//go cd

	//Explosive Willpower
	static AnimationChain* GiveExplosiveWillpower(Entity* e);

	static void EWC(Entity* ent);
	static void EW1(Entity* ent);

	//Acid Split
	static AnimationChain* GiveAcidSplit(Entity* e);

	static void AS1(Entity* ent);
	static void ASC(Entity* ent);

	//Mina
	static AnimationChain* GiveMina(Entity* e);

	static void M1(Entity* ent);
	static void MC(Entity* ent);

	//Pollo
	static AnimationChain* GivePollo(Entity* e);

	static void PO1(Entity* ent);
	static void POC(Entity* ent);

	//Shrug Off
	static AnimationChain* GiveShrugOff(Entity* e);

	static void SO1(Entity* ent);
	static void SOC(Entity* ent);

	//More Power
	static AnimationChain* GiveMorePower(Entity* e);

	static void MP1(Entity* ent);
	static void MPC(Entity* ent);

	//Hookshot
	static AnimationChain* GiveHookshot(Entity* e);

	static void HS1(Entity* ent);
	static void HSC(Entity* ent);

	//Dash
	static AnimationChain* GiveDash(Entity* e);

	static void Dash(Entity* ent);
	static void DashC(Entity* ent);

	//Vampiric Strike
	static AnimationChain* GiveVampiricStrike(Entity* e);

	static void VS1(Entity* ent);
	static void VSC(Entity* ent);

	//Hail Shard
	static AnimationChain* GiveHailBall(Entity* e);

	static void HB1(Entity* ent);
	static void HBC(Entity* ent);

	//Reaching Strike
	static AnimationChain* GiveReachingStrike(Entity* e);

	static void RS1(Entity* ent);
	static void RSC(Entity* ent);

	//FlyingKicks
	static AnimationChain* GiveFlyingKicks(Entity* e);

	static void FK1(Entity* ent);
	static void FK2(Entity* ent);
	static void FK3(Entity* ent);
	static void FK4(Entity* ent);
	static void FKC(Entity* ent);

	//LaserLineal
	static AnimationChain* GiveLaserLineal(Entity* e);

	static void LL1(Entity* ent);
	static void LLC(Entity* ent);

	//Nado Kick
	static AnimationChain* GiveNadoKick(Entity* e);

	static void NK1(Entity* ent);
	static void NK2(Entity* ent);
	static void NK3(Entity* ent);
//	static void NKF(Entity* ent);
	static void NKC(Entity* ent);


	//Knock Down
	static AnimationChain* GiveKnockDown(Entity* e);

	static void KD1(Entity* ent);
	static void KD2(Entity* ent);
	static void KDC(Entity* ent);

	static Entity* instanceEntitywHitbox(Entity* ent, double width, double height, Vector2D pos, Vector2D speed, uint16 mask, GameState* currentState, App* app, Texture* texture, int orientation, HitboxData* uData, bool gravity = false, bool render=false);
	
	//static Entity* createProyectile(Entity* ent, double width, double height, Vector2D pos, Vector2D speed, int damage, int hitstun,
		//Vector2D knockBack, int time, uint16 mask, GameState* currentState, App* app, Texture* texture, int orientation, bool destroyInContact = false, bool gravity = false, bool multihit = false);
private: 

	AbilityFactory() {};
	~AbilityFactory() {};
	static void goOnCoolodwn(Entity* e, int cool);
	static std::map<GameManager::AbilityID, std::function<AnimationChain* (Entity*)>> abilities_map;
};