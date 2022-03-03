#include "RenderImage.h"

RenderImage::~RenderImage()
{
	transform_ = nullptr;
	texture_ = nullptr;
}

//set the transform to the entity transform
void RenderImage::init()
{
	transform_ = entity_->getComponent<Transform>(ecs::Transform);
}

//render the image
void RenderImage::render()
{
	if (rendered) {
		Vector2D pos(transform_->getPosition());
		SDL_Rect dest = SDL_Rect();
		dest.x = pos.getX();
		dest.y = pos.getY();
		dest.w = transform_->getWidth() * transform_->getWMult();
		dest.h = transform_->getHeight() * transform_->getHMult();
		//dest.x = pos.getX() - dest.w / 2;
		//dest.y = pos.getY() - dest.h / 2;
		if (color_.r != 255 || color_.g != 255 || color_.b != 255 || color_.a != 255) {
			texture_->setColor(color_);
		}

		//Experimental
		if (transform_->getOrientation() == 1)	texture_->render(dest, curY, curX, transform_->getRotation());
		else texture_->render(dest, curY, curX, transform_->getRotation(), SDL_FLIP_HORIZONTAL);

		if (color_.r != 255 || color_.g != 255 || color_.b != 255 || color_.a != 255) {
			texture_->setColor({ 255, 255, 255, 255 });
		}
	}
}
