#pragma once
#include "TrackerEvent.h"
class AbilityEvent : public TrackerEvent
{
public:
	AbilityEvent(time_t timestamp, Characters characters, Abilities ability, Players playerId);
	std::string toJSON() const override;
private:
	Characters _character;
	Abilities _ability;
	Players _playerID;
};
