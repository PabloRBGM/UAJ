#include "InventoryLogic.h"
#include "Entity.h"
#include "UITransform.h"
InventoryLogic::InventoryLogic(NavigationController* nav, int player, RenderImage* left, RenderImage* right):
	Component(ecs::InventoryLogic), nav_(nav), player_(player), left_(left), right_(right)
{
}

//Two first abilties selected by default
void InventoryLogic::init()
{
	pressed = false;
	abs_size = app_->getGameManager()->getPlayerInfo(player_).abilities.size();
	ab1_index = 0;
	ab2_index = 1;
	app_->getGameManager()->setFirstHab(ab1_index, player_);
	app_->getGameManager()->setSecondHab(ab2_index, player_);
	left_->setTexture(app_->getAssetsManager()->getTexture((AssetsManager::TextureNames)(AssetsManager::_abilityIcon_start + app_->getGameManager()->getPlayerInfo(player_).abilities[ab1_index] + 1)));
	right_->setTexture(app_->getAssetsManager()->getTexture((AssetsManager::TextureNames)(AssetsManager::_abilityIcon_start + app_->getGameManager()->getPlayerInfo(player_).abilities[ab2_index] + 1)));
	ent = new Entity();
	ent->addComponent<Transform>(Vector2D(), Vector2D(), 150, 150, 45);
	ent->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::SelectionSquare));
	offset = Vector2D(-10.0, -10.0);
}

// Updates the selection square
void InventoryLogic::update()
{
	if (!pressed) {
		Vector2D selectionPos = nav_->GetElementInPos(nav_->GetPosX(), nav_->GetPosY())->getEntity()->getComponent<UITransform>(ecs::Transform)->getPosition() + offset;
		ent->getComponent<Transform>(ecs::Transform)->setPosition(selectionPos);
	}
}

// Renders the selection square
void InventoryLogic::render()
{
	if (!pressed&& nav_->GetPosY()<2) {
		ent->render();
	}
}

// Handles input to move through the inventory matrix
// Updates left or right images and players abilities depending on player input
// Checks if the player pressed the ready button
void InventoryLogic::handleInput()
{
	int posY = nav_->GetPosY();
	if ( posY != 2) {
		if (app_->getGameManager()->getPlayerInfo(player_).hid->ButtonPressed(HID::LeftBumper) && !pressed) {
			int indX = nav_->GetPosX();
			if (posY > 0) {
				indX += 5;
			}
			if (indX < abs_size) {
				if (indX == ab2_index) {
					swapIndex();
				}
				else {
					ab1_index = indX;
					left_->setTexture(app_->getAssetsManager()->getTexture((AssetsManager::TextureNames)(AssetsManager::_abilityIcon_start + app_->getGameManager()->getPlayerInfo(player_).abilities[ab1_index] + 1)));
					app_->getGameManager()->setFirstHab(ab1_index, player_);
				}
			}
		}
		if (app_->getGameManager()->getPlayerInfo(player_).hid->ButtonPressed(HID::RightBumper) && !pressed) {
			int indX = nav_->GetPosX();
			if (posY > 0) {
				indX += 5;
			}		
			if ( indX < abs_size) {
				if (indX == ab1_index) {
					swapIndex();
				}
				else {
					ab2_index = indX;
					right_->setTexture(app_->getAssetsManager()->getTexture((AssetsManager::TextureNames)(AssetsManager::_abilityIcon_start + app_->getGameManager()->getPlayerInfo(player_).abilities[ab2_index] + 1)));
					app_->getGameManager()->setSecondHab(ab2_index, player_);
				}
			}			
		}
	}
	else 
	{
		HID* owner_controller = app_->getGameManager()->getPlayerInfo(player_).hid;
		if ((owner_controller->ButtonPressed(HID::RightPad_Down) || owner_controller->ButtonPressed(HID::Select)) && !pressed) {
			pressed = true;
		#ifdef _DEBUG
			cout << "waiting for fight";
		#endif
		}
		
		else if (pressed && owner_controller->ButtonPressed(HID::RightPad_Right)) {
			pressed = false;
		#ifdef _DEBUG
			cout << "Canceled";
		#endif		
		}
	}
}

// Swaps indexes of the abilities and
// refreshes the left/right textures
void InventoryLogic::swapIndex() {
	int aux = ab1_index;
	ab1_index = ab2_index;
	ab2_index = aux;

	app_->getGameManager()->setFirstHab(ab1_index, player_);
	app_->getGameManager()->setSecondHab(ab2_index, player_);

	//actualizar texturas
	left_->setTexture(app_->getAssetsManager()->getTexture((AssetsManager::TextureNames)(AssetsManager::_abilityIcon_start + app_->getGameManager()->getPlayerInfo(player_).abilities[ab1_index] + 1)));
	right_->setTexture(app_->getAssetsManager()->getTexture((AssetsManager::TextureNames)(AssetsManager::_abilityIcon_start + app_->getGameManager()->getPlayerInfo(player_).abilities[ab2_index] + 1)));
}