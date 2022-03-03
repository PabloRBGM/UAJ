#include "Component.h"

Component::Component(ecs::CmpId id):entity_(nullptr),id_(id), app_(nullptr), state_(nullptr)
{}

Component::~Component()
{}
