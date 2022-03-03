#pragma once
#include "Component.h"
#include "RenderImage.h"
#include "UIElement.h"
#include "TextComponent.h"

using SetIndexOnClick = void(App* app, int index, int control,int player);

class ButtonControl : public UIElement {

public:
	//constructor
	ButtonControl(SetIndexOnClick* startClickCallback = nullptr, int index = 0, int control = 0, int player=0,TextComponent* text = nullptr) : UIElement(), clickCallback_(startClickCallback), index(index), control(control), player(player),text_(text) {};

	virtual void Press()
	{
		Buttonstate_ = Pressed;
		entity_->getComponent<RenderImage>(ecs::RenderImage)->setFrame(2, 0);
	};
	virtual void Select()
	{
		if (Buttonstate_ != Selected) {
			Buttonstate_ = Selected;
			entity_->getComponent<RenderImage>(ecs::RenderImage)->setFrame(1, 0);
		}
	};
	virtual void Disable()
	{
		Buttonstate_ = Disabled;
	};
	virtual void Deselect()
	{
		Buttonstate_ = Normal;
		entity_->getComponent<RenderImage>(ecs::RenderImage)->setFrame(0, 0);
	};

	//destructor
	virtual ~ButtonControl() {};

	//callbacks
	inline void setClickCallback(SetIndexOnClick* callback) { clickCallback_ = callback; }
	//methods overrided of Component
	void init() override;
	//handle the input of the mouse by the moment
	void handleInput() override;
	void render() override;
	int getIndex()
	{
		return index;
	}

private:
	SetIndexOnClick* clickCallback_ = nullptr;
	//SetIndexOnClick* stopClickCallback_ = nullptr;
	int index;
	int control;
	int player;

	enum state
	{
		ini,
		pressA,
		pressEnter,
		AUP,
		ENTERUP,
		leeInput,
	};
	state b;
	string texto;
	TextComponent* text_;

};
