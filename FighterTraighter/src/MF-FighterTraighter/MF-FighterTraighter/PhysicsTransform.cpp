#include "PhysicsTransform.h"
#include "UserData.h"
//	cBits are the category bits, the collision group this body is in
//	cMask are the mask bits, the collision groups to check
//	if not modified, the body will collide with everything
PhysicsTransform::PhysicsTransform(Vector2D position, Vector2D speed, double width, double height, double rotation,b2World* world, uint16 cBits, uint16 mBits, int dyn)
	: Transform(position, speed, width, height, rotation), cBits_(cBits), mBits_(mBits), dynamic_(dyn),world_(world), col_width_(width),
	col_height_(height), body_(nullptr), mainFixture_(nullptr)
{
}


PhysicsTransform::~PhysicsTransform() {
	resetUserData(nullptr);
}

void PhysicsTransform::resetUserData(UserData* newData) {
	//if (newData == nullptr) {
	//int* m = nullptr;
	//delete m;
	delete static_cast<UserData*>(mainFixture_->GetUserData());
	mainFixture_->SetUserData(newData);
	/*}
	else {
		cout << "mal";
	}*/
}

void PhysicsTransform::init() {
	b2BodyDef bodydef;
	bodydef.position.Set((float32)position_.getX() * app_->METERS_PER_PIXEL,(float32) position_.getY() * app_->METERS_PER_PIXEL);
	if (dynamic_ == 0)
		bodydef.type = b2_dynamicBody;	//makes the dynamic body if it is dynamic
	else if (dynamic_ == 1) bodydef.type = b2_kinematicBody;
	else  bodydef.type = b2_staticBody;//default
	body_ = world_->CreateBody(&bodydef);
	resetMainFixture(b2Vec2_zero, 0);	//por defecto en el centro del cuerpo, y con angulo 0
	body_->SetFixedRotation(true);
	//The default userData is the entity
	mainFixture_->SetUserData(new UserData(this->entity_));
}

void PhysicsTransform::setHeight(double height) {
	height_ = height;
}

void PhysicsTransform::setColliderHeight(double height, Vector2D center, float angle) {

	col_height_ = height;
	void* prev_data = mainFixture_->GetUserData();	//it applies to the new collider the same user data as it had before
	body_->DestroyFixture(mainFixture_);
	resetMainFixture((b2Vec2)(center * app_->METERS_PER_PIXEL), angle);
	mainFixture_->SetUserData(prev_data);
}

void PhysicsTransform::setWidth(double width) {
	width_ = width;
}

void PhysicsTransform::setColliderWidth(double width, Vector2D center, float angle) {

	col_width_ = width;
	void* prev_data = mainFixture_->GetUserData();	//it applies to the new collider the same user data as it had before
	body_->DestroyFixture(mainFixture_);
	resetMainFixture((b2Vec2)(center * app_->METERS_PER_PIXEL), angle);
	mainFixture_->SetUserData(prev_data);
}

void PhysicsTransform::setSize(double width, double height) {
	width_ = width, height_ = height;
}

void PhysicsTransform::setColliderSize(double width, double height, Vector2D center, float angle) {

	col_width_ = width;
	col_height_ = height;
	void* prev_data = mainFixture_->GetUserData();	//it applies to the new collider the same user data as it had before
	body_->DestroyFixture(mainFixture_);
	resetMainFixture((b2Vec2)(center * app_->METERS_PER_PIXEL), angle);
	mainFixture_->SetUserData(prev_data);
}

void PhysicsTransform::moveCollider(const Vector2D& move) {
	b2Shape* preShape = mainFixture_->GetShape();
}


void PhysicsTransform::resetMainFixture(const b2Vec2& center, float angle) {
	b2PolygonShape shape;
	shape.SetAsBox((col_width_ * (float32)app_->METERS_PER_PIXEL) * wMult_ / 2, (col_height_ * (float32)app_->METERS_PER_PIXEL) * hMult_ / 2, center, angle);
	b2FixtureDef fixturedef;
	fixturedef.shape = &shape;
	fixturedef.density = 0.0f;
	fixturedef.filter.categoryBits = cBits_;
	fixturedef.filter.maskBits = mBits_;
	fixturedef.friction = 0;
	mainFixture_ = body_->CreateFixture(&fixturedef);
}

void PhysicsTransform::changeMask(uint16 newMask) {
	b2Filter filter;
	filter=mainFixture_->GetFilterData();
	//filter.categoryBits = filte;
	filter.maskBits = newMask;
	//filter.groupIndex = ...;
	//f->SetFilterData(&filter);
	mainFixture_->SetFilterData(filter);
}

void PhysicsTransform::changeFriction(float32 newFrict)
{
	mainFixture_->SetFriction(newFrict);
}

void PhysicsTransform::resetMainFixture2(const b2Vec2& center, float angle , float32 newFrict) {
	b2PolygonShape shape;
	shape.SetAsBox((col_width_ * (float32)app_->METERS_PER_PIXEL) * wMult_ / 2, (col_height_ * (float32)app_->METERS_PER_PIXEL) * hMult_ / 2, center, angle);
	b2FixtureDef fixturedef;
	fixturedef.shape = &shape;
	fixturedef.density = 0.0f;
	fixturedef.filter.categoryBits = cBits_;
	fixturedef.filter.maskBits = mBits_;
	fixturedef.friction = newFrict;
	mainFixture_ = body_->CreateFixture(&fixturedef);
}