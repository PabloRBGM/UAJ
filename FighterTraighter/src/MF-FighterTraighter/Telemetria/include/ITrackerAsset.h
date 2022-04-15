#pragma once
#include "TrackerEvent.h"

class ITrackerAsset
{
public:
	ITrackerAsset() = delete;
	ITrackerAsset(const ITrackerAsset&) = delete;
	ITrackerAsset& operator= (const ITrackerAsset&) = delete;
	ITrackerAsset(ITrackerAsset&&) = delete;
	ITrackerAsset& operator= (ITrackerAsset&&) = delete;
	~ITrackerAsset() = delete;
	/// <summary>
	/// Permite el paso a eventos aceptados
	/// </summary>
	virtual bool accept(TrackerEvent trackerEvent) = 0;
};