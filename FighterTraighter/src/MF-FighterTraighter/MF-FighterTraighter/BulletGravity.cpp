#include "BulletGravity.h"

BulletGravity::BulletGravity(uint16 playernumber, HitboxData* onhit, Vector2D speed) :
	Bullet(playernumber, onhit,speed)
{

}
//void BulletGravity::init() {
//	Bullet::init();
//}

void BulletGravity::update()
{
	speed_.setY(speed_.getY() + 0.1);
	transform_->setSpeed(speed_);
}
