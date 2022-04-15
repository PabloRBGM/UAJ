#pragma once
#include "TrackerEvent.h"
class AttackEvent :    public TrackerEvent
{
public:
	AttackEvent(time_t timestamp, Characters characters, Attacks attack, Players playerId);
	std::string toJSON() const override;
private:
	Characters _character;
	Attacks _attack;
	Players _playerID;
};

