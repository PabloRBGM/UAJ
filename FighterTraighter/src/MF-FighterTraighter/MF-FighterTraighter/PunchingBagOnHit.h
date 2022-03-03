#pragma once
#include "UserData.h"

//The punchingBag only has Datas that are subClasses of this
class PunchingBagOnHit : public UserData
{
public:
	PunchingBagOnHit(Entity* e) : UserData(e){}
	~PunchingBagOnHit() {}
	//Decide the player who is the winner when its a draw
	virtual int timeout_Winner() = 0;
};

