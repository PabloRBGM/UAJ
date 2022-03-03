#include "Transform.h"

//constructor
Transform::Transform(Vector2D position, Vector2D speed, double width, double height, double rotation):
	Component(ecs::Transform),position_(position),speed_(speed), width_(width), height_(height), rotation_(rotation){}


//constructor, physics transform has the same ecs because is a similar component
Transform::Transform():
	Component(ecs::Transform),position_(),speed_(),width_(),height_(),rotation_() { }

Transform::~Transform()	{}
