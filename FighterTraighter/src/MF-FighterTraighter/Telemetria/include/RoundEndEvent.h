#pragma once
#include "TrackerEvent.h"

class RoundEndEvent :
    public TrackerEvent
{
public:
	RoundEndEvent(time_t timestamp, Characters characters[NUM_PLAYERS], Players winner);
	std::string toJSON() const override;
private:
	Characters _characters[NUM_PLAYERS];
	Players _winner;
};

