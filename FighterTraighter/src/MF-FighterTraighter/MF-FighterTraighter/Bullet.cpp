#include "Bullet.h"
#include "DestroyOnHit.h"
Bullet::Bullet(uint16 playernumber,HitboxData* onHit,Vector2D speed) :
	Component(ecs::Bullet), onHit_(onHit),  playerNumber_(playernumber), speed_(speed){
}
void Bullet::init()
{
	transform_ = entity_->getComponent<PhysicsTransform>(ecs::Transform);
	transform_->setSpeed(speed_);
	//	EntityHitboxData(Entity* e, int damage, int time, int hitstun, Vector2D knockback, bool guardbreaker, bool destroyOnHit = false) : 
	//cout << damage_ << endl;
	//DestroyOnHit* hitbox_ = new DestroyOnHit(damage_,timeAlive_, hitstun_, knockBack_,false, playerNumber_, entity_, destroyInContact_);//create the hitbox's data
	transform_->resetUserData(onHit_);
	entity_->getState()->addHitbox(playerNumber_,onHit_,transform_->getMainFixture());

}