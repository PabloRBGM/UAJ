#include "AbilitySelection.h"
#include "UITransform.h"
#include "RenderImage.h"

void AbilitySelection::init()
{
	GameState::init();

	Entity* b = entManager_.addEntity();
	b->addComponent<UITransform>(Vector2D(), Vector2D(), Vector2D(), Vector2D(app_->getWindowManager()->getCurResolution().w, app_->getWindowManager()->getCurResolution().h));
	b->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(AssetsManager::BackgroundFight));

	AssetsManager::TextureNames abi1 = (AssetsManager::TextureNames)(GameManager::AbilityID)app_->getRandGen()->nextInt(GameManager::level1_flag, GameManager::max_level_flag);
	AssetsManager::TextureNames abrand = (AssetsManager::TextureNames)(AssetsManager::_abilityIcon_start + abi1);
	Entity* ab1 = entManager_.addEntity();
	ab1->addComponent<UITransform>(Vector2D(400, 600), Vector2D(), Vector2D(), Vector2D(300, 300));
	ab1->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(abrand));

	AssetsManager::TextureNames abi2;
	do {
		abi2 = (AssetsManager::TextureNames)(GameManager::AbilityID)app_->getRandGen()->nextInt(GameManager::level1_flag, GameManager::max_level_flag);
	} while (abi1 == abi2);

	AssetsManager::TextureNames abrand2 = (AssetsManager::TextureNames)(AssetsManager::_abilityIcon_start + abi2);
	Entity* ab2 = entManager_.addEntity();
	ab2->addComponent<UITransform>(Vector2D(800, 600), Vector2D(), Vector2D(), Vector2D(300, 300));
	ab2->addComponent<RenderImage>(app_->getAssetsManager()->getTexture(abrand2));

	/*pWin->abilitiesInventory.push_back((AbilityID)app_->getRandGen()->nextInt(level1_flag, max_level_flag));
	pWin->abilitiesInventory.push_back((AbilityID)app_->getRandGen()->nextInt(level1_flag, max_level_flag));*/
}
