#include "OptionsMenu.h"
#include "InputManager.h"

#include "Entity.h"
#include "UIFactory.h"

#include "RenderImage.h"
#include "Transform.h"
#include "Slider.h"
#include "VerticalSlider.h"
#include "IndexSlider.h"
#include "OptionsLogic.h"
#include "GraphicsOptionsLogic.h"
#include "AudioOptionsLogic.h"
#include "NavigationController.h"
#include "ControlsMenu.h"
#include "App.h"
#include <cmath>
#include "RenderAnimation.h"
#include "UITransform.h"

OptionsMenu::OptionsMenu(App* app) : GameState(app)
{
#ifdef _DEBUG

	cout << "OptionsMenu" << endl;
#endif
	init();

}

OptionsMenu::~OptionsMenu()
{

}

void OptionsMenu::init()
{
	GameState::init();


#pragma region Background
	// Background
	Entity* bg = entManager_.addEntity();
	bg->addComponent<Transform>(Vector2D(), Vector2D(), app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h, 0);
	bg->addComponent<RenderAnimation>(app_->getAssetsManager()->getTexture(AssetsManager::BackgroundFight), 20);



	// Tint
	Entity* tint = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Tint),
		Vector2D(),
		Vector2D(),
		Vector2D(),
		app_->getWindowManager()->getCurResolution().h, app_->getWindowManager()->getCurResolution().h, 0);



	// Tint right
	Entity* tintRight = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Tint),
		Vector2D(),
		Vector2D(app_->getWindowManager()->getCurResolution().w, 0),
		Vector2D(app_->getWindowManager()->getCurResolution().h, 0),
		app_->getWindowManager()->getCurResolution().h, app_->getWindowManager()->getCurResolution().h, 0);
	tintRight->getComponent<UITransform>(ecs::Transform)->setOrientation(-1);
#pragma endregion



	// Position variables
	const double leftOffset = 100;
	const double buttonInitPos = -160;
	const double buttonSeparation = 115;
	const double rightButtonSeparation = 130;
	const double textOffset = 5;
	const double textSize = 85;
	const double rightTextSize = 60;
	const double buttonHeight = 100;
	const double rightButtonHeight = 72;



	// Logo
	Entity* logo = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Logo),
		Vector2D(leftOffset, 160),
		Vector2D(0, 0),
		Vector2D(0, 91 * 1.5 / 2),
		320 * 1.5, 91 * 1.5, 0);



#pragma region Main buttons
	// Graphics button
	tuple<Entity*, Entity*> graphics = UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Button), app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black),
		Vector2D(leftOffset, buttonInitPos),
		Vector2D(0, app_->getWindowManager()->getCurResolution().h / 2),
		Vector2D(0, buttonHeight / 2),
		420, buttonHeight, 0, nullptr, nullptr, "Graphics", textSize);
	std::get<1>(graphics)->getComponent<UITransform>(ecs::Transform)->setPosition(leftOffset + 35, buttonInitPos + textOffset);



	// Audio button
	tuple<Entity*, Entity*> audio = UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Button), app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black),
		Vector2D(leftOffset, buttonInitPos + buttonSeparation),
		Vector2D(0, app_->getWindowManager()->getCurResolution().h / 2),
		Vector2D(0, buttonHeight / 2),
		300, buttonHeight, 0, nullptr, nullptr, "Audio", textSize);
	std::get<1>(audio)->getComponent<UITransform>(ecs::Transform)->setPosition(leftOffset + 35, buttonInitPos + buttonSeparation + textOffset);



	// Controls button
	tuple<Entity*, Entity*> controls = UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Button), app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black),
		Vector2D(leftOffset, buttonInitPos + buttonSeparation * 2),
		Vector2D(0, app_->getWindowManager()->getCurResolution().h / 2),
		Vector2D(0, buttonHeight / 2),
		410, buttonHeight, 0, GoControlsCallback, nullptr, "Controls", textSize);
	std::get<1>(controls)->getComponent<UITransform>(ecs::Transform)->setPosition(leftOffset + 35, buttonInitPos + buttonSeparation * 2 + textOffset);



	// Back button
	tuple<Entity*, Entity*> back = UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Button), app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black),
		Vector2D(leftOffset, buttonInitPos + buttonSeparation * 3),
		Vector2D(0, app_->getWindowManager()->getCurResolution().h / 2),
		Vector2D(0, buttonHeight / 2),
		280, buttonHeight, 0, GoBackCallback, nullptr, "Back", textSize, TextComponent::TextAlignment::Left);
	std::get<1>(back)->getComponent<UITransform>(ecs::Transform)->setPosition(leftOffset + 35, buttonInitPos + buttonSeparation * 3 + textOffset);



	// Navigation
	Entity* navMain = entManager_.addEntity();
	NavigationController* ctrlMain = navMain->addComponent<NavigationController>(1, 4);
	ctrlMain->SetElementInPos(std::get<0>(graphics)->getComponent<UIElement>(ecs::UIElement), 0, 0);
	ctrlMain->SetElementInPos(std::get<0>(audio)->getComponent<UIElement>(ecs::UIElement), 0, 1);
	ctrlMain->SetElementInPos(std::get<0>(controls)->getComponent<UIElement>(ecs::UIElement), 0, 2);
	ctrlMain->SetElementInPos(std::get<0>(back)->getComponent<UIElement>(ecs::UIElement), 0, 3);
