#pragma once
#include "UserData.h"
#include "Vector2D.h"

class HitboxData :  public UserData
{
public:
	HitboxData(double damage, int time, int hitstun, Vector2D knockback, bool guardbreaker, int id, Entity* e, bool mHit = false, bool proy = false) : UserData(e),
		damage_(damage), time_(time), hitstun_(hitstun), knockBack_(knockback), guardBreaker_(guardbreaker), id_(id), multiHit_(mHit), proyectile_(proy){}
	virtual ~HitboxData() {}
	virtual void onHit(b2Fixture* other) {
		if (!multiHit_ && !destroy_) {			
			entity_->getState()->killHitbox(it_, id_);
			destroy_ = true;
		}
	}
	void setIt(std::list<b2Fixture*>::iterator i) {
		it_ = i;
	}

	//returns true if the hitbox lifetime is over and kills the hitbox
	//updates te hitbox damage timer if it is a multihit 
	virtual void update() {
		if(--time_ <= 0 && !destroy_)
		{
			entity_->getState()->killHitbox(it_, id_);
			destroy_ = true;
		}
		if (multiHit_) {
			if(doesDamage())
				aux_frec = damage_frec;
			else
				aux_frec = max(0, aux_frec - 1);
		}
	}

	//use this method to check if the hitbox can do damage
	//if a hitbox is not multiHit, it does damage everytime
	//if not,it does damage every "damage_frec" frames while the hitbox is alive
	virtual bool doesDamage() {
		return aux_frec == 0;
	}
	//Establish the hitbox as a multiHit that hits every frame_time
	virtual void enableMultiHit(int frame_time) {
		multiHit_ = true;
		damage_frec = frame_time;
	}
	//Attributes estaran protectec y haremos getters en algun momento xd
	std::list<b2Fixture*>::iterator it_; 
	unsigned int id_ = 1;
	double damage_ = -1,
		time_ = -1,
		hitstun_ = -1;
	Vector2D knockBack_; //Assuming looking to the right
	bool guardBreaker_ = false;
	bool destroy_ = false;//if its true it means that it has to be destroyed
	bool multiHit_ = false;	//si la hitbox es multiHit, solo se destruye cuando pasa su tiempo
	bool proyectile_ = false; //si la hitbox es un proyectil, para no eliminarla cuando aterrizas o te interrumpen un ataque
	int damage_frec = 0;	//frames that the hitbox is not doing damage 
	int aux_frec = 0;		//if aux_fec == 0, a multiHit hitbox can do damage
};

