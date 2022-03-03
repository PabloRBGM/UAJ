#include "PlayerParticleSystem.h"
#include "Entity.h"

void PlayerParticleSystem::init()
{
	phys_ = entity_->getComponent<PhysicsTransform>(ecs::Transform);
	particles_ = std::vector<ParticleData>(maxParticles_);

	for (int i = 0; i < particles_.size(); ++i) {
		particles_[i].time_ = -1;
	}
}