#pragma endregion



#pragma region Graphics options
	// Fullscreen button
	tuple<Entity*, Entity*> fullscreen = UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Button), app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black),
		Vector2D(-leftOffset, buttonInitPos), 
		Vector2D(app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h / 2),
		Vector2D(350, buttonHeight / 2),
		350, rightButtonHeight, 0, nullptr, fullscreenCallback, "Fullscreen", rightTextSize, TextComponent::TextAlignment::Right);
	std::get<1>(fullscreen)->getComponent<UITransform>(ecs::Transform)->setPosition(-leftOffset - 35, buttonInitPos + textOffset);



	// Resolution slider
	tuple<Entity*, Entity*, Entity*, Entity*> resolutionSlider = UIFactory::createSlider(app_, this, 0, 10, 10,
		app_->getAssetsManager()->getTexture(AssetsManager::SliderRegulator), app_->getAssetsManager()->getTexture(AssetsManager::Button), app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black),
		Vector2D(-leftOffset, buttonInitPos + rightButtonSeparation),
		Vector2D(app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h / 2),
		Vector2D(500, 5),
		500, 10, resolutionCallback, "Resolution", rightTextSize, "1920x1080@60Hz", rightTextSize);
	std::get<2>(resolutionSlider)->getComponent<TextComponent>(ecs::TextComponent)->setAlignment(TextComponent::Right);
	std::get<3>(resolutionSlider)->getComponent<UITransform>(ecs::Transform)->setPosition(-500 - leftOffset - 35, buttonInitPos + rightButtonSeparation - rightTextSize / 2);
	std::get<3>(resolutionSlider)->getComponent<TextComponent>(ecs::TextComponent)->setAlignment(TextComponent::Right);



	// Brightness slider
	tuple<Entity*, Entity*, Entity*, Entity*> brightSlider = UIFactory::createSlider(app_, this, 0.4, 1, 6,
		app_->getAssetsManager()->getTexture(AssetsManager::SliderRegulator), app_->getAssetsManager()->getTexture(AssetsManager::Button), app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black),
		Vector2D(-leftOffset, buttonInitPos + rightButtonSeparation * 2),
		Vector2D(app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h / 2),
		Vector2D(500, 5),
		500, 10, brightnessCallback, "Brightness", rightTextSize, "1.0", rightTextSize);
	std::get<2>(brightSlider)->getComponent<TextComponent>(ecs::TextComponent)->setAlignment(TextComponent::Right);
	std::get<3>(brightSlider)->getComponent<UITransform>(ecs::Transform)->setPosition(-500 - leftOffset - 35, buttonInitPos + rightButtonSeparation * 2 - rightTextSize / 2);
	std::get<3>(brightSlider)->getComponent<TextComponent>(ecs::TextComponent)->setAlignment(TextComponent::Right);



	// Navigation
	Entity* navGraphics = entManager_.addEntity();
	NavigationController* ctrlGraphics = navGraphics->addComponent<NavigationController>(1, 3);
	ctrlGraphics->SetElementInPos(std::get<0>(fullscreen)->getComponent<UIElement>(ecs::UIElement), 0, 0);
	ctrlGraphics->SetElementInPos(std::get<0>(resolutionSlider)->getComponent<UIElement>(ecs::UIElement), 0, 1);
	ctrlGraphics->SetElementInPos(std::get<0>(brightSlider)->getComponent<UIElement>(ecs::UIElement), 0, 2);
#pragma endregion



