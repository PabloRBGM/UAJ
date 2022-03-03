#include "CharacterSelectionHandler.h"
#include "Entity.h"
#include "UITransform.h"
#include "Training.h"
#include "InventorySelection.h"
void CharacterSelectionHandler::init()
{
	ent = state_->getEntityManager().addEntity();
	ent->addComponent<Transform>(Vector2D(0, app_->getWindowManager()->getCurResolution().h/4), Vector2D(), app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h / 4,0);
	ent->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::Panel))->setRendered(false);
}

void CharacterSelectionHandler::update()
{
	RenderImage* rImage = ent->getComponent<RenderImage>(ecs::RenderImage);
	j1_ = log1->getComponent<CharacterSelectionLogic>(ecs::CharacterSelectionLogic)->getChosen();
	if(log2)//2 players
		j2_ = log2->getComponent<CharacterSelectionLogic>(ecs::CharacterSelectionLogic)->getChosen();

	if (j1_ && j2_) {
		--goTimer;
		if (!rImage->getRendered()) rImage->setRendered(true);
		if (goTimer == 0) {
			app_->getStateMachine()->pushState(new Training(app_));
		}
	}//1 player
	else if (j1_ && log2 == nullptr) {
		--goTimer;
		if (!rImage->getRendered()) rImage->setRendered(true);
		if (goTimer == 0) {
			app_->getStateMachine()->pushState(new InventorySelection(app_,1));
		}
	}
	else {
		if (rImage->getRendered()) rImage->setRendered(false);
	}
}
