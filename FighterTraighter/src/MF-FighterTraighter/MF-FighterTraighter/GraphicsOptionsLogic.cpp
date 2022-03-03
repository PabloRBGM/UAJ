#include "GraphicsOptionsLogic.h"
#include "Entity.h"
#include "TextComponent.h"
#include "Slider.h"

void GraphicsOptionsLogic::init()
{
	WindowManager* mngr = app_->getWindowManager();
	Slider* resSlider = std::get<0>(resolutionsSlider)->getComponent<Slider>(ecs::UIElement);
	resSlider->setValue(mngr->getCurResolutionIndex());
	resSlider->setMinValue(0);
	resSlider->setMaxValue(mngr->getAvailableResolutions() - 2);
	resSlider->setSteps(mngr->getAvailableResolutions() - 2);
	resSlider->setValue(mngr->getCurBrightness());
	SetElements();
}

void GraphicsOptionsLogic::update()
{
	if (enabled) {
		SetElements();
	}
}

void GraphicsOptionsLogic::setEnabled(bool e)
{
	enabled = e;
	if (!enabled) {
		graphicsNav->setEnabled(false);
		std::get<0>(fullscreenButton)->getComponent<RenderImage>(ecs::RenderImage)->setRendered(false);
		std::get<1>(fullscreenButton)->getComponent<TextComponent>(ecs::TextComponent)->setText("");
		std::get<0>(resolutionsSlider)->getComponent<RenderImage>(ecs::RenderImage)->setRendered(false);
		std::get<1>(resolutionsSlider)->getComponent<RenderImage>(ecs::RenderImage)->setRendered(false);
		std::get<2>(resolutionsSlider)->getComponent<TextComponent>(ecs::TextComponent)->setText("");
		std::get<3>(resolutionsSlider)->getComponent<TextComponent>(ecs::TextComponent)->setText("");
		std::get<0>(brightnessSlider)->getComponent<RenderImage>(ecs::RenderImage)->setRendered(false);
		std::get<1>(brightnessSlider)->getComponent<RenderImage>(ecs::RenderImage)->setRendered(false);
		std::get<2>(brightnessSlider)->getComponent<TextComponent>(ecs::TextComponent)->setText("");
		std::get<3>(brightnessSlider)->getComponent<TextComponent>(ecs::TextComponent)->setText("");
	}
	else {
		graphicsNav->setEnabled(true);
		graphicsNav->ChangeSelectedItem(0, 0);
		std::get<0>(fullscreenButton)->getComponent<RenderImage>(ecs::RenderImage)->setRendered(true);
		std::get<1>(fullscreenButton)->getComponent<TextComponent>(ecs::TextComponent)->setText("Fullscreen");
		std::get<0>(resolutionsSlider)->getComponent<RenderImage>(ecs::RenderImage)->setRendered(true);
		std::get<1>(resolutionsSlider)->getComponent<RenderImage>(ecs::RenderImage)->setRendered(true);
		std::get<2>(resolutionsSlider)->getComponent<TextComponent>(ecs::TextComponent)->setText("Resolution");
		std::get<3>(resolutionsSlider)->getComponent<TextComponent>(ecs::TextComponent)->setText("");
		std::get<0>(brightnessSlider)->getComponent<RenderImage>(ecs::RenderImage)->setRendered(true);
		std::get<1>(brightnessSlider)->getComponent<RenderImage>(ecs::RenderImage)->setRendered(true);
		std::get<2>(brightnessSlider)->getComponent<TextComponent>(ecs::TextComponent)->setText("Brightness");
		std::get<3>(brightnessSlider)->getComponent<TextComponent>(ecs::TextComponent)->setText("");
	}
}

void GraphicsOptionsLogic::SetElements()
{
	WindowManager* mngr = app_->getWindowManager();
	Slider* resSlider = std::get<0>(resolutionsSlider)->getComponent<Slider>(ecs::UIElement);
	std::get<3>(resolutionsSlider)->getComponent<TextComponent>(ecs::TextComponent)->setText(std::to_string(mngr->getSupportedResolutions()[resSlider->getValue()].w)
		+ "x" + std::to_string(mngr->getSupportedResolutions()[resSlider->getValue()].h)
		+ "@" + std::to_string(mngr->getSupportedResolutions()[resSlider->getValue()].refresh_rate) + "Hz");

	std::get<3>(brightnessSlider)->getComponent<TextComponent>(ecs::TextComponent)->setText(std::to_string(mngr->getCurBrightness()));
}
