#pragma once
#include "Component.h"
class FightController :
	public Component
{
public:
	FightController(int roundIniTime, int roundEndTime, int playerNumber=2) : Component(ecs::FightController), ini_timer(roundIniTime), roundEndTime_(roundEndTime),playerNumber_(playerNumber) {}

	void init() override;
	void update() override;

	virtual void PlayerLost(int playerNumber);

	virtual ~FightController() {}
protected:
	int playerLost_ = -2; // -2 = round is still going, -1 = tie, 0 = leftPlayer, 1 = rightPlayer

	Entity* msgEnt = nullptr;
	bool showInitialMessage = true;
	int roundEndTime_;
	int end_timer = 0;
	int ini_timer = 0;
	virtual void end();
	//allows the players to perform any action
	virtual void disablePlayers(bool mode);

	//displays a message in the middle of the screen
	void displayMessage(string msg);
	int playerNumber_ = 2;
};

