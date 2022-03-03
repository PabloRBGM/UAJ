#include "VerticalSlider.h"

VerticalSlider::VerticalSlider(double minValue, double maxValue): Slider(minValue, maxValue)
{
}

VerticalSlider::VerticalSlider(double minValue, double maxValue, int steps, CallbackOnValueChanged* valueChanged)
	: Slider(minValue, maxValue, steps, valueChanged)
{
}

VerticalSlider::~VerticalSlider()
{
}

void VerticalSlider::handleInput()
{
	if (Buttonstate_ == Selected) {
		if (!owner_ && app_->getInputManager()->pressedUp() || owner_ && owner_->ButtonPressed(HID::LeftPad_Up)) {
			if (steps_ > 1) {
				setValue(value_ + (maxValue_ - minValue_) / steps_);
			}
			else {
				setValue(value_ + 1);
			}
		}
		else if (!owner_ && app_->getInputManager()->pressedDown() || owner_ && owner_->ButtonPressed(HID::LeftPad_Down)) {
			if (steps_ > 1) {
				setValue(value_ - (maxValue_ - minValue_) / steps_);
			}
			else {
				setValue(value_ - 1);
			}
		}
	}
}