#pragma region Audio options
	// Music slider
	tuple<Entity*, Entity*, Entity*, Entity*> musicSlider = UIFactory::createSlider(app_, this, 0, 50, 10,
		app_->getAssetsManager()->getTexture(AssetsManager::SliderRegulator), app_->getAssetsManager()->getTexture(AssetsManager::Button), app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black),
		Vector2D(-leftOffset, buttonInitPos),
		Vector2D(app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h / 2),
		Vector2D(500, 5),
		500, 10, SetVolume, "Music volume", rightTextSize, "50", rightTextSize);
	std::get<2>(musicSlider)->getComponent<TextComponent>(ecs::TextComponent)->setAlignment(TextComponent::Right);
	std::get<3>(musicSlider)->getComponent<UITransform>(ecs::Transform)->setPosition(-500 - leftOffset - 35, buttonInitPos - rightTextSize / 2);
	std::get<3>(musicSlider)->getComponent<TextComponent>(ecs::TextComponent)->setAlignment(TextComponent::Right);



	// Sound slider
	tuple<Entity*, Entity*, Entity*, Entity*> soundSlider = UIFactory::createSlider(app_, this, 0, 50, 10,
		app_->getAssetsManager()->getTexture(AssetsManager::SliderRegulator), app_->getAssetsManager()->getTexture(AssetsManager::Button), app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black),
		Vector2D(-leftOffset, buttonInitPos + rightButtonSeparation),
		Vector2D(app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h / 2),
		Vector2D(500, 5),
		500, 10, SetSfxVolume, "Sound volume", rightTextSize, "50", rightTextSize);
	std::get<2>(soundSlider)->getComponent<TextComponent>(ecs::TextComponent)->setAlignment(TextComponent::Right);
	std::get<3>(soundSlider)->getComponent<UITransform>(ecs::Transform)->setPosition(-500 - leftOffset - 35, buttonInitPos + rightButtonSeparation - rightTextSize / 2);
	std::get<3>(soundSlider)->getComponent<TextComponent>(ecs::TextComponent)->setAlignment(TextComponent::Right);



	// Silence button
	tuple<Entity*, Entity*> silenceVolume = UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Button), app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black),
		Vector2D(-leftOffset, buttonInitPos + rightButtonSeparation * 2),
		Vector2D(app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h / 2),
		Vector2D(370, rightButtonHeight / 2),
		370, rightButtonHeight, 0, nullptr, silence, "Mute audio", rightTextSize, TextComponent::TextAlignment::Right);
	std::get<1>(silenceVolume)->getComponent<UITransform>(ecs::Transform)->setPosition(-leftOffset - 35, buttonInitPos + textOffset + rightButtonSeparation * 2);



	//// Navigation
	Entity* navAudio = entManager_.addEntity();
	NavigationController* ctrlAudio = navAudio->addComponent<NavigationController>(1, 3);
	ctrlAudio->SetElementInPos(std::get<0>(musicSlider)->getComponent<UIElement>(ecs::UIElement), 0, 0);
	ctrlAudio->SetElementInPos(std::get<0>(soundSlider)->getComponent<UIElement>(ecs::UIElement), 0, 1);
	ctrlAudio->SetElementInPos(std::get<0>(silenceVolume)->getComponent<UIElement>(ecs::UIElement), 0, 2);
#pragma endregion



	// Logic
	Entity* logic = entManager_.addEntity();
	logic->addComponent<GraphicsOptionsLogic>(ctrlGraphics, fullscreen, resolutionSlider, brightSlider);
	logic->addComponent<AudioOptionsLogic>(ctrlAudio, musicSlider, soundSlider, silenceVolume);
	logic->addComponent<OptionsLogic>(navMain->getComponent<NavigationController>(ecs::NavigationController),
		std::get<0>(graphics)->getComponent<UIElement>(ecs::UIElement),
		std::get<0>(audio)->getComponent<UIElement>(ecs::UIElement),
		std::get<0>(controls)->getComponent<UIElement>(ecs::UIElement));
}

void OptionsMenu::GoBackCallback(App* app) {
	app->getStateMachine()->popState();
}
void OptionsMenu::GoControlsCallback(App* app) {
	app->getStateMachine()->pushState(new ControlsMenu(app));
}

void OptionsMenu::brightnessCallback(App* app, double value)
{
	app->getWindowManager()->setBrightness(value);
	// also save to a config file
}



void OptionsMenu::SetVolume(App* app, double value)
{
	app->getAudioMngr()->setMusicVolume((int)value);

}


void OptionsMenu::SetSfxVolume(App* app, double value)
{
	app->getAudioMngr()->setSFXVolume((int)value);
}

void OptionsMenu::silence(App* app)
{
	AudioManager* audioMng = app->getAudioMngr();
	if (!audioMng->pausedMusic())
		audioMng->silenceMusic();
	else audioMng->resumeMusic();
}



//fullscreen
void OptionsMenu::fullscreenCallback(App* app) {
	app->getWindowManager()->setFullscreen(!app->getWindowManager()->getFullscreen());
	// also save to a config file
}

double OptionsMenu::curResolution_ = 0;
void OptionsMenu::resolutionCallback(App* app, double value)
{
	OptionsMenu::curResolution_ = value;
	// also save to a config file
}

void OptionsMenu::applySettings(App* app)
{
	app->getWindowManager()->setResolution(lround(OptionsMenu::curResolution_));
}
