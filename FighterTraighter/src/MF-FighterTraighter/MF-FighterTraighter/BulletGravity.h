#pragma once
#include "Bullet.h"
class BulletGravity : public Bullet
{
public:
	BulletGravity(uint16 playernumber, HitboxData* onhit, Vector2D speed=Vector2D(0,0));
	virtual ~BulletGravity() {}
	//void init() override;
	void update() override;
	//void update() override;
	void changeSpeed(const Vector2D& newSpeed) { speed_ = newSpeed; }
	Vector2D getSpeed() { return speed_; }

};

