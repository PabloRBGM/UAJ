#include "AudioOptionsLogic.h"
#include "Entity.h"
#include "RenderImage.h"
#include "TextComponent.h"
#include "Slider.h"

void AudioOptionsLogic::init()
{	
	WindowManager* mngr = app_->getWindowManager();
	AudioManager* audioMng =app_->getAudioMngr();
	std::get<0>(musicSlider)->getComponent<Slider>(ecs::UIElement)->setValue(audioMng ->getMusicVolume());
	//Solucion 1 Poner volumen a 0
	//audioMng->setSFXVolume(0);
	std::get<0>(soundSlider)->getComponent<Slider>(ecs::UIElement)->setValue(audioMng->getSFXVolume());
	//Solucion 2 poner un valor inicial del slider sin que llame al callback
	//SFXSlider_->setinValue(audioMng->getSFXVolume());
	SetElements();
}

void AudioOptionsLogic::update()
{
	if (enabled) SetElements();
}

void AudioOptionsLogic::setEnabled(bool e)
{
	enabled = e;
	if (!enabled) {
		audioNav->setEnabled(false);
		std::get<0>(musicSlider)->getComponent<RenderImage>(ecs::RenderImage)->setRendered(false);
		std::get<1>(musicSlider)->getComponent<RenderImage>(ecs::RenderImage)->setRendered(false);
		std::get<2>(musicSlider)->getComponent<TextComponent>(ecs::TextComponent)->setText("");
		std::get<3>(musicSlider)->getComponent<TextComponent>(ecs::TextComponent)->setText("");
		std::get<0>(soundSlider)->getComponent<RenderImage>(ecs::RenderImage)->setRendered(false);
		std::get<1>(soundSlider)->getComponent<RenderImage>(ecs::RenderImage)->setRendered(false);
		std::get<2>(soundSlider)->getComponent<TextComponent>(ecs::TextComponent)->setText("");
		std::get<3>(soundSlider)->getComponent<TextComponent>(ecs::TextComponent)->setText("");
		std::get<0>(silenceButton)->getComponent<RenderImage>(ecs::RenderImage)->setRendered(false);
		std::get<1>(silenceButton)->getComponent<TextComponent>(ecs::TextComponent)->setText("");

	}
	else {
		audioNav->setEnabled(true);
		audioNav->ChangeSelectedItem(0, 0);
		std::get<0>(musicSlider)->getComponent<RenderImage>(ecs::RenderImage)->setRendered(true);
		std::get<1>(musicSlider)->getComponent<RenderImage>(ecs::RenderImage)->setRendered(true);
		std::get<2>(musicSlider)->getComponent<TextComponent>(ecs::TextComponent)->setText("Music volume");
		std::get<3>(musicSlider)->getComponent<TextComponent>(ecs::TextComponent)->setText("");
		std::get<0>(soundSlider)->getComponent<RenderImage>(ecs::RenderImage)->setRendered(true);
		std::get<1>(soundSlider)->getComponent<RenderImage>(ecs::RenderImage)->setRendered(true);
		std::get<2>(soundSlider)->getComponent<TextComponent>(ecs::TextComponent)->setText("Sound volume");
		std::get<3>(soundSlider)->getComponent<TextComponent>(ecs::TextComponent)->setText("");
		std::get<0>(silenceButton)->getComponent<RenderImage>(ecs::RenderImage)->setRendered(true);
		std::get<1>(silenceButton)->getComponent<TextComponent>(ecs::TextComponent)->setText("Mute audio");
	}
}

void AudioOptionsLogic::SetElements()
{	
	WindowManager* mngr = app_->getWindowManager();
	
	if (app_->getAudioMngr()->pausedMusic()) {//just change the value
		std::get<3>(soundSlider)->getComponent<TextComponent>(ecs::TextComponent)->setText(std::to_string((int)std::get<0>(soundSlider)->getComponent<Slider>(ecs::UIElement)->getValue()));
	}
	else//do a sound if not silenced and change the value
		std::get<3>(soundSlider)->getComponent<TextComponent>(ecs::TextComponent)->setText(std::to_string(app_->getAudioMngr()->getSFXVolume()));
	std::get<3>(musicSlider)->getComponent<TextComponent>(ecs::TextComponent)->setText(std::to_string((int)std::get<0>(musicSlider)->getComponent<Slider>(ecs::UIElement)->getValue()));

}
