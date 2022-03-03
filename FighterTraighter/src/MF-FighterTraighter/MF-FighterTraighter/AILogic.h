#pragma once
#include "Component.h"
#include "PlayerState.h"
#include "Vector2D.h"
#include <queue>
class AILogic :
	public Component
{
public:
	enum AIStates {
		idle,
		movingLeft,
		movingRight,
		//We should not separate states tbh
		attacking,
		blocking,
		crouching,
		jumping
	};


protected:
	// Size: (49 + nProjectiles * 24) bytes
	struct WorldInformation {
		PlayerState::Status otherPlayerStatus_; // 1 byte
		Vector2D otherPlayerPosition_; // 24 bytes
		Vector2D thisPosition_; // 24 bytes
		std::vector<Vector2D> projectilesPosition_; // nProjectiles * 24 bytes
	};

public:
	AILogic(ecs::HandlerId playerID, int reactionTime, Vector2D interval) : Component(ecs::AILogic), reactionTime_(reactionTime), playerID_(playerID), preferredInterval_(interval) {}

	void init() override;
	void update() override;

	inline AIStates getMovingState() { return movementState_; }

	virtual ~AILogic() {};
protected:
	bool GetCloser();
	bool GetFurther();

	AIStates movementState_;
	//AIStates attackState_;	//??

	Vector2D preferredInterval_;	//Min, Max
	int reactionTime_;
	int timePassed = 0;
	ecs::HandlerId playerID_;


	// Current information
	Entity* otherPlayer_;
	std::vector<Entity*> projectiles_;

	// Each item was the state of the world captured at that moment
	std::queue<WorldInformation> worldReads_;
};

