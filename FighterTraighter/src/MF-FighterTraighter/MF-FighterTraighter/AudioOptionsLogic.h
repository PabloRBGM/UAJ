#pragma once
#include "Component.h"
#include "NavigationController.h"
class AudioOptionsLogic :
	public Component
{
public:
	AudioOptionsLogic(NavigationController* audioNav,
		std::tuple<Entity*, Entity*, Entity*, Entity*> musicSlider,
		std::tuple<Entity*, Entity*, Entity*, Entity*> soundSlider,
		std::tuple<Entity*, Entity*> silenceButton) :
		Component(ecs::AudioOptionsLogic),
		audioNav(audioNav),
		musicSlider(musicSlider),
		soundSlider(soundSlider),
		silenceButton(silenceButton) {}
	virtual ~AudioOptionsLogic() {}

	void init() override;
	void update() override;

	void setEnabled(bool e);
	void SetElements();
protected:
	NavigationController* audioNav;

	std::tuple<Entity*, Entity*, Entity*, Entity*> musicSlider;
	std::tuple<Entity*, Entity*, Entity*, Entity*> soundSlider;
	std::tuple<Entity*, Entity*> silenceButton;

	bool enabled = true;
};

