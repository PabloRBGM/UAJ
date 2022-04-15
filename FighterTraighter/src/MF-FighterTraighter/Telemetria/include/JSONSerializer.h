#pragma once
#include "ISerializer.h"

class JSONSerializer : public ISerializer {
public:
	JSONSerializer() {}
	virtual ~JSONSerializer() {}
	std::string serialize(const TrackerEvent& tracker) override;
};