#pragma once
#include <list>

#include "Singleton.h"
#include "IPersistence.h"
#include <string>
class Tracker: public Singleton<Tracker>
{
	friend Singleton<Tracker>;
private:
	IPersistence* persistenceObject;
	std::string currSession;	
public:
	~Tracker();
	void init();
	void trackEvent(TrackerEvent* event);
	void flushPersistence();
	inline std::string getSessionID() { return currSession; }
};