#pragma once
#include "TrackerEvent.h"

class SessionEndEvent :  public TrackerEvent
{
public:
	SessionEndEvent(time_t timestamp);
	std::string toJSON() const override;
};

