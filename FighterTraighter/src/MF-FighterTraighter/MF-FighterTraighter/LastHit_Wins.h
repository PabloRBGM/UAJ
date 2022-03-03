#pragma once
#include "PunchingBagOnHit.h"

/*
* The player that kills the Punching Bag is the one who wins
* If its a draw, he last player that hit the Punching Bag is the one who wins
*/

class LastHit_Wins : public PunchingBagOnHit
{
public:
	LastHit_Wins(Entity* e) : PunchingBagOnHit(e) {}
	~LastHit_Wins() {}
	void onHit(b2Fixture* other) override;
	int timeout_Winner() override;
private:
	int last_hit = -1;
};

