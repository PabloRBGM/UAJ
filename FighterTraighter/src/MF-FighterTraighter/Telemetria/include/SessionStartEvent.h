#pragma once
#include "TrackerEvent.h"

class SessionStartEvent : public TrackerEvent
{
public:
	SessionStartEvent( time_t timestamp);
	std::string toJSON() const override;
};

