#include "ButtonControl.h"
#include "Entity.h"
#include "Transform.h"
#include "PauseMenu.h"
#include "OptionsMenu.h"
#include "KeyboardHID.h"
#include "GamepadHID.h"

void ButtonControl::init()
{
	b = ini;
}

void ButtonControl::handleInput()
{
	InputManager* imngr = app_->getInputManager();

	switch (b)
	{
	case ButtonControl::ini:
		if (Buttonstate_ == Selected) {

			if (imngr->isKeyDown(SDL_SCANCODE_RETURN) && control == 0) {
				Press();
				text_->setText("Press Key");

				b = pressEnter;
			}
			/**/else if (imngr->isControllerButtonPressed(0, SDL_CONTROLLER_BUTTON_A) && control == 1)
			{
				Press();
				text_->setText("Press Button");
				b = pressA;
			}
		}
		break;
	case ButtonControl::pressEnter:
		if (imngr->isKeyUp(SDL_GetScancodeFromName("Return")))
		{
			imngr->readKey();

			b = ENTERUP;
		}

		break;
	case ButtonControl::pressA:
		if (imngr->isControllerButtonUp(0, SDL_CONTROLLER_BUTTON_A))
		{
			imngr->readKey();
			b = AUP;

		}
		break;
	case ButtonControl::AUP:

		texto = imngr->lastcontrol();
		if (texto != "")
		{
			b = leeInput;

		}
		break;
	case ButtonControl::ENTERUP:
		if (imngr->keyboardEvent())
		{
			texto = SDL_GetScancodeName(imngr->lastKey());
			if (texto != "")
			{
				b = leeInput;

			}

		}
		break;
	case ButtonControl::leeInput:
		texto = "";
		b = ini;
		if (clickCallback_)
		{
			clickCallback_(app_, index, control,player);
		}
		Buttonstate_ = Selected;
		entity_->getComponent<RenderImage>(ecs::RenderImage)->setFrame(1, 0);
		imngr->stopreadKey();
		break;
	}
}

void ButtonControl::render()
{
	if (b == ini)
	{
		if (control == 0)
		{
			text_->setText(SDL_GetScancodeName(dynamic_cast<KeyboardHID*>(app_->getGameManager()->getPlayerInfo(player).hid)->getkeys().at(index)));

		}
		else
		{
			text_->setText(dynamic_cast<GamepadHID*>(app_->getGameManager()->getPlayerInfo(player).hid)->getControl().at(index));
		}
	}

};
