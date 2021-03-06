#pragma once
#include "PlayerData.h"

class F10RData : public PlayerData
{
public:
	F10RData(double width, double height, double rotation, double jump_impulse, Vector2D ini_pos, double speed, double ini_health, double attack, double defense, int playerNumber);
	virtual ~F10RData() {}
	void init() override;
private:
	static void NP1(Entity* ent);
	static CallbackData np1;

	static void HP1(Entity* ent);
	static CallbackData hp1;

	static void NK1(Entity* ent);
	static CallbackData nk1;

	static void HK1(Entity* ent);
	static CallbackData hk1;

	static void ANP1(Entity* ent);
	static CallbackData anp1;

	static void AHP1(Entity* ent);
	static CallbackData ahp1;

	static void ANK1(Entity* ent);
	static CallbackData ank1;

	static void AHK1(Entity* ent);
	static CallbackData ahk1;

	static void GB(Entity* ent);
	static CallbackData gb;
};