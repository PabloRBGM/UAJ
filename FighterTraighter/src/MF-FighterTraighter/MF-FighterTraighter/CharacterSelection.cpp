#include "CharacterSelection.h"

#include "Entity.h"
#include "UIFactory.h"
#include "RenderImage.h"
#include "Transform.h"
#include "Button.h"
#include "TextComponent.h"
#include "NavigationController.h"
#include "Font.h"
#include "RenderAnimation.h"
#include "UITransform.h"
#include "CharacterSelectionLogic.h"

#include "Fight.h"
#include "CharacterSelectionHandler.h"
void CharacterSelection::init()
{
	GameState::init();
	// Background
	Entity* background = entManager_.addEntity();
	background->addComponent<Transform>(Vector2D(), Vector2D(), app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h, 0);
	background->addComponent<RenderAnimation>(app_->getAssetsManager()->getTexture(AssetsManager::BackgroundFight), 20);

	// CenterPanel
	Entity* centralP = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Panel),
		Vector2D(0, -150), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, app_->getWindowManager()->getCurResolution().h / 2), Vector2D(780, 360), 1560, 720, 0);
	Entity* text = UIFactory::createText(app_, this, Vector2D(app_->getWindowManager()->getCurResolution().w / 3, 0),
		Vector2D(app_->getWindowManager()->getCurResolution().w / 2, 0), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, 0),
		app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), "Choose your character", 60, TextComponent::Left, 300, 100, 500);


	// Icons of all characters
	UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Flor_icon),
		Vector2D(-125, -125), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, app_->getWindowManager()->getCurResolution().h / 2 - 175), Vector2D(115, 115), 230, 230, 0);

	UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Ganonbot_icon),
		Vector2D(125, -125), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, app_->getWindowManager()->getCurResolution().h / 2 - 175), Vector2D(115, 115), 230, 230, 0);

	UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Aisha_icon),
		Vector2D(-125, 125), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, app_->getWindowManager()->getCurResolution().h / 2 - 175), Vector2D(115, 115), 230, 230, 0)->getComponent<RenderImage>(ecs::RenderImage)->setColor({125, 125, 125, 255});

	UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Mock_icon),
		Vector2D(125, 125), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, app_->getWindowManager()->getCurResolution().h / 2 - 175), Vector2D(115, 115), 230, 230, 0);

	UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Random_icon),
		Vector2D(), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, app_->getWindowManager()->getCurResolution().h / 2 - 175), Vector2D(115, 115), 230, 230, 0);





	// Player 1
	Entity* leftP = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Banner),
		Vector2D(50, 50),
		Vector2D(0, 0),
		Vector2D(0, 0),
		384, 720, 0);

	Entity* text_j1 = UIFactory::createText(app_, this, Vector2D(60, -30),
		Vector2D(0, app_->getWindowManager()->getCurResolution().h / 4 * 3),
		Vector2D(0, 50),
		app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), "description_ j1", 25, TextComponent::Left,
		100, 100, 25);

	Entity* florElement1 = entManager_.addEntity();
	florElement1->addComponent<UITransform>(Vector2D(-125, -125), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, app_->getWindowManager()->getCurResolution().h / 2 - 175), Vector2D(125, 125), Vector2D(250, 250));
	florElement1->addComponent<UIElement>(app_->getGameManager()->getPlayerInfo(1).hid);
	florElement1->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::SelectionSquare));

	Entity* mockElement1 = entManager_.addEntity();
	mockElement1->addComponent<UITransform>(Vector2D(125, 125), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, app_->getWindowManager()->getCurResolution().h / 2 - 175), Vector2D(125, 125), Vector2D(250, 250));
	mockElement1->addComponent<UIElement>(app_->getGameManager()->getPlayerInfo(1).hid);
	mockElement1->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::SelectionSquare));

	Entity* MKElement1 = entManager_.addEntity();
	MKElement1->addComponent<UITransform>(Vector2D(125, -125), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, app_->getWindowManager()->getCurResolution().h / 2 - 175), Vector2D(125, 125), Vector2D(250, 250));
	MKElement1->addComponent<UIElement>(app_->getGameManager()->getPlayerInfo(1).hid);
	MKElement1->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::SelectionSquare));

	Entity* aishaElement1 = entManager_.addEntity();
	aishaElement1->addComponent<UITransform>(Vector2D(-125, 125), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, app_->getWindowManager()->getCurResolution().h / 2 - 175), Vector2D(125, 125), Vector2D(250, 250));
	aishaElement1->addComponent<UIElement>(app_->getGameManager()->getPlayerInfo(1).hid);
	aishaElement1->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::SelectionSquare));

	Entity* randElement1 = entManager_.addEntity();
	randElement1->addComponent<UITransform>(Vector2D(), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, app_->getWindowManager()->getCurResolution().h / 2 - 175), Vector2D(125, 125), Vector2D(250, 250));
	randElement1->addComponent<UIElement>(app_->getGameManager()->getPlayerInfo(1).hid);
	randElement1->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::SelectionSquare));


	Entity* nav1 = entManager_.addEntity();
	NavigationController* ctrl1 = nav1->addComponent<NavigationController>(2, 3, app_->getGameManager()->getPlayerInfo(1).hid);
	ctrl1->SetElementInPos(florElement1->getComponent<UIElement>(ecs::UIElement), 0, 0);
	ctrl1->SetElementInPos(MKElement1->getComponent<UIElement>(ecs::UIElement), 1, 0);
	ctrl1->SetElementInPos(randElement1->getComponent<UIElement>(ecs::UIElement), 0, 1);
	//ctrl1->SetElementInPos(aishaElement1->getComponent<UIElement>(ecs::UIElement), 0, 2);
	ctrl1->SetElementInPos(mockElement1->getComponent<UIElement>(ecs::UIElement), 1, 2);

	Entity* logic1 = entManager_.addEntity();
	logic1->addComponent<CharacterSelectionLogic>(1, text_j1->getComponent<TextComponent>(ecs::TextComponent), leftP->getComponent<RenderImage>(ecs::RenderImage), aisha_desc, mkwhoop_desc, flor_desc, mock_desc, nav1->getComponent<NavigationController>(ecs::NavigationController),
		aishaElement1, florElement1, MKElement1, mockElement1, randElement1,
		app_->getAssetsManager()->getTexture(AssetsManager::AishaArtwork), app_->getAssetsManager()->getTexture(AssetsManager::FlorArtwork), app_->getAssetsManager()->getTexture(AssetsManager::GanonArtwork), app_->getAssetsManager()->getTexture(AssetsManager::MockArtwork), app_->getAssetsManager()->getTexture(AssetsManager::RandomArtwork));



	// Player 2
	Entity* rightP = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Banner),
		Vector2D(-50, 50),
		Vector2D(app_->getWindowManager()->getCurResolution().w, 0),
		Vector2D(384, 0),
		384, 720, 0);
	rightP->getComponent<UITransform>(ecs::Transform)->setOrientation(-1);

	if (numPlayer_ == 2){
		Entity* text_j2 = UIFactory::createText(app_, this, Vector2D(-360, -30),
			Vector2D(app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h / 4 * 3),
			Vector2D(0, 50),
			app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), "description_ j2", 25, TextComponent::Left,
			100, 100, 25);

		Entity* florElement2 = entManager_.addEntity();
		florElement2->addComponent<UITransform>(Vector2D(-125, -125), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, app_->getWindowManager()->getCurResolution().h / 2 - 175), Vector2D(125, 125), Vector2D(250, 250));
		florElement2->addComponent<UIElement>(app_->getGameManager()->getPlayerInfo(2).hid);
		RenderImage* r = florElement2->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::SelectionSquare));
		r->setColor({ 255, 0, 0, 255 });

		Entity* mockElement2 = entManager_.addEntity();
		mockElement2->addComponent<UITransform>(Vector2D(125, 125), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, app_->getWindowManager()->getCurResolution().h / 2 - 175), Vector2D(125, 125), Vector2D(250, 250));
		mockElement2->addComponent<UIElement>(app_->getGameManager()->getPlayerInfo(2).hid);
		r = mockElement2->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::SelectionSquare));
		r->setColor({ 255, 0, 0, 255 });

		Entity* MKElement2 = entManager_.addEntity();
		MKElement2->addComponent<UITransform>(Vector2D(125, -125), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, app_->getWindowManager()->getCurResolution().h / 2 - 175), Vector2D(125, 125), Vector2D(250, 250));
		MKElement2->addComponent<UIElement>(app_->getGameManager()->getPlayerInfo(2).hid);
		r = MKElement2->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::SelectionSquare));
		r->setColor({ 255, 0, 0, 255 });

		Entity* aishaElement2 = entManager_.addEntity();
		aishaElement2->addComponent<UITransform>(Vector2D(-125, 125), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, app_->getWindowManager()->getCurResolution().h / 2 - 175), Vector2D(125, 125), Vector2D(250, 250));
		aishaElement2->addComponent<UIElement>(app_->getGameManager()->getPlayerInfo(2).hid);
		r = aishaElement2->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::SelectionSquare));
		r->setColor({ 255, 0, 0, 255 });

		Entity* randElement2 = entManager_.addEntity();
		randElement2->addComponent<UITransform>(Vector2D(), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, app_->getWindowManager()->getCurResolution().h / 2 - 175), Vector2D(125, 125), Vector2D(250, 250));
		randElement2->addComponent<UIElement>(app_->getGameManager()->getPlayerInfo(2).hid);
		r = randElement2->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::SelectionSquare));
		r->setColor({ 255, 0, 0, 255 });
		Entity* nav_ = entManager_.addEntity();

		NavigationController* ctrl2 = nav_->addComponent<NavigationController>(2, 3, app_->getGameManager()->getPlayerInfo(2).hid);
		ctrl2->SetElementInPos((florElement2)->getComponent<UIElement>(ecs::UIElement), 0, 0);
		ctrl2->SetElementInPos((MKElement2)->getComponent<UIElement>(ecs::UIElement), 1, 0);
		ctrl2->SetElementInPos((randElement2)->getComponent<UIElement>(ecs::UIElement), 0, 1);
		//ctrl2->SetElementInPos((aishaElement2)->getComponent<UIElement>(ecs::UIElement), 0, 2);
		ctrl2->SetElementInPos((mockElement2)->getComponent<UIElement>(ecs::UIElement), 1, 2);
		
		Entity* logic2 = entManager_.addEntity();
		logic2->addComponent<CharacterSelectionLogic>(2, text_j2->getComponent<TextComponent>(ecs::TextComponent), rightP->getComponent<RenderImage>(ecs::RenderImage), aisha_desc, mkwhoop_desc, flor_desc, mock_desc, nav_->getComponent<NavigationController>(ecs::NavigationController),
			aishaElement2, florElement2, MKElement2, mockElement2, randElement2,
			app_->getAssetsManager()->getTexture(AssetsManager::AishaArtwork), app_->getAssetsManager()->getTexture(AssetsManager::FlorArtwork), app_->getAssetsManager()->getTexture(AssetsManager::GanonArtwork), app_->getAssetsManager()->getTexture(AssetsManager::MockArtwork), app_->getAssetsManager()->getTexture(AssetsManager::RandomArtwork));
		Entity* ent = entManager_.addEntity();
		ent->addComponent<CharacterSelectionHandler>(logic1, logic2);
	}
	
	else {
		Entity* ent = entManager_.addEntity();
		ent->addComponent<CharacterSelectionHandler>(logic1, nullptr);
	}

}

void CharacterSelection::handleInput()
{
	if (app_->getInputManager()->pressedStart()) {
		app_->getGameManager()->pressedStart();
	}
	else
		GameState::handleInput();

}


