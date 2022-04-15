#pragma once

#define NUM_PLAYERS 2
#define NUM_ABILITIES 2

enum EventType {
	SessionStart,
	SessionEnd,
	RoundStart,
	RoundEnd,
	Attack,
	Ability,
	ReceiveDamage,
	ERROR
};

enum Players {
	PLAYER1, PLAYER2
};

enum Characters {
	MKWH00P, F10R, Mockingbird
};

enum Attacks {
	NormalPunch,
	HeavyPunch,
	NormalKick,
	Heavykick,
	AirNormalPunch,
	AirHeavyPunch,
	AirNormalKick,
	AirHeavyKick,
	GuardBreaker,
	NoAttack
};

enum Abilities {
	//------level 1------//
	ShrugOff,
	ReachingStrike,
	MorePower,
	Pollo,
	//------level 2------//
	AcidSplit,
	Dash,
	VampiricStrike,
	LaserLineal,
	//------level 3------//
	Mina,
	Hookshot,
	HailBall,
	KnockDown,
	//------level 4------//
	ExplosiveWillpower,
	FlyingKicks,
	NadoKick,
	//------level 5------//
	MegatonGrip,
	SeismicShock,
	NoAbility
};