#pragma once
#include "Component.h"

//Component to control the training,
//it handles the initial wait message and the
//end message of the training part
//stopping the players during this messages
class TrainingController : public Component
{
public:
	TrainingController(int roundIniTime, int roundEndTime) : Component(ecs::TrainingController), ini_timer(roundIniTime), roundEndTime_(roundEndTime) {}

	void init() override;
	void update() override;

	void PlayerWins(int playerNumber);
	//void setIniText(string it);
	virtual ~TrainingController() {}
protected:
	int playerWins_ = -1; // -1 = round is still going, 0 = leftPlayer, 1 = rightPlayer
	Entity* msgEnt = nullptr;
	bool showInitialMessage = true;
	int roundEndTime_;
	int end_timer = 0;
	int ini_timer = 0;

	//allows the players to perform any action
	void disablePlayers(bool mode);

	//displays a message in the middle of the screen
	void displayMessage(string msg);
};

