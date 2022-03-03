#include "Slider.h"
#include "Entity.h"

Slider::Slider(double minValue, double maxValue, int steps, CallbackOnValueChanged* valueChanged, HID* owner)
	: UIElement(owner), transform_(nullptr), valueChanged_(valueChanged), minValue_(minValue), maxValue_(maxValue), steps_(steps)
{
}

void Slider::init()
{
	value_ = maxValue_;
	transform_ = entity_->getComponent<Transform>(ecs::Transform);
}

void Slider::handleInput()
{
	if (Buttonstate_ == Selected) {
		if (!owner_ && app_->getInputManager()->pressedRight() || owner_ && owner_->ButtonPressed(HID::LeftPad_Right)) {
			if (steps_ > 1) {
				setValue(value_ + (maxValue_ - minValue_) / steps_);
			}
			else {
				setValue(value_ + 1);
			}
		}
		else if (!owner_ && app_->getInputManager()->pressedLeft() || owner_ && owner_->ButtonPressed(HID::LeftPad_Left)) {
			if (steps_ > 1) {
				setValue(value_ - (maxValue_ - minValue_) / steps_);
			}
			else {
				setValue(value_ - 1);
			}
		}
	}
}

void Slider::update()
{

}

void Slider::render()
{
	// should render itself, or have children which render themselves (transform and children?)
}

void Slider::setValue(double newValue)
{
	double oldValue = value_;
	if (steps_ >= 1) { // if steps < 1, continuous
		double distanceBetweenSteps = (maxValue_ - minValue_) / steps_;

		int j = ceil((-distanceBetweenSteps / 2 + newValue - minValue_) / distanceBetweenSteps);
		newValue = minValue_ + distanceBetweenSteps * j;
	}
	value_ = newValue;

	if (value_ < minValue_)
		value_ = minValue_;
	else if (value_ > maxValue_)
		value_ = maxValue_;

	if (valueChanged_ && oldValue != value_) valueChanged_(app_, value_);
}

Slider::~Slider()
{
}
