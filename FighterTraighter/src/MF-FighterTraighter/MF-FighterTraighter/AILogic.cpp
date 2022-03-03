#include "AILogic.h"
#include "Bullet.h"

void AILogic::init()
{

}

void AILogic::update()
{
	if (otherPlayer_ == nullptr) {
		ecs::HandlerId id;
		if (playerID_ == ecs::Player1) id = ecs::Player2;
		else if (playerID_ == ecs::Player2) id = ecs::Player1;
		otherPlayer_ = state_->getEntityManager().getHandler(id);
	}

	//// Auxiliary variables
	//WorldInformation w;

	//// Get current world projectiles
	//std::list<Entity*> scene = state_->getEntityManager().getScene();
	//std::vector<Vector2D> tempVector;
	//for (auto ent : scene) {
	//	if (ent->getComponent<Bullet>(ecs::Bullet)) { // Can I recognize a projectile by this?
	//		tempVector.push_back(ent->getComponent<Transform>(ecs::Transform)->getPosition());
	//	}
	//}

	//// Push current world state
	//w.otherPlayerPosition_ = otherPlayer_->getComponent<Transform>(ecs::Transform)->getPosition();
	//w.otherPlayerStatus_ = (PlayerState::Status)otherPlayer_->getComponent<PlayerState>(ecs::PlayerState)->getState();
	//w.thisPosition_ = entity_->getComponent<Transform>(ecs::Transform)->getPosition();
	//w.projectilesPosition_ = std::move(tempVector);
	//worldReads_.push(w);

	//if (worldReads_.size() > reactionTime_) {

	//	// read the first state
	//	w = worldReads_.front();
	//	cout << w.otherPlayerPosition_.getX() << ", " << w.otherPlayerPosition_.getY() << endl;

	//	worldReads_.pop();
	//}




	++timePassed;
	// Auxiliary variables
	WorldInformation w;

	// Get current world projectiles
	std::list<Entity*> scene = state_->getEntityManager().getScene();
	std::vector<Vector2D> tempVector;
	for (auto ent : scene) {
		if (ent->getComponent<Bullet>(ecs::Bullet)) { // Can I recognize a projectile by this?
			tempVector.push_back(ent->getComponent<Transform>(ecs::Transform)->getPosition());
		}
	}

	if (worldReads_.size() == 0) {
		// Push current world state
		w.otherPlayerPosition_ = otherPlayer_->getComponent<Transform>(ecs::Transform)->getPosition();
		w.otherPlayerStatus_ = (PlayerState::Status)otherPlayer_->getComponent<PlayerState>(ecs::PlayerState)->getState();
		w.thisPosition_ = entity_->getComponent<Transform>(ecs::Transform)->getPosition();
		w.projectilesPosition_ = std::move(tempVector);
		worldReads_.push(w);
	}

	if (timePassed > reactionTime_) {

		// read the first state
		w = worldReads_.front();

		if (otherPlayer_->getComponent<PlayerState>(ecs::PlayerState)->isAttacking()) {
			int randN = app_->getRandGen()->nextInt(0, 10);
			if (randN <= 6)movementState_ = blocking;
		}
		else if (GetCloser()) {
			if (playerID_ == 0) movementState_ = movingRight;
			else movementState_ = movingLeft;
		}
		else if (GetFurther()) {
			if (playerID_ == 0) movementState_ = movingLeft;
			else movementState_ = movingRight;
		}
		else {
			int randN = app_->getRandGen()->nextInt(0, 50);
			if (randN < 29) movementState_ = idle;
			else if (randN < 39) movementState_ = attacking;
			else if (randN < 44) movementState_ = crouching;
			else movementState_ = jumping;
		}

		worldReads_.pop();
		timePassed = 0;
	}
}

bool AILogic::GetCloser()
{
	return abs(worldReads_.front().otherPlayerPosition_.getX() - worldReads_.front().thisPosition_.getX()) > preferredInterval_.getY();
}

bool AILogic::GetFurther()
{
	return abs(worldReads_.front().otherPlayerPosition_.getX() - worldReads_.front().thisPosition_.getX()) < preferredInterval_.getX();;
}
