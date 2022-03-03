#pragma once
#include <ctime>

namespace ecs {

	using CmpIdType = std::size_t;
	using HandlerIdType = std::size_t;

	enum CmpId : CmpIdType {
		Transform = 0,
		CharacterController,
		Health,
		RenderImage,
		RenderAnimation,
		TextComponent,
		Jump,
		SacoTimer,
		SacoManager,
		PunchingBagCollision,
		Crouch,
		CharacterAttacks,
		VerticalSlider,
		IndexSlider,
		CreatorBody,
		HitboxMng,
		InventoryLogic,
		OptionsLogic,
		CharacterSelectionLogic,
		CharacterSelectionHandler,
		NavigationController,
		PlayerState,
		OnHit,
		UIElement,
		UITimer,
		UIHealthbar,
		UIRoundRenderer,
		PlayerData,
		PlayerAnimation,
		InputState,
		KeyboardInput,
		GamepadInput,
		Bullet,
		Camera,
		AbilitiesTimerFunction,
		Shake,
		PlayerParticleSystem,
		AILogic,
		FightController,
		TrainingController,
		GraphicsOptionsLogic,
		AudioOptionsLogic,
		IAController,
		/*
		
		*/
		_LastCmptId_
	};

	enum HandlerId : HandlerIdType {
		Player1 = 0,
		Player2,
		Saco,
		Controller,
		Camara,
		/*
		
		*/
		_LastHndlrId_
	};

	constexpr std::size_t maxComponents = _LastCmptId_;
	constexpr std::size_t maxHandlers = _LastHndlrId_;

	// these two should be used to get a component via the field
	// entity_
#define GETCMP2_(id,type)  GETCMP3(entity_,id,type)
#define GETCMP1_(type)     GETCMP3(entity_,ecs::type,type)

// these two should be used to get a component via an
// entity e provided as a parameter
#define GETCMP2(e,type) GETCMP3(e,ecs::type,type)
#define GETCMP3(e,id,type) e->getComponent<type>(id)

}
