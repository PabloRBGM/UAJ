#pragma once
#include "GameState.h"
#include "Box2D\Box2D.h"
#include "PhysicsTransform.h"
#include "SDLDebugDraw.h"
#include "PlayerAttacks.h"
#include "Entity.h"
#include "PlayerController.h"
#include "RenderImage.h"
#include "PauseMenu.h"
#include "ResetJumpListener.h"
#include "UITimer.h"

class Fight : public GameState
{
public:
	Fight(App* app);
	void init() override;
	virtual void handleInput() override;
	virtual ~Fight();
};
