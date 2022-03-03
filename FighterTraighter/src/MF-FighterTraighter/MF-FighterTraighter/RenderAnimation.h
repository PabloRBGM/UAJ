#pragma once
#include "Component.h"
#include "Transform.h"
class RenderAnimation: public Component
{
public:
	// FrameDuration is the amount of ingame frames one frame of this animation lasts
	RenderAnimation(Texture* tex, int frameDuration = 1) : Component(ecs::RenderAnimation), tex_(tex), frameDuration_(frameDuration) {}

	void init() override;
	void update() override;
	void render() override;
protected:
	Transform* tr_;
	Texture* tex_;
	int frameDuration_;
	int framesSinceLastFrame_ = 0;
	int curFrame_ = 0;
};

