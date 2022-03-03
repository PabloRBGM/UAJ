#pragma once
#include "FightController.h"
class Iv1Controller : public FightController
{

public:
	Iv1Controller(int roundIniTime, int roundEndTime) : FightController(roundIniTime, roundEndTime) {}

	void init() override;
	void update() override;

	void PlayerLost(int playerNumber) override;
	
	virtual ~Iv1Controller() {}
protected:
	void end() override;
	void disablePlayers(bool mode) override;
//	int playerLost_ = -2; // -2 = round is still going, -1 = tie, 0 = leftPlayer, 1 = rightPlayer
//
//	Entity* msgEnt = nullptr;
//	bool showInitialMessage = true;
//	int roundEndTime_;
//	int end_timer = 0;
//	int ini_timer = 0;
//
//	//allows the players to perform any action
//	void disablePlayers(bool mode);
//
//	//displays a message in the middle of the screen
//	void displayMessage(string msg);
};

