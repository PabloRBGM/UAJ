#pragma once
#include "GameState.h"
#include "App.h"
class CharacterSelection: public GameState
{

public:

	//constructor
	CharacterSelection(App* app, int numPlayer) : GameState(app),numPlayer_(numPlayer) { init(); }
	virtual ~CharacterSelection() {}
	void init() override;
	void handleInput() override;
private:
	int numPlayer_;
	string mkwhoop_desc= "MKW00P: Has a slow and powerfull playstyle, with hard hits and high push and a lot of live points.";
	string aisha_desc= "Aisha: Has a balanced playstyle, not specialy fast or slow, with aerial attacks specialy skillfull. Has medium live points.";
	string flor_desc= "F10R: Is a range attacks character, able to keep distance with the enemy. It does not have very much live points.";
	string mock_desc = "MockingBird: Has fast attacks but not very powerful. His playstyle is about combos and velocity. His live points are low.";

};

