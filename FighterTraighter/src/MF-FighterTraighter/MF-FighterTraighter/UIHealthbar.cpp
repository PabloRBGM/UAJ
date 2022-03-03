#include "UIHealthbar.h"
#include "Transform.h"
#include "Entity.h"

void UIHealthbar::init()
{
	transform_ = entity_->getComponent<Transform>(ecs::Transform);
}

void UIHealthbar::render()
{
	Vector2D pos(transform_->getPosition());
	Vector2D size(transform_->getWidth() * transform_->getWMult(), transform_->getHeight() * transform_->getHMult());
	SDL_Rect dest;
	if (!flipped_)
		dest.x = pos.getX();
	else
		dest.x = pos.getX() + size.getX() * (health_->getMaxHealth() - health_->getLife()) / health_->getMaxHealth();
	dest.y = pos.getY();
	dest.w = size.getX() * health_->getLife() / health_->getMaxHealth();
	dest.h = size.getY();

	texture_->render({ 0, 0, texture_->getWidth() * health_->getLife() / health_->getMaxHealth(), texture_->getHeight() },
		dest, 0, flipped_ ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}
