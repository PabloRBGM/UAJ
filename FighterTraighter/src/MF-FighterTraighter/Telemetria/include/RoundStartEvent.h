#pragma once
#include "TrackerEvent.h"

class RoundStartEvent :
    public TrackerEvent
{
public:
	RoundStartEvent(time_t timestamp, Characters characters[NUM_PLAYERS], Abilities abilities[NUM_PLAYERS][NUM_ABILITIES]);
	std::string toJSON() const override;
private:
	Characters _characters[NUM_PLAYERS];
	Abilities _abilities[NUM_PLAYERS][NUM_ABILITIES];
};

