#pragma once
#include "PlayerData.h"
class MkWH00PData : public PlayerData
{
public:
	MkWH00PData(double width, double height, double rotation, double jump_impulse, Vector2D ini_pos, double speed, double ini_health, double attack, double defense, int playerNumber);
	virtual ~MkWH00PData() {}
	void init() override;
private:
	//Static callbacks to generate hitboxes, if both player choose the same player, their attacks are the same, the values that 
	//change are PlayerData non static values (attack, deffense...)

	static void NP1(Entity* ent);
	static CallbackData np1;

	static void HP1(Entity* ent);
	static CallbackData hp1;

	static void NK1(Entity* ent);
	static CallbackData nk1;

	static void NK2(Entity* ent);
	static CallbackData nk2;

	static void HK1(Entity* ent);
	static void HK2(Entity* ent);
	static CallbackData hk1;
	static CallbackData hk2;

	static void ANP1(Entity* ent);
	static CallbackData anp1;

	static void ANP2(Entity* ent);
	static CallbackData anp2;

	static void AHP1(Entity* ent);
	static CallbackData ahp1;

	static void ANK1(Entity* ent);
	static CallbackData ank1;

	static void ANK2(Entity* ent);
	static CallbackData ank2;

	static void AHK1(Entity* ent);
	static CallbackData ahk1;

	static void GB(Entity* ent);
	static CallbackData gb;
};

