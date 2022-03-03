#pragma once
#include "Component.h"
#include "NavigationController.h"
class GraphicsOptionsLogic;
class AudioOptionsLogic;

class OptionsLogic :
	public Component
{
public:
	OptionsLogic(NavigationController* mainNav,
		UIElement* graphicsButton, UIElement* audioButton, UIElement* controlsButton) : 
		Component(ecs::OptionsLogic),
		mainNav(mainNav),
		graphicsButton(graphicsButton), audioButton(audioButton), controlsButton(controlsButton) {}

	void init() override;
	void handleInput() override;

	virtual ~OptionsLogic() {}
protected:
	NavigationController* mainNav;

	UIElement* graphicsButton;
	UIElement* audioButton;
	UIElement* controlsButton;

	GraphicsOptionsLogic* grLogic = nullptr;
	AudioOptionsLogic* auLogic = nullptr;

	bool mainNavEnabled = true;
};

