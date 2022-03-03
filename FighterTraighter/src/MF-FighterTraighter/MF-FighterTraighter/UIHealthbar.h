#pragma once
#include "Component.h"
#include "Health.h"
#include "Transform.h"
class UIHealthbar :
	public Component
{
public:
	// Health probably shouldn't be in the same entity as Healthbar
	UIHealthbar(Health* health, Texture* tex, bool flipped = false) : Component(ecs::UIHealthbar), flipped_(flipped), health_(health), texture_(tex), transform_(nullptr) {}

	void init() override;
	// Has to render by itself because it uses a different texture render
	void render() override;
protected:
	bool flipped_;
	Health* health_;
	Texture* texture_;
	Transform* transform_;
};

