#include "CharacterAttacks.h"

CharacterAttacks::CharacterAttacks(AnimationChain* highFist, AnimationChain* airHighFist, AnimationChain* lowFist, AnimationChain* airLowFist,
	AnimationChain* highKick, AnimationChain* airHighKick, AnimationChain* lowKick, AnimationChain* airLowKick, AnimationChain* testGB) : Component(ecs::CharacterAttacks)
{
	attacksList.push_back(highFist);
	attacksList.push_back(lowFist);
	attacksList.push_back(highKick);
	attacksList.push_back(lowKick);
	attacksList.push_back(airHighFist);
	attacksList.push_back(airLowFist);
	attacksList.push_back(airHighKick);
	attacksList.push_back(airLowKick);
	attacksList.push_back(testGB);
}

CharacterAttacks::~CharacterAttacks()
{
	//hay que descomentar cuando las animaciones sean diferentes
	for (int i = 0; i < attacksList.size(); i++) {
		delete attacksList[i];
		attacksList[i] = nullptr;

	}
	attacksList.clear();

	for (int i = 0; i < abilityList.size(); i++) {
		delete abilityList[i];
		abilityList[i] = nullptr;
	}
	abilityList.clear();
}

void CharacterAttacks::setAbility(AnimationChain* newAbility, int index)
{
	if (abilityList[index] != nullptr)delete abilityList[index]; //Necesario? no se
	abilityList[index] = newAbility;
}

//if u are attacking, interrupt it, also check if your orientation is right just in case
void CharacterAttacks::interruptAttack()
{
	PhysicsTransform* pT = entity_->getComponent<PhysicsTransform>(ecs::Transform);
	if (entity_->getComponent<PlayerData>(ecs::PlayerData)->getPlayerNumber() == 0)
		pT->setOrientation(1);
	else   pT->setOrientation(-1);


	if (activeAttack_ != nullptr) {
		activeAttack_->reset();
		activeAttack_ = nullptr;
		resetOneTimeMultiplier();
	}
	//destroy all attack´s hitboxes
	app_->getStateMachine()->getCurrentState()->resetGroup((entity_->getComponent<PhysicsTransform>(ecs::Transform)->getMainFixture()->GetFilterData().categoryBits) >> 2);
}

int CharacterAttacks::getAbilityIndex()	//IN THEORY IT NEVER SHOULD RETURN -1
{										//BUT
	int index = -1;
	for (int i = 0; i < abilityList.size(); ++i) {
		if (activeAttack_ == abilityList[i]) index = i;
	}
	return index;
}

void CharacterAttacks::setTimeCool(int ind, int cool)
{
	if (ind == 0) { timeCool0 = cool; }
	if (ind == 1) { timeCool1 = cool; }
}

void CharacterAttacks::activeTimer(int ind, bool act)
{
	if (ind == 0) {
		actTimer0 = act;
	}
	if (ind == 1) {
		actTimer1 = act;
	}
}

bool CharacterAttacks::IsTimerActive(int ind)
{
	if (ind == 0) return actTimer0;
	if (ind == 1) return actTimer1;
}

int CharacterAttacks::getTimeCool(int ind)
{
	if (ind == 0) return timeCool0;
	if (ind == 1) return timeCool1;
}
