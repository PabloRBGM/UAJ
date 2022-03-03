#include "PlayerData.h"

PlayerData::PlayerData(double width, double height, double rotation, double jump_impulse, Vector2D ini_pos, 
	double speed, double ini_health, double attack, double defense, int playerNumber) :
    Component(ecs::PlayerData), width_(&width), height_(&height), rotation_(&rotation), jump_impulse_(&jump_impulse),
	initial_position_(ini_pos), speed_(&speed), health_(&ini_health), attack_(attack), defense_(defense), 
	playerNumber_(playerNumber){ }