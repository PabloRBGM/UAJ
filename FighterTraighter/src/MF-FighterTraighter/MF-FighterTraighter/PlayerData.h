#pragma once
#include "Component.h"
#include "Vector2D.h"
#include "AnimationChain.h"
#include "PhysicsTransform.h"
//Podemos tener todos los datos en un .json o un .txt
//Tener un método para parsear y rellenar el attackData

struct AnimationData {
	int sheetLength_;
	bool loops_;
	int increaseVelocity_;
};

class PlayerData : public Component {
public:
	
	PlayerData(double width, double height, double rotation, double jump_impulse, Vector2D ini_pos, 
		double speed, double ini_health, double attack, double defense, int playerNumber);
	virtual double* getWidth() {
		return width_;
	}
	virtual void setWidth(double* width) {
		 width_=width;
	}

	virtual double* getHeight() {
		return height_;
	}
	virtual void setHeight(double* height) {
		 height_= height;
	}

	virtual double* getRotation() {
		return rotation_;
	}
	virtual void setRotation(double* rotation) {
		 rotation_=rotation;
	}

	virtual double* getJumpImpulse() {
		return jump_impulse_;
	}
	virtual void setJumpImpulse(double* jump) {
		 jump_impulse_=jump;
	}

	virtual double* getHealth() {
		return health_;
	}
	virtual void setHealth(double* health) {
		 health_= health;
	}

	virtual double getAttack() {
		return attack_;
	}
	virtual void setAttack(double attack) {
		attack_ = attack;
	}

	virtual double geDefense() {
		return defense_;
	}
	virtual void setDefense(double defense) {
		defense_ = defense;
	}

	virtual double* getSpeed() {
		return speed_;
	}
	virtual void setSpeed(double speed) {
		 *speed_ = speed;
	}

	virtual Vector2D getInitial_Position() {
		return initial_position_;
	}
	virtual void setInit_Position(Vector2D initial_position) {
		initial_position_ = initial_position;
	}

	virtual AnimationChain* getNormal_punch() {
		return normal_punch_;
	}
	virtual void setNormal_punch(AnimationChain* normal_punch) {
		normal_punch_ = normal_punch;
	}

	virtual AnimationChain* getHard_punch() {
		return hard_punch_;
	}
	virtual void setHard_punch(AnimationChain* hard_punch) {
		hard_punch_ = hard_punch;
	}

	virtual AnimationChain* getNormal_kick() {
		return normal_kick_;
	}
	virtual void setNormal_kick(AnimationChain* normal_kick) {
		normal_kick_ = normal_kick;
	}

	virtual AnimationChain* getHard_kick() {
		return hard_kick_;
	}
	virtual void setHard_kick(AnimationChain* hard_kick) {
		hard_kick_ = hard_kick;
	}
	
	virtual AnimationChain* air_normal_punch() {
		return air_normal_punch_;
	}
	virtual void setAir_normal_punch(AnimationChain* air_normal_punch) {
		air_normal_punch_ = air_normal_punch;
	}

	virtual AnimationChain* air_hard_punch() {
		return air_hard_punch_;
	}
	virtual void setAir_hard_punch(AnimationChain* air_hard_punch) {
		air_hard_punch_ = air_hard_punch;
	}

	virtual AnimationChain* air_normal_kick() {
		return air_normal_kick_;
	}
	virtual void setAir_normal_kick(AnimationChain* air_normal_kick) {
		air_normal_kick_ = air_normal_kick;
	}

	virtual AnimationChain* air_hard_kick() {
		return air_hard_kick_;
	}
	virtual void setAir_hard_kick(AnimationChain* air_hard_kick) {
		air_hard_kick_ = air_hard_kick;
	}

	virtual AnimationChain* guard_breaker() {
		return guard_breaker_;
	}
	virtual void setGuard_reaker(AnimationChain* guard_breaker) {
		guard_breaker_ = guard_breaker;
	}

	virtual int getAnimLength(int index) {
		return animLength_[index].sheetLength_;
	}
	virtual bool getAnimLoops(int index) {
		return animLength_[index].loops_;
	}
	virtual int getAnimVelocity(int index) {
		return animLength_[index].increaseVelocity_;
	}

	virtual int getPlayerNumber() {
		return playerNumber_;
	}

	virtual void setDmgSound(Mix_Chunk* sound) {
		damageSound_ = sound;
	}
	virtual Mix_Chunk* getDmgSound() {
		return damageSound_;
	}
	virtual ~PlayerData() {}
	
protected:
	//CallbackData to handle generated hitbox better
	struct CallbackData {
		Vector2D position,
			knockBack;
		int width,
			height,
			time,
			damage,
			hitstun;
		
	};
	//Player Features
	double* width_,
			*height_,
			*rotation_,
			*jump_impulse_,
			*health_,
			*speed_;
	//Player Stats
	Vector2D initial_position_;
	double 	attack_ = 1,
			defense_ = 1;

	//Attacks
	//Normal Punch 
	AnimationChain* normal_punch_=nullptr;
	//Hard Punch
	AnimationChain* hard_punch_ = nullptr;
	//Normal Kick
	AnimationChain* normal_kick_ = nullptr;
	//Hard Kick
	AnimationChain* hard_kick_ = nullptr;
	//Air Normal Punch 
	AnimationChain* air_normal_punch_ = nullptr;
	//Air Hard Punch 
	AnimationChain* air_hard_punch_ = nullptr;
	//Air Normal Kick
	AnimationChain* air_normal_kick_ = nullptr;
	//Air Hard Kick
	AnimationChain* air_hard_kick_ = nullptr;
	//Guard Breaker
	AnimationChain* guard_breaker_ = nullptr;

	//To generate hitboxes easily
	PhysicsTransform* pT = nullptr;
	b2Filter mask;

	//Animation data
	std::vector<AnimationData> animLength_;
	
	// Either player 1 or 2 (0 or 1)
	int playerNumber_;

	Mix_Chunk* damageSound_;
};