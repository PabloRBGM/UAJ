#include "SacoManager.h"
#include "LastHit_Wins.h"
#include "MoreDamage_Wins.h"
#include "TrainingController.h"

int SacoManager::rndInter = 0;

void SacoManager::init() {

	transform_ = entity_->getComponent<PhysicsTransform>(ecs::Transform);
	rndInter = ((rndInter + 1) % 2);
	PunchingBagInteraction aux = (PunchingBagInteraction)rndInter;
	PunchingBagOnHit* pb = nullptr;
	switch (aux)
	{
	case LAST_HIT:
		pb = new LastHit_Wins(entity_);
		transform_->resetUserData(pb);
		infoText = "Last Hit the Punching Bag!";
		break;
	case MORE_DAMAGE:
		pb = new MoreDamage_Wins(entity_);
		transform_->resetUserData(pb);	//este seria diferente
		infoText = "Destroy the Punching Bag!";
		break;
	default:
		pb = nullptr;
		break;
	}

	//entity_->getState()->getEntityManager().getHandler(ecs::Controller)->getComponent<TrainingController>(ecs::TrainingController)->setIniText(pb->getInfoMessage());
	
}

//updates the punchingBag time limit
void SacoManager::update() {
	if (timerOn) {
		currTime_ = SDL_GetTicks() - startTime_;
		if (currTime_ > timeLimit_) {
			int winner = (static_cast<PunchingBagOnHit*>(entity_->getComponent<PhysicsTransform>(ecs::Transform)->getUserData()))->timeout_Winner();
			entity_->getState()->getEntityManager().getHandler(ecs::Controller)->getComponent<TrainingController>(ecs::TrainingController)->PlayerWins(winner);
		}
	}
}

void SacoManager::startTimer() {
	timerOn = true;
	startTime_ = SDL_GetTicks();
	//instanciar el timer en pantalla
	Entity* timer = state_->getEntityManager().addEntity();
	timer->addComponent<UITransform>(Vector2D(0, 120), Vector2D(app_->getWindowManager()->getCurResolution().w / 2, 0), Vector2D(200, 50), Vector2D(400, 100));
	timer->addComponent<TextComponent>("0000", app_->getAssetsManager()->getFont(AssetsManager::Roboto_Black), 45, TextComponent::Center);
	timer->addComponent<UITimer>(UITimer::Seconds)->setCountdown(timeLimit_);
}