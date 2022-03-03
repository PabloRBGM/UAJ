#pragma once
#include "Component.h"
#include "PhysicsTransform.h"
#include "HitboxData.h"
#include "Entity.h"
class Bullet : public Component
{
public:
	Bullet(uint16 playernumber,HitboxData* onhit, Vector2D speed=Vector2D(0,0));
	virtual ~Bullet() {}
	virtual void init() override;
	int getPlayerNumber() { return playerNumber_; }
protected:
	PhysicsTransform* transform_ = nullptr;
	Vector2D speed_;
	HitboxData* onHit_;

	int playerNumber_;
};

