#pragma once
#include "Component.h"
#include "Vector2D.h"
#include "PhysicsTransform.h"

class Entity;

class PlayerParticleSystem : public Component {
public:
	enum DeletionMethod {
		None,
		OnHit,
		OnAttack,
		OnDamaged
	};

	struct ParticleData {
		Texture* tex_;
		Vector2D pos_;
		Vector2D size_;
		int time_;
		DeletionMethod method_;

		int frame_;
		int maxFrames_;
		int prevIncr_;
		int incr_;
		bool loops_;
	};

	PlayerParticleSystem(int max) : Component(ecs::PlayerParticleSystem), maxParticles_(max), currParticles_(0), phys_(nullptr) {};
	void addNewParticle(Texture* tex, Vector2D pos, Vector2D size, int time, DeletionMethod deletion) {
		if (currParticles_ < maxParticles_) {
			int index = findAvailableIndex(); //Find empty spot (timer = -1)
			particles_[index].tex_ = tex;
			particles_[index].pos_ = pos;
			particles_[index].size_ = size;
			particles_[index].time_ = time;
			particles_[index].method_ = deletion;
			particles_[index].frame_ = 0;
			particles_[index].maxFrames_ = 1;
			particles_[index].prevIncr_ = 0;
			particles_[index].incr_ = 0;
			particles_[index].loops_ = false;
			currParticles_++;
		}
	}

	void addNewParticle(Texture* tex, Vector2D pos, Vector2D size, int time, DeletionMethod deletion, int maxFrames, int incrSpeed, bool lups) {
		if (currParticles_ < maxParticles_) {
			int index = findAvailableIndex(); //Find empty spot (timer = -1)
			particles_[index].tex_ = tex;
			particles_[index].pos_ = pos;
			particles_[index].size_ = size;
			particles_[index].time_ = time;
			particles_[index].method_ = deletion;
			particles_[index].frame_ = 0;
			particles_[index].maxFrames_ = maxFrames;
			particles_[index].prevIncr_ = 0;
			particles_[index].incr_ = incrSpeed;
			particles_[index].loops_ = lups;
			currParticles_++;
		}
	}
	virtual void init() override;

	virtual void update() override {
		for (int i = 0; i < particles_.size(); ++i) {
			//Lower the timer
			if (particles_[i].time_ > 0) {
				particles_[i].time_--;
			}
			if (particles_[i].time_ == 0) {
				particles_[i].time_ = -1;
				currParticles_--;		//Timer reached -1 -> Free spot
			}

			if (particles_[i].time_ != -1) {	//prevent unnecesary updating
				if (particles_[i].prevIncr_ >= particles_[i].incr_) {
					particles_[i].prevIncr_ = 0;
					particles_[i].frame_++;
					if (!particles_[i].loops_) {
						if (particles_[i].frame_ >= particles_[i].maxFrames_) particles_[i].frame_ = particles_[i].maxFrames_ - 1;
					}
					else particles_[i].frame_ = particles_[i].frame_ % particles_[i].maxFrames_;
				}
				else
				{
					particles_[i].prevIncr_++;
				}
			}
		}
	}

	virtual void render() {
		for (int i = 0; i < particles_.size(); ++i) {
			if (particles_[i].time_ != -1) {	//This allows particles with time = -2 to not have a time limit, and to be instead released by another method (like onHit)
				SDL_Rect dest = SDL_Rect();
				dest.x = phys_->getPosition().getX() + particles_[i].pos_.getX();
				dest.y = phys_->getPosition().getY() + particles_[i].pos_.getY();
				dest.w = particles_[i].size_.getX();
				dest.h = particles_[i].size_.getY();
				particles_[i].tex_->render(dest, 0, particles_[i].frame_, 0, phys_->getOrientation() == 1 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
			}
		}
	}

	int findAvailableIndex() {
		int i = 0;
		int found = -1;
		while (i < particles_.size() && found < 0) {
			if (particles_[i].time_ == -1) {
				found = i;
			}
			++i;
		}

		return found;
	}

	void removeDeletionMethodParticles(DeletionMethod meth) {
		for (int i = 0; i < particles_.size(); ++i) {
			if (particles_[i].method_ == meth) {
				particles_[i].time_ = -1;
				currParticles_--;
			}
		}
	}

	~PlayerParticleSystem() {};
private:
	int maxParticles_;
	int currParticles_;

	std::vector<ParticleData> particles_;

	PhysicsTransform* phys_;
};