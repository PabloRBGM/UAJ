#pragma once
#pragma once
#include "HID.h"
#include <SDL.h>
class AIHID :
	public HID
{
public:
	AIHID() {}
	void updateInput();
	~AIHID() {};
protected:
};