#pragma once
#include <string>
class TrackerEvent;

class ISerializer
{
	ISerializer(const ISerializer&) = delete;
	ISerializer& operator= (const ISerializer&) = delete;
	ISerializer(ISerializer&&) = delete;
	ISerializer& operator= (ISerializer&&) = delete;
protected:
	ISerializer() {}
public:
	virtual ~ISerializer() {}
	std::string virtual serialize(const TrackerEvent& tracker) = 0;
}; 
