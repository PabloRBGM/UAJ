#pragma once
#include "UserData.h"
#include "FightController.h"
class PlayerOnHit : public UserData
{
public:
	PlayerOnHit(Entity* e) : UserData(e) {}
	virtual ~PlayerOnHit() {}
	virtual void onHit(b2Fixture* fixture) override;
};

