#include "SkillSelectionHandler.h"
#include "Entity.h"
#include "UITransform.h"
#include "InventorySelection.h"
#include "SkillSelectionLogic.h"

void SkillSelectionHandler::init()
{
}

void SkillSelectionHandler::update()
{
	pressed_1 = j1_->getComponent<SkillSelectionLogic>(ecs::InventoryLogic)->getPressed();
	pressed_2 = j2_->getComponent<SkillSelectionLogic>(ecs::InventoryLogic)->getPressed();
}

void SkillSelectionHandler::render()
{
}

void SkillSelectionHandler::handleInput()
{
	if (pressed_1 && pressed_2) {
		app_->getGameManager()->addHability(selectedAb, winner);
		app_->getStateMachine()->pushState(new InventorySelection(app_));
	}
}