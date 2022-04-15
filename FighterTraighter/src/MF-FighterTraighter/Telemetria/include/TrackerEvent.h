#pragma once
#include "EventData.h"
#include <string>

class TrackerEvent
{
protected:
	TrackerEvent(EventType type_, time_t timestamp_, std::string sessionID_);
	TrackerEvent(EventType type_, time_t timestamp_);
	EventType _type;
	time_t _timestamp;
	std::string _sessionID;
public:
	virtual std::string toJSON() const;
	std::string baseInfo() const;
};