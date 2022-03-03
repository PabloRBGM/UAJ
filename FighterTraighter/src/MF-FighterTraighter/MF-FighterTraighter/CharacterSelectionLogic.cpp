#include "CharacterSelectionLogic.h"

CharacterSelectionLogic::~CharacterSelectionLogic()
{

}

void CharacterSelectionLogic::init()
{
	desc_->setText("");
	curNavX = nav_->GetPosX();
	curNavY = nav_->GetPosY();
	aisha_->getComponent<RenderImage>(ecs::RenderImage)->setRendered(false);
	flor_->getComponent<RenderImage>(ecs::RenderImage)->setRendered(false);
	mkwhoop_->getComponent<RenderImage>(ecs::RenderImage)->setRendered(false);
	mock_->getComponent<RenderImage>(ecs::RenderImage)->setRendered(false);
	random_->getComponent<RenderImage>(ecs::RenderImage)->setRendered(false);
	SetElements();
	chose = false;
}

void CharacterSelectionLogic::update()
{
	// If nothing changed, don't do anything
	if (curNavX == nav_->GetPosX() && curNavY == nav_->GetPosY()) return;
	SetElements();

}

void CharacterSelectionLogic::handleInput()
{
	if ((app_->getGameManager()->getPlayerInfo(playerNumber_).hid->ButtonPressed(HID::RightPad_Down) ||
		app_->getGameManager()->getPlayerInfo(playerNumber_).hid->ButtonPressed(HID::Select))) {
		if (!chose) {
#ifdef _DEBUG
			cout << "you chose character  " << playerNumber_ << endl;

#endif // _DEBUG

			UIElement* e = nav_->GetElementInPos(nav_->GetPosX(), nav_->GetPosY());
			if (e == aisha_->getComponent<UIElement>(ecs::UIElement)) {

				// Not implemented
				//app_->getGameManager()->setCharacter(app_->getGameManager()->Aisha, n);
			}
			else if (e == flor_->getComponent<UIElement>(ecs::UIElement)) {

				app_->getGameManager()->setCharacter(app_->getGameManager()->F10R, playerNumber_);
			}
			else if (e == mkwhoop_->getComponent<UIElement>(ecs::UIElement)) {

				app_->getGameManager()->setCharacter(app_->getGameManager()->MKWh00p, playerNumber_);
			}
			else if (e == mock_->getComponent<UIElement>(ecs::UIElement)) {
				app_->getGameManager()->setCharacter(app_->getGameManager()->Mockingbird, playerNumber_);
			}
			else if (e == random_->getComponent<UIElement>(ecs::UIElement)) {

				int n = app_->getRandGen()->nextInt(1, 3); // use this to enable/disable characters

				switch (n) {
				case 0:
					n = 1;
					//another random cause it's Aisha case 
					break;
				case 1:
					app_->getGameManager()->setCharacter(app_->getGameManager()->F10R, playerNumber_);
					break;
				case 2:
					app_->getGameManager()->setCharacter(app_->getGameManager()->MKWh00p, playerNumber_);
					break;
				case 3:
					app_->getGameManager()->setCharacter(app_->getGameManager()->Mockingbird, playerNumber_);
					break;
				}
			}

			chose = true;
			curNavX = nav_->GetPosX();
			curNavY = nav_->GetPosY();
		}
		else {
#ifdef _DEBUG
			cout << "you quit your character" << endl;
#endif // _DEBUG
			chose = false;
		}
	}
}


void CharacterSelectionLogic::SetElements()
{
	UIElement* e = nav_->GetElementInPos(nav_->GetPosX(), nav_->GetPosY());
	if (!chose) {

		aisha_->getComponent<RenderImage>(ecs::RenderImage)->setRendered(false);
		flor_->getComponent<RenderImage>(ecs::RenderImage)->setRendered(false);
		mkwhoop_->getComponent<RenderImage>(ecs::RenderImage)->setRendered(false);
		mock_->getComponent<RenderImage>(ecs::RenderImage)->setRendered(false);
		random_->getComponent<RenderImage>(ecs::RenderImage)->setRendered(false);

		if (e == aisha_->getComponent<UIElement>(ecs::UIElement)) {
			desc_->setText(aisha_desc_);
			image_->setTexture(aisha_texture);
			aisha_->getComponent<RenderImage>(ecs::RenderImage)->setRendered(true);
		}
		else if (e == flor_->getComponent<UIElement>(ecs::UIElement)) {
			desc_->setText(flor_desc_);
			image_->setTexture(flor_texture);
			flor_->getComponent<RenderImage>(ecs::RenderImage)->setRendered(true);
		}
		else if (e == mkwhoop_->getComponent<UIElement>(ecs::UIElement)) {
			desc_->setText(mkwhoop_desc_);
			image_->setTexture(mkwhoop_texture);
			mkwhoop_->getComponent<RenderImage>(ecs::RenderImage)->setRendered(true);
		}
		else if (e == mock_->getComponent<UIElement>(ecs::UIElement)) {
			desc_->setText(mock_desc_);
			image_->setTexture(mock_texture);
			mock_->getComponent<RenderImage>(ecs::RenderImage)->setRendered(true);
		}
		else if (e == random_->getComponent<UIElement>(ecs::UIElement)) {
			//generate a random (generated in handleinput)
			desc_->setText(" ");
			image_->setTexture(random_texture); //add random texture
			random_->getComponent<RenderImage>(ecs::RenderImage)->setRendered(true);
		}

		curNavX = nav_->GetPosX();
		curNavY = nav_->GetPosY();
	}
}
