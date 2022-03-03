#pragma once
#include "Component.h"
#include "NavigationController.h"
class GraphicsOptionsLogic :
	public Component
{
public:
	GraphicsOptionsLogic(NavigationController* graphicsNav,
		std::tuple<Entity*, Entity*> fullscreenButton,
		std::tuple<Entity*, Entity*, Entity*, Entity*> resolutionsSlider,
		std::tuple<Entity*, Entity*, Entity*, Entity*> brightnessSlider) :
		Component(ecs::GraphicsOptionsLogic),
		graphicsNav(graphicsNav),
		fullscreenButton(fullscreenButton),
		resolutionsSlider(resolutionsSlider),
		brightnessSlider(brightnessSlider) {}
	virtual ~GraphicsOptionsLogic() {}

	void init() override;
	void update() override;

	void setEnabled(bool e);
	void SetElements();
protected:
	NavigationController* graphicsNav;

	std::tuple<Entity*, Entity*> fullscreenButton;
	std::tuple<Entity*, Entity*, Entity*, Entity*> resolutionsSlider;
	std::tuple<Entity*, Entity*, Entity*, Entity*> brightnessSlider;

	bool enabled = true;
};

