#include "InventorySelection.h"
#include "UIFactory.h"
#include "Entity.h"
#include "RenderImage.h"
#include "UITransform.h"
#include "Fight.h"
#include "InventoryLogic.h"
#include "NavigationController.h"
#include "InventoryHandler.h"
#include "KeyboardHID.h"
#include "GamepadHID.h"

void InventorySelection::init()
{
	GameState::init();

	// Background
	Entity* b = entManager_.addEntity();
	b->addComponent<UITransform>(Vector2D(), Vector2D(), Vector2D(), Vector2D(app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h));
	b->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::BackgroundFight));


	// Player1 panel
	UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Celda1),
		Vector2D(0, 0), Vector2D(50, 50), Vector2D(0, 0), (app_->getWindowManager()->getCurResolution().w / 2.0) - 100.0, app_->getWindowManager()->getCurResolution().h - 100.0, 0);
	
	// A fourth of the screens width, to use it for placing UI elements
	const double fourthScreenW = app_->getWindowManager()->getCurResolution().w / 4;

	// Player's left/right slots variables
	const double lPosX = -200;
	const double rPosX = 100;
	const double lrPosY = 200;
	const double lrAnchorPivotY = 100;
	const Vector2D lrSize = Vector2D(100, 100);
	const double textOffset = -50;
	const int textFontsize = 36;
	std::string leftTxt;
	std::string rightTxt;
	resolveHelpText(leftTxt, rightTxt, 1);
	// Entity to handle the icons frames
	Entity* mark;
	// Player1 left slot, frame and help text
	Entity* left_j1 = entManager_.addEntity();
	left_j1->addComponent<UIElement>(app_->getGameManager()->getPlayerInfo(1).hid);
	left_j1->addComponent<UITransform>(
		Vector2D(fourthScreenW + lPosX, lrPosY), 
		Vector2D(fourthScreenW, lrAnchorPivotY), 
		Vector2D(fourthScreenW, lrAnchorPivotY), 
		lrSize);
	left_j1->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::EmptyHability));
	
	//help text
	UIFactory::createText(app_, this,
		Vector2D(fourthScreenW + lPosX, lrPosY + textOffset),
		Vector2D(fourthScreenW, lrAnchorPivotY),
		Vector2D(fourthScreenW, lrAnchorPivotY),
		app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), leftTxt, textFontsize, TextComponent::Center,
		100, 100, 25);

	//icon frame
	mark = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Mark1),
		Vector2D(fourthScreenW + lPosX, lrPosY),
		Vector2D(fourthScreenW, lrAnchorPivotY),
		Vector2D(fourthScreenW, lrAnchorPivotY),
		lrSize.getX(), lrSize.getY(), 0);

	// Player1 right slot, frame and help text
	Entity* right_j1 = entManager_.addEntity();
	right_j1->addComponent<UIElement>(app_->getGameManager()->getPlayerInfo(1).hid);
	right_j1->addComponent<UITransform>(
		Vector2D(fourthScreenW + rPosX, lrPosY), 
		Vector2D(fourthScreenW, lrAnchorPivotY),
		Vector2D(fourthScreenW, lrAnchorPivotY),
		lrSize);
	right_j1->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::EmptyHability));

	
	//help text
	UIFactory::createText(app_, this, 
		Vector2D(fourthScreenW + rPosX, lrPosY + textOffset),
		Vector2D(fourthScreenW, lrAnchorPivotY),
		Vector2D(fourthScreenW, lrAnchorPivotY), 
		app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), rightTxt, textFontsize, TextComponent::Center,
		100, 100, 25);
	
	//icon frame
	mark = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Mark2),
		Vector2D(fourthScreenW + rPosX, lrPosY),
		Vector2D(fourthScreenW, lrAnchorPivotY),
		Vector2D(fourthScreenW, lrAnchorPivotY),
		lrSize.getX(), lrSize.getY(), 0);

	// Button position variables
	const double buttonPosY = -190;
	const double buttonTxtPosY = -150;
	const double bAnchorX = fourthScreenW;
	const double bAnchorY = app_->getWindowManager()->getCurResolution().h;
	const Vector2D buttonPivot = Vector2D(320, 60);
	const double buttonW = 640;
	const double buttonH = 180;
	const double buttonFontSize = 80;
	const string buttonText = "Ready!";

	// Ready button
	tuple <Entity*, Entity*> boton2 = UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Button), app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black),
		Vector2D(0, buttonPosY),
		Vector2D(bAnchorX, bAnchorY),
		buttonPivot,
		buttonW, buttonH, 0, nullptr, nullptr, buttonText, buttonFontSize, TextComponent::TextAlignment::Center);
	
	std::get<1>(boton2)->getComponent<UITransform>(ecs::Transform)->setPosition(0, buttonTxtPosY);

	
	
	// In arcade, generate abilities here
	if (numPlayer_ == 1) {
		if (app_->getGameManager()->getPlayerRounds(1) < 5) {
			GameManager::AbilityID abi1 = (GameManager::AbilityID)app_->getRandGen()->nextInt(GameManager::level1_flag, GameManager::max_level_flag);
			// Creating two abilities and introducing them into the vector, only if rounds < 5
			for (int i = 0; i < 2; i++) {
				do {
					//New ability
					abi1 = (GameManager::AbilityID)app_->getRandGen()->nextInt(GameManager::level1_flag, GameManager::max_level_flag);
				} while (checkAbility(abi1));//check if it correct
				app_->getGameManager()->addHability(abi1, 1);
			}
		}
	}

	// Players abilities slots variables
	const double slotX = 128.0;
	const double slotMargin_p1 = 40.0;
	const double slotMargin_p2 = 1000.0;
	const double slotY = 72.0;
	const double firstRowFactor = 4.7;
	const double secondRowFactor = 6.7;
	const Vector2D slotSize = Vector2D(128.0, 128.0);

	// Player 1 abilities placing
	Entity* nav_j1 = entManager_.addEntity();
	NavigationController* ctrl = nav_j1->addComponent<NavigationController>(5, 3, app_->getGameManager()->getPlayerInfo(1).hid);

	for (double i = 0; i < 10; i++) {	
		Entity* habj1 = entManager_.addEntity();
		if (i < app_->getGameManager()->getPlayerInfo(1).abilities.size()) {
			if (i < 5) { 
				habj1->addComponent<UIElement>();
				habj1->addComponent<UITransform>(
					Vector2D((slotX + i * slotX) + slotMargin_p1, slotY * firstRowFactor),
					Vector2D((slotX + i * slotX) + slotMargin_p1, slotY * firstRowFactor),
					Vector2D((slotX + i * slotX) + slotMargin_p1, slotY * firstRowFactor),
					slotSize);
				habj1->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::EmptyHability));
				ctrl->SetElementInPos((habj1)->getComponent<UIElement>(ecs::UIElement), i, 0);
			}

			else {
				habj1->addComponent<UIElement>();
				habj1->addComponent<UITransform>(
					Vector2D((slotX + (i - 5) * slotX) + slotMargin_p1, slotY * secondRowFactor), 
					Vector2D((slotX + (i - 5) * slotX) + slotMargin_p1, slotY * secondRowFactor),
					Vector2D((slotX + (i - 5) * slotX) + slotMargin_p1, slotY * secondRowFactor),
					slotSize);
				habj1->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::EmptyHability));
				
				ctrl->SetElementInPos((habj1)->getComponent<UIElement>(ecs::UIElement), (i - 5), 1);
			}

			habj1->getComponent<RenderImage>(ecs::RenderImage)->setTexture(app_->getAssetsManager()
				->getTexture((AssetsManager::TextureNames)(AssetsManager::_abilityIcon_start + app_->getGameManager()->getPlayerInfo(1).abilities[i] + 1)));
		}

		else {
			if (i < 5) {
				habj1->addComponent<UIElement>();
				habj1->addComponent<UITransform>(
					Vector2D((slotX + i * slotX) + slotMargin_p1, slotY * firstRowFactor),
					Vector2D((slotX + i * slotX) + slotMargin_p1, slotY * firstRowFactor),
					Vector2D((slotX + i * slotX) + slotMargin_p1, slotY * firstRowFactor),
					slotSize);
				habj1->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::EmptyHability));
				ctrl->SetElementInPos((habj1)->getComponent<UIElement>(ecs::UIElement), i, 0);
			}

			else {
				habj1->addComponent<UIElement>();
				habj1->addComponent<UITransform>(
					Vector2D((slotX + (i - 5) * slotX) + slotMargin_p1, slotY * secondRowFactor),
					Vector2D((slotX + (i - 5) * slotX) + slotMargin_p1, slotY * secondRowFactor),
					Vector2D((slotX + (i - 5) * slotX) + slotMargin_p1, slotY * secondRowFactor),
					slotSize);
				habj1->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::EmptyHability));

				ctrl->SetElementInPos((habj1)->getComponent<UIElement>(ecs::UIElement), (i - 5), 1);
			}

		}

	}
	// Setting up the navigation
	for (int i = 0; i < 5; i++) {
		ctrl->SetElementInPos(std::get<0>(boton2)->getComponent<UIElement>(ecs::UIElement), i, 2);
	}

	// Inventary logic for player1
	Entity* logicJ1 = entManager_.addEntity();
	logicJ1->addComponent<InventoryLogic>(ctrl, 1, left_j1->getComponent<RenderImage>(ecs::RenderImage), right_j1->getComponent<RenderImage>(ecs::RenderImage));

	// If there are 2 players
	if (numPlayer_ == 2) {
		resolveHelpText(leftTxt, rightTxt, 2);
		// Player 2 panel
		UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Celda1),
			Vector2D(0, 0),
			Vector2D((double)app_->getWindowManager()->getCurResolution().w - 430, 50),
			Vector2D(430.0 + 50.0, 0),
			double(app_->getWindowManager()->getCurResolution().w / 2) - 100, double(app_->getWindowManager()->getCurResolution().h) - 100, 0);

		// Ready button
		tuple <Entity*, Entity*> boton1 = UIFactory::createButton(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Button), app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black),
			Vector2D(0, buttonPosY),
			Vector2D(bAnchorX * 3,bAnchorY),
			buttonPivot,
			buttonW, buttonH, 0, nullptr, nullptr, buttonText, buttonFontSize, TextComponent::TextAlignment::Center);
		std::get<1>(boton1)->getComponent<UITransform>(ecs::Transform)->setPosition(0, buttonTxtPosY);

		// Player 2 left slot
		Entity* left_j2 = entManager_.addEntity();
		left_j2->addComponent<UIElement>(app_->getGameManager()->getPlayerInfo(2).hid);
		left_j2->addComponent<UITransform>(
			Vector2D(3 * fourthScreenW + lPosX, lrPosY),
			Vector2D(3 * fourthScreenW, lrAnchorPivotY),
			Vector2D(3 * fourthScreenW, lrAnchorPivotY),
			lrSize);
		left_j2->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::EmptyHability));

		//help text
		UIFactory::createText(app_, this,
			Vector2D(3 * fourthScreenW + lPosX, lrPosY + textOffset),
			Vector2D(3 * fourthScreenW, lrAnchorPivotY),
			Vector2D(3 * fourthScreenW, lrAnchorPivotY),
			app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), leftTxt, textFontsize, TextComponent::Center,
			100, 100, 25);

		//icon frame
		mark = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Mark2),
			Vector2D(3 * fourthScreenW + lPosX, lrPosY),
			Vector2D(3 * fourthScreenW, lrAnchorPivotY),
			Vector2D(3 * fourthScreenW, lrAnchorPivotY),
			lrSize.getX(), lrSize.getY(), 0);

		// Player 2 right slot
		Entity* right_j2 = entManager_.addEntity();
		right_j2->addComponent<UIElement>(app_->getGameManager()->getPlayerInfo(2).hid);
		right_j2->addComponent<UITransform>(
			Vector2D(3 * fourthScreenW + rPosX, lrPosY),
			Vector2D(3 * fourthScreenW, lrAnchorPivotY),
			Vector2D(3 * fourthScreenW, lrAnchorPivotY),
			lrSize);
		right_j2->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::EmptyHability));

		//help text
		UIFactory::createText(app_, this,
			Vector2D(3 * fourthScreenW + rPosX, lrPosY + textOffset),
			Vector2D(3 * fourthScreenW, lrAnchorPivotY),
			Vector2D(3 * fourthScreenW, lrAnchorPivotY),
			app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), rightTxt, textFontsize, TextComponent::Center,
			100, 100, 25);

		//icon frame
		mark = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Mark2),
			Vector2D(3 * fourthScreenW + rPosX, lrPosY),
			Vector2D(3 * fourthScreenW, lrAnchorPivotY),
			Vector2D(3 * fourthScreenW, lrAnchorPivotY),
			lrSize.getX(), lrSize.getY(), 0);

		// Player 2 abilities placing
		Entity* nav_j2 = entManager_.addEntity();
		NavigationController* ctrl_ = nav_j2->addComponent<NavigationController>(5, 3, app_->getGameManager()->getPlayerInfo(2).hid);
		// Abilities collocation on the available slots
		for (double i = 0; i < 10; i++) {
			Entity* habj2 = entManager_.addEntity();
			if (i < app_->getGameManager()->getPlayerInfo(2).abilities.size()) {
				if (i < 5) {
					habj2->addComponent<UIElement>();
					habj2->addComponent<UITransform>(
						Vector2D((slotX + i * slotX) + slotMargin_p2, slotY* firstRowFactor),
						Vector2D((slotX + i * slotX) + slotMargin_p2, slotY* firstRowFactor),
						Vector2D((slotX + i * slotX) + slotMargin_p2, slotY* firstRowFactor),
						slotSize);
					habj2->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::EmptyHability));
					ctrl_->SetElementInPos((habj2)->getComponent<UIElement>(ecs::UIElement), i, 0);
				}
				else {
					habj2->addComponent<UIElement>();
					habj2->addComponent<UITransform>(
						Vector2D((slotX + (i - 5) * slotX) + slotMargin_p2, slotY* secondRowFactor),
						Vector2D((slotX + (i - 5) * slotX) + slotMargin_p2, slotY* secondRowFactor),
						Vector2D((slotX + (i - 5) * slotX) + slotMargin_p2, slotY* secondRowFactor),
						slotSize);
					habj2->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::EmptyHability));
					ctrl_->SetElementInPos((habj2)->getComponent<UIElement>(ecs::UIElement), (i - 5), 1);
				}

				habj2->getComponent<RenderImage>(ecs::RenderImage)->setTexture(app_->getAssetsManager()
					->getTexture((AssetsManager::TextureNames)(AssetsManager::_abilityIcon_start + app_->getGameManager()->getPlayerInfo(2).abilities[i] + 1))); //no vas a poder acceder
			}

			else {
				if (i < 5) {
					habj2->addComponent<UIElement>();
					habj2->addComponent<UITransform>(
						Vector2D((slotX + i * slotX) + slotMargin_p2, slotY* firstRowFactor),
						Vector2D((slotX + i * slotX) + slotMargin_p2, slotY* firstRowFactor),
						Vector2D((slotX + i * slotX) + slotMargin_p2, slotY* firstRowFactor),
						slotSize);
					habj2->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::EmptyHability));
					ctrl_->SetElementInPos((habj2)->getComponent<UIElement>(ecs::UIElement), i, 0);
				}
				else {
					habj2->addComponent<UIElement>();
					habj2->addComponent<UITransform>(
						Vector2D((slotX + (i - 5) * slotX) + slotMargin_p2, slotY * secondRowFactor),
						Vector2D((slotX + (i - 5) * slotX) + slotMargin_p2, slotY * secondRowFactor),
						Vector2D((slotX + (i - 5) * slotX) + slotMargin_p2, slotY * secondRowFactor),
						slotSize);
					habj2->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::EmptyHability));
					ctrl_->SetElementInPos((habj2)->getComponent<UIElement>(ecs::UIElement), (i - 5), 1);
				}
			}
		}

		// Setting up the navigation
		for (int i = 0; i < 5; i++) {
			ctrl_->SetElementInPos(std::get<0>(boton1)->getComponent<UIElement>(ecs::UIElement), i, 2);
		}

		// Player 2 inventory logic
		Entity* logicJ2 = entManager_.addEntity();
		logicJ2->addComponent<InventoryLogic>(ctrl_, 2, left_j2->getComponent<RenderImage>(ecs::RenderImage), right_j2->getComponent<RenderImage>(ecs::RenderImage));

		Entity* ent = entManager_.addEntity();

		// Central text
		Entity* text_ = entManager_.addEntity();
		text_->addComponent<UITransform>(Vector2D(0, 0), Vector2D((app_->getWindowManager()->getCurResolution().w / 2), 0), Vector2D((app_->getWindowManager()->getCurResolution().w / 2), 0), Vector2D((double)app_->getWindowManager()->getCurResolution().w - 50, ((double)app_->getWindowManager()->getCurResolution().h / 20) + 50));
		text_->addComponent<TextComponent>("Prepare for the fight!", app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), 80, TextComponent::TextAlignment::Center);

		//Inventory Handler for two players
		ent->addComponent<InventoryHandler>(logicJ1, logicJ2);
	}

	//Inventory Handler if there's one player
	else {
		Entity* ent = entManager_.addEntity();
		ent->addComponent<InventoryHandler>(logicJ1, nullptr);
	}
}



void InventorySelection::handleInput()
{
	if (app_->getInputManager()->pressedStart()) {
		app_->getGameManager()->pressedStart();
	}
	else
		GameState::handleInput();

}

// Check if the newAb is actually new 
bool InventorySelection::checkAbility(GameManager::AbilityID newAb)
{
	//generated abilities here
	for (int i = 0; i < generatedAbs_1.size(); i++) {
		if (newAb == generatedAbs_1[i])
			return true;
	}
	std::vector<GameManager::AbilityID> aux = app_->getGameManager()->getPlayerInfo(1).abilities;
	//player1 abilities
	for (int i = 0; i < aux.size(); i++) {
		if (newAb == aux[i])
			return true;
	}
	generatedAbs_1.push_back(newAb);
	return false;
}


// Changes the text dependign on the player controller (keyboard or gamepad)
void InventorySelection::resolveHelpText(std::string& leftTxt, std::string& rightTxt, int player) {
	if (dynamic_cast<KeyboardHID*>(app_->getGameManager()->getPlayerInfo(player).hid) != nullptr) {
		leftTxt = "2";
		rightTxt = "3";
	}
	else {
		leftTxt = "LB";
		rightTxt = "RB";
	}
}