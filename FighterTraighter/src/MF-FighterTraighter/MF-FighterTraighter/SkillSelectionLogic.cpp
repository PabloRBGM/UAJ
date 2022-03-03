#include "SkillSelectionLogic.h"
#include "Entity.h"
#include "RenderImage.h"
#include "UITransform.h"
#include "InventorySelection.h"

SkillSelectionLogic::SkillSelectionLogic(NavigationController* nav, int player, vector<GameManager::AbilityID> v):Component(ecs::OptionsLogic), nav_(nav), player_(player), v_(v), op(op)
{
	
}

SkillSelectionLogic::~SkillSelectionLogic()
{
	delete ent;
}

void SkillSelectionLogic::init()
{
	op = v_[0];
	ent = new Entity();
	ent->addComponent<Transform>(Vector2D(), Vector2D(), 170, 170, 0);
	ent->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::SelectionSquare));
}

void SkillSelectionLogic::update()
{
	ent->getComponent<Transform>(ecs::Transform)->setPosition
	(nav_->GetElementInPos(nav_->GetPosX(), nav_->GetPosY())->getEntity()->getComponent<UITransform>(ecs::Transform)->getPosition());
}

void SkillSelectionLogic::render()
{
	ent->render();
}

void SkillSelectionLogic::handleInput()
{
	HID* owner_controller = app_->getGameManager()->getPlayerInfo(player_).hid;
	if (owner_controller->ButtonPressed(HID::RightPad_Down) || owner_controller->ButtonPressed(HID::Select)) {
		// estamos en la fila 0 y escogemos la habilidad opcional
		if (nav_->GetPosY() == 0) {

			op = v_[nav_->GetPosX()];
			app_->getGameManager()->addHability(op, player_);
			app_->getStateMachine()->pushState(new InventorySelection(app_));
		}
	}
}
