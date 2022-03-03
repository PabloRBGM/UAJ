#pragma once
#include "Component.h"
#include "LinkedGrid.h"
#include "Vector2D.h"
#include "UIElement.h"

class NavigationController :
	public Component
{
public:
	NavigationController(size_t sizeX, size_t sizeY, HID* owner = nullptr);
	virtual ~NavigationController() {};

	void init() override;
	void handleInput() override;

	void ChangeSelectedItem(int oldX, int oldY);
	
	void SetElementInPos(UIElement* ent, size_t x, size_t y);
	UIElement* GetElementInPos(size_t x, size_t y);
	inline UIElement* GetSelectedElement() { return GetElementInPos(cursorPositionX_, cursorPositionY_); }

	void SetCursorInPos(size_t x, size_t y) { cursorPositionX_ = x; cursorPositionY_ = y; }

	int GetPosX() { return cursorPositionX_; }
	int GetPosY() { return cursorPositionY_; }

	inline void setEnabled(bool e) { enabled_ = e; GetElementInPos(cursorPositionX_, cursorPositionY_)->Deselect(); }
protected:
	LinkedGrid<UIElement*> grid_;
	int cursorPositionX_ = 0; // col
	int cursorPositionY_ = 0; // row

	int findInRowFrom(int y);
	int findInColFrom(int x);

	bool selectedFirst_ = false;
	HID* owner_ = nullptr;
	bool enabled_ = true;
};

