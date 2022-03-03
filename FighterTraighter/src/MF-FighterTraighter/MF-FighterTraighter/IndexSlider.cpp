#include "IndexSlider.h"
#include "Entity.h"
IndexSlider::~IndexSlider()
{
}
void IndexSlider::init()
{
	transform_ = entity_->getComponent<Transform>(ecs::Transform);
	slider_ = sliderEnt_->getComponent<Slider>(ecs::UIElement);
	transform_slider = sliderEnt_->getComponent<Transform>(ecs::Transform);
}

void IndexSlider::update()
{
	double sliderValue = slider_->getValue();
	double sliderWidth = transform_slider->getWidth() * transform_slider->getWMult();
	double sliderRange = slider_->getMaxValue() - slider_->getMinValue();
	transform_->setPosition({ transform_slider->getPosition().getX() + ((sliderValue - slider_->getMinValue()) / sliderRange) * sliderWidth - transform_->getWidth() * transform_->getWMult() / 2, 
		transform_slider->getPosition().getY() - transform_->getHeight() * transform_->getHMult() / 2 });
}

