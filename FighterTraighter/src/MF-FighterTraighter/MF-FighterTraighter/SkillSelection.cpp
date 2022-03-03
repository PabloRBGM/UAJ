#include "SkillSelection.h"
#include "UIFactory.h"
#include "Entity.h"
#include "RenderImage.h"
#include "UITransform.h"
#include "Fight.h"
#include "NavigationController.h"
#include "InventorySelection.h"
#include "SkillSelectionLogic.h"

void SkillSelection::init()
{
	GameState::init();
	
	//Background
	Entity* b = entManager_.addEntity();
	b->addComponent<UITransform>(Vector2D(), Vector2D(), Vector2D(), Vector2D(app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h));
	b->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::BackgroundFight));

	int loser = 1;
	if (winner_ == 1) 
		loser = 2;
	
	// Player1 submenu panel
	UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Celda1),
		Vector2D(0, 0), 
		Vector2D(50, 50), 
		Vector2D(0, 0), 
		((double)app_->getWindowManager()->getCurResolution().w / 2)-100, (double)app_->getWindowManager()->getCurResolution().h-100, 0);
	
	// Player2 submenu panel
	UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Celda1),
		Vector2D(0, 0),
		Vector2D((double)app_->getWindowManager()->getCurResolution().w - 430, 50),
		Vector2D(430.0 + 50.0,0),
		((double)app_->getWindowManager()->getCurResolution().w / 2) - 100, ((double)app_->getWindowManager()->getCurResolution().h) - 100, 0);
	
	


	//Winner chooses text
	double txtMargin;
	if (winner_ == 1)
		txtMargin = -600.0;
	else
		txtMargin = 300;

	Entity* text = UIFactory::createText(app_, this,
		Vector2D(txtMargin, 0),
		Vector2D(((double)app_->getWindowManager()->getCurResolution().w / 2), (double)app_->getWindowManager()->getCurResolution().h - 200),
		Vector2D(0, 0),
		app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), ("Player " + to_string(winner_) + " chooses!"),
		60, TextComponent::Center, 300, 100, 500);


	//Icon position variables
	Vector2D iconPos = Vector2D();
	Vector2D iconAnchor = Vector2D();
	const Vector2D iconPivot = Vector2D(80, 80);
	const Vector2D iconSize = Vector2D(160, 160);
	const double frameSep = 300.0;

	//The winner obtains 3 random abilities, he can choose between the first 2
	GameManager::AbilityID abi1;
	Entity* nav_j1 = entManager_.addEntity();
	NavigationController* nav = nav_j1->addComponent<NavigationController>(2, 1, app_->getGameManager()->getPlayerInfo(winner_).hid);
	for (int i = 0; i < 3; i++) {
		do {
			abi1 = (GameManager::AbilityID)app_->getRandGen()->nextInt(GameManager::level1_flag, GameManager::max_level_flag);
		} while (checkAbility(abi1, winner_));
		//Ability icon
		AssetsManager::TextureNames abrand = (AssetsManager::TextureNames)(AssetsManager::_abilityIcon_start + abi1 + 1);
		
		//Icon placing depending on the winner
		Entity* ab1 = entManager_.addEntity();
		Entity* mark;
		
		ab1->addComponent<UIElement>();
		if (winner_ == 1) {
			if (i < 2) {

				iconAnchor = Vector2D((i * frameSep) + frameSep, (app_->getWindowManager()->getCurResolution().h / 2.0) - frameSep);
				//icon image
				ab1->addComponent<UITransform>(iconPos, iconAnchor, iconPivot, iconSize);
				ab1->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(abrand));
				nav->SetElementInPos((ab1)->getComponent<UIElement>(ecs::UIElement), i, 0);

				//icon frame
				mark = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Mark2),
					iconPos,
					iconAnchor,
					iconPivot,
					iconSize.getX(), iconSize.getY(), 0);
			}
			else {
				iconAnchor = Vector2D(app_->getWindowManager()->getCurResolution().w / 4.0, (double)app_->getWindowManager()->getCurResolution().h / 2.0);
				//icon image
				ab1->addComponent<UITransform>(
					iconPos,
					iconAnchor,
					iconPivot,
					iconSize);

				ab1->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(abrand));
				app_->getGameManager()->addHability(abi1, winner_);

				//icon frame
				mark = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Mark1),
					iconPos,
					iconAnchor,
					iconPivot,
					iconSize.getX(), iconSize.getY(), 0);
			}
		}
		else {
			if (i < 2) {
				iconPos.setX(50);
				iconAnchor = Vector2D(app_->getWindowManager()->getCurResolution().w / 2 + ((double)i * frameSep) + frameSep, ((double)app_->getWindowManager()->getCurResolution().h / 2) - frameSep);
				ab1->addComponent<UITransform>(
					iconPos,
					iconAnchor,
					iconPivot,
					iconSize);

				ab1->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(abrand));
				nav->SetElementInPos((ab1)->getComponent<UIElement>(ecs::UIElement), i, 0);

				mark = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Mark2),
					iconPos,
					iconAnchor,
					iconPivot,
					iconSize.getX(), iconSize.getY(), 0);

				iconPos.setX(0);
			}
			else {
				iconAnchor = Vector2D(((app_->getWindowManager()->getCurResolution().w / 4)) * 3, ((double)app_->getWindowManager()->getCurResolution().h / 2));
				ab1->addComponent<UITransform>(
					iconPos,
					iconAnchor,
					iconPivot,
					iconSize);

				ab1->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(abrand));
				app_->getGameManager()->addHability(abi1, winner_);

				mark = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Mark1),
					iconPos,
					iconAnchor,
					iconPivot,
					iconSize.getX(), iconSize.getY(), 0);
			}
		}
	}

	

	//The winner is the only one that can navigate through this menu
	Entity* log = entManager_.addEntity();
	if (winner_ == 1) {
		log->addComponent<SkillSelectionLogic>(nav, winner_, generatedAbs_1);
	}
	else {
		log->addComponent<SkillSelectionLogic>(nav, winner_, generatedAbs_2);
	}
	
	//The losing player gets two random abilities and doesn't get to choose
	for (int i = 0; i < 2; i++) {
		do {
			abi1 = (GameManager::AbilityID)app_->getRandGen()->nextInt(GameManager::level1_flag, GameManager::max_level_flag);
		} while (checkAbility(abi1, loser));
		//Ability icon
		AssetsManager::TextureNames abrand = (AssetsManager::TextureNames)(AssetsManager::_abilityIcon_start + abi1 + 1);
		Entity* ab1 = entManager_.addEntity();
		Entity* mark;
		//Icon placing depending on the winner
		if (winner_ == 1) {			
			iconAnchor = Vector2D((((double)app_->getWindowManager()->getCurResolution().w) / 4) * 3, (((double)app_->getWindowManager()->getCurResolution().h) / 2) + (frameSep * (i - 1)));
			ab1->addComponent<UIElement>();
			ab1->addComponent<UITransform>(
				iconPos,
				iconAnchor,
				iconPivot,
				iconSize);
			ab1->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(abrand));
			app_->getGameManager()->addHability(abi1, loser);

			mark = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Mark1),
				iconPos,
				iconAnchor,
				iconPivot,
				iconSize.getX(), iconSize.getY(), 0);
		}
		else {
			iconAnchor = Vector2D(((app_->getWindowManager()->getCurResolution().w) / 4), (((double)app_->getWindowManager()->getCurResolution().h / 2) + (frameSep * (i - 1.0))));
			ab1->addComponent<UIElement>();
			ab1->addComponent<UITransform>(
				iconPos,
				iconAnchor,
				iconPivot,
				iconSize);
			ab1->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(abrand));
			app_->getGameManager()->addHability(abi1, loser);

			mark = UIFactory::createPanel(app_, this, app_->getAssetsManager()->getTexture(AssetsManager::Mark1),
				iconPos,
				iconAnchor,
				iconPivot,
				iconSize.getX(), iconSize.getY(), 0);
		}
	}
}

//	Ads an ability to the generatedAbilities vector depending on the player.
//	Ads a non repeated ability considering the abilities already generated
//	and the abilities that the player already has
bool SkillSelection::checkAbility(GameManager::AbilityID newAb, int player) {

	std::vector<GameManager::AbilityID> aux = app_->getGameManager()->getPlayerInfo(player).abilities;
	if (player == 1) {	
		for (int i = 0; i < generatedAbs_1.size(); i++) {
			if (newAb == generatedAbs_1[i])
				return true;
		}

		for (int i = 0; i < aux.size(); i++) {
			if (newAb == aux[i])
				return true;
		}
		generatedAbs_1.push_back(newAb);
		return false;
	}
	else {
		for (int i = 0; i < generatedAbs_2.size(); i++) {
			if (newAb == generatedAbs_2[i])
				return true;
		}

		//player2 abilities
		for (int i = 0; i < aux.size(); i++) {
			if (newAb == aux[i])
				return true;
		}	
		generatedAbs_2.push_back(newAb);
		return false;
	}
	
}

void SkillSelection::handleInput() {	
	if (app_->getInputManager()->pressedStart()) {
		app_->getGameManager()->pressedStart();
	}
	else
		GameState::handleInput();
}