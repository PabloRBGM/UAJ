#include "Button.h"
#include "Entity.h"
#include "Transform.h"
#include "PauseMenu.h"
#include "OptionsMenu.h"

void Button::init()
{
}

void Button::handleInput()
{
	if (Buttonstate_ == Selected) {
		if (!owner_ && app_->getInputManager()->pressedAccept() || owner_ && (owner_->ButtonPressed(HID::RightPad_Down) || owner_->ButtonPressed(HID::Select))) {
			Press();
		}
	}
	else if (Buttonstate_ == Pressed) {
		Buttonstate_ = Selected;
		entity_->getComponent<RenderImage>(ecs::RenderImage)->setFrame(1, 0);
		if (stopClickCallback_) stopClickCallback_(app_);
	}
}

void Button::render()
{

}
