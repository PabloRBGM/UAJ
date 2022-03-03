#pragma once
#include "PunchingBagOnHit.h"
class MoreDamage_Wins : public PunchingBagOnHit
{
public:
	MoreDamage_Wins(Entity* e) : PunchingBagOnHit(e) {}
	~MoreDamage_Wins() {}
	void onHit(b2Fixture* other) override;
	int timeout_Winner() override;
private:
	double	p1_damage = 0,
			p2_damage = 0;

	int computeWinner();
};

