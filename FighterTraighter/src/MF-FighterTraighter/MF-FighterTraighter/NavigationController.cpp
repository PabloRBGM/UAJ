#include "NavigationController.h"
#include "Button.h"

NavigationController::NavigationController(size_t sizeX, size_t sizeY, HID* owner) : Component(ecs::NavigationController), grid_(sizeX, sizeY), cursorPositionX_(), cursorPositionY_(), owner_(owner)
{
}

void NavigationController::init()
{
}

void NavigationController::handleInput()
{
	if (enabled_) {
		InputManager* mngr = app_->getInputManager();
		int newX = cursorPositionX_, newY = cursorPositionY_;
		int temp;
		if ((!owner_ && mngr->pressedUp() ||
			owner_ && (owner_->ButtonPressed(HID::LeftPad_Up) ||
			((owner_->AxisChanged(HID::LJoyY)) && owner_->AxisInput(HID::LJoyY) < 0)))
			&& cursorPositionY_ > 0 && (temp = findInRowFrom(--newY)) != -1)
		{
			newX = temp;
		}
		else if ((!owner_ && mngr->pressedDown() ||
			owner_ && (owner_->ButtonPressed(HID::LeftPad_Down) ||
			((owner_->AxisChanged(HID::LJoyY)) && owner_->AxisInput(HID::LJoyY) > 0)))
			&& cursorPositionY_ < grid_.GetSizeY() - 1 && (temp = findInRowFrom(++newY)) != -1)
		{
			newX = temp;
		}
		else if ((!owner_ && mngr->pressedLeft() ||
			owner_ && (owner_->ButtonPressed(HID::LeftPad_Left) ||
			((owner_->AxisChanged(HID::LJoyX)) && owner_->AxisInput(HID::LJoyX) < 0)))
			&& cursorPositionX_ > 0 && (temp = findInColFrom(--newX)) != -1)
		{
			newY = temp;
		}
		else if ((!owner_ && mngr->pressedRight() ||
			owner_ && (owner_->ButtonPressed(HID::LeftPad_Right) ||
			((owner_->AxisChanged(HID::LJoyX)) && owner_->AxisInput(HID::LJoyX) > 0)))
			&& cursorPositionX_ < grid_.GetSizeX() - 1 && (temp = findInColFrom(++newX)) != -1)
		{
			newY = temp;
		}

		if (newX != cursorPositionX_ || newY != cursorPositionY_) // If the cursor moved
		{
			ChangeSelectedItem(newX, newY);
			entity_->getApp()->getAudioMngr()->playSFX(entity_->getApp()->getAssetsManager()->getSFX(AssetsManager::BOTON), false);
		}
	}
}

void NavigationController::ChangeSelectedItem(int x, int y)
{
	UIElement* ent = grid_.GetItem(cursorPositionX_, cursorPositionY_);
	ent->Deselect();
	ent = grid_.GetItem(x, y);
	ent->Select();
	cursorPositionX_ = x;
	cursorPositionY_ = y;
}

void NavigationController::SetElementInPos(UIElement* ent, size_t x, size_t y)
{
	grid_.SetItemInPos(ent, x, y);
	if (!selectedFirst_) {
		cursorPositionX_ = x;
		cursorPositionY_ = y;
		ent->Select();
		selectedFirst_ = true;
	}
}

UIElement* NavigationController::GetElementInPos(size_t x, size_t y)
{
	return grid_.GetItem(x, y);
}

int NavigationController::findInRowFrom(int y)
{
	int i = cursorPositionX_;
	while (i >= 0 && grid_.GetItem(i, y) == nullptr) {
		--i;
	}
	if (i < 0 && cursorPositionX_ + 1 < grid_.GetSizeX()) {
		i = cursorPositionX_ + 1;
		while (i < grid_.GetSizeX() && grid_.GetItem(i, y) == nullptr) {
			++i;
		}
	}
	if (i == grid_.GetSizeX()) return -1;
	return i;
}

int NavigationController::findInColFrom(int x)
{
	int i = cursorPositionY_;
	while (i >= 0 && grid_.GetItem(x, i) == nullptr) {
		--i;
	}
	if (i < 0 && x + 1 < grid_.GetSizeY()) {
		i = cursorPositionY_ + 1;
		while (i < grid_.GetSizeY() && grid_.GetItem(x, i) == nullptr) {
			++i;
		}
	}
	if (i == grid_.GetSizeY()) return -1;
	return i;
}
