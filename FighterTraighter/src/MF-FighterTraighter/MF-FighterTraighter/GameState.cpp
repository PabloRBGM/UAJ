#include "GameState.h"
#include "Entity.h"
#include "App.h"
#include "OnHit.h"
#include "ResetJumpListener.h"
#include "HitboxData.h"
#include "DestroyOnHit.h"
GameState::GameState(App* app) : app_(app), entManager_(app, this), world(nullptr)
{
}
void GameState::init()
{
	gravity = Vector2D(0.0f, 10.0f);
	world = new b2World(gravity);
#if _DEBUG
	debugInstance = new SDLDebugDraw(app_->getRenderer(), app_->PIXELS_PER_METER);
	world->SetDebugDraw(debugInstance);
	debugInstance->SetFlags(b2Draw::e_shapeBit);
#else
#endif
	resJumpListener = new ResetJumpListener();
	world->SetContactListener(resJumpListener);

}

void GameState::handleInput()
{
	for (auto it = entManager_.getScene().begin(); it != entManager_.getScene().end(); ++it) {
		(*it)->handleInput();
	}
}

void GameState::update()
{
	for (auto it = entManager_.getScene().begin(); it != entManager_.getScene().end(); ++it) {
		(*it)->update();
	}
	//destroy the hitbox and pop it from the hitbox list
	UpdateHitboxes();
	RemoveHitbox();

	if (doStep)
		world->Step(1.0 / app_->getFrameRate(), 8, 3); //update box2d
}

// Updates every hitbox
// Checks hitbox overlaps with the main hurtbox and 
// if they overlap, it does both objects onHits
void GameState::UpdateHitboxes()
{
	for (unsigned int i = 0; i < 2; i++) {
		for (auto it = hitboxGroups_[i].begin(); it != hitboxGroups_[i].end(); ++it) {
			HitboxData* hB = static_cast<HitboxData*>((*it)->GetUserData());

			hB->update();

			if(!hB->destroy_){	// if the hitbox doesnt "die", it checks overlaps with the main hitboxes
				
				for (b2Fixture* mainHB : mainHurtboxes) {
					//checks overlaps considering masks
					if (!hB->destroy_ && (mainHB->GetFilterData().maskBits & (*it)->GetFilterData().categoryBits) != 0
						&& (mainHB->GetFilterData().categoryBits & (*it)->GetFilterData().maskBits) != 0
						&& b2TestOverlap((*it)->GetAABB(0), mainHB->GetAABB(0))) {
						//does both objects onHits if they hit each other
						UserData* objOnHit = static_cast<UserData*>(mainHB->GetUserData());
						objOnHit->onHit(*it);
						hB->onHit(mainHB);
					}
				}
			}
		}
	}
}

// Adds a hitbox relative to a body parameter
// pos is the positon of the hitbox relative to the body
// width and height of the hitbox
// time is the lifetime of the hitbox
// damage, hitstun and knockback(as meters)
// id is the player ID
// cBits are the same as the player, and mBits are the same except it excludes boundaries and walls to avoid bugs /*CAMBIAR CON CLASE BASE*/
// guardBreaker indicates if the hitbox is a GuardBreaker
void GameState::addHitbox(Vector2D pos, int width, int height, int time, int damage, int hitstun, Vector2D knockBack, b2Body* body, uint16 id, Entity* e, uint16 cBits, uint16 mBits, bool guardBreaker)
{
	b2PolygonShape shape;
	shape.SetAsBox(width * app_->METERS_PER_PIXEL / 2, height * app_->METERS_PER_PIXEL / 2, { float32((pos.getX() + width / 2) * app_->METERS_PER_PIXEL),float32((pos.getY() + height / 2) * app_->METERS_PER_PIXEL) }, 0);
	b2FixtureDef fixturedef;
	fixturedef.shape = &shape;
	fixturedef.density = 0.0f;			
	fixturedef.isSensor = true;
	fixturedef.filter.categoryBits = cBits;
	fixturedef.filter.maskBits = mBits & (PLAYER_1 | PLAYER_2 | P_BAG); //kk
	HitboxData* hData = new HitboxData(damage, time, hitstun, knockBack * app_->METERS_PER_PIXEL, guardBreaker, id, e);
	fixturedef.userData = hData;

	hitboxGroups_[id].push_back(body->CreateFixture(&fixturedef));
	hData->setIt(--hitboxGroups_[id].end());
}

// Adds a hitbox with its data
void GameState::addHitbox( uint16 id, HitboxData* hitbox, b2Fixture* fixture)
{
	hitbox->proyectile_ = true;
	HitboxData* hData = hitbox;
	hitboxGroups_[id].push_back(fixture);
	hData->setIt(--hitboxGroups_[id].end());
	hitboxGroups_[id].back()->SetUserData(hitbox);//saving hitbox's data
}

// Destroy every hitbox that has to be destroyed
void GameState::RemoveHitbox()
{
	for (auto hb_it = hitboxRemove_pair_.begin(); hb_it != hitboxRemove_pair_.end(); ++hb_it) {
		UserData* hitbox= static_cast<UserData*>((*(*hb_it).first)->GetUserData());
		delete hitbox;
		(*(*hb_it).first)->GetBody()->DestroyFixture((*(*hb_it).first));
		hitboxGroups_[(*hb_it).second].erase((*hb_it).first);
	}
	hitboxRemove_pair_.clear();
}

// Deleting all 
void GameState::clearHitboxes() {
	mainHurtboxes.clear();
	hitboxRemove_pair_.clear();
	for (int i = 0; i < 2; i++) {
		for (auto it = hitboxGroups_[i].begin(); it != hitboxGroups_[i].end(); ++it) {
			delete static_cast<HitboxData*>((*it)->GetUserData());
			(*it)->GetBody()->DestroyFixture(*it);
		}
		hitboxGroups_[i].clear();
	}
}



// Clears all the hitbox of a hitboxGroup   
// it is called when you interrupt an attack 
void GameState::resetGroup(int group) {

	for (auto it = hitboxGroups_[group].begin(); it != hitboxGroups_[group].end(); ++it) {
		HitboxData* hB = static_cast<HitboxData*>((*it)->GetUserData());
		if (!hB->destroy_ && !hB->proyectile_) {
			hitboxRemove_pair_.push_back(std::pair<std::list<b2Fixture*>::iterator, unsigned int>(it, group));
			hB->destroy_ = true;
		}
	}
}

// Puts a hitbox in the remove list
void GameState::killHitbox(std::list<b2Fixture*>::iterator it, unsigned int id) {
	hitboxRemove_pair_.push_back(std::pair<std::list<b2Fixture*>::iterator, unsigned int>(it, id));
}

void GameState::render()
{
	SDL_RenderClear(app_->getRenderer());

	for (auto it = entManager_.getScene().begin(); it != entManager_.getScene().end(); ++it) {
		(*it)->render();
	}
#if _DEBUG
	world->DrawDebugData();
#endif
	SDL_RenderPresent(app_->getRenderer());
}

void GameState::empty()
{
	for (auto it = entManager_.getScene().begin(); it != entManager_.getScene().end(); ++it) {
		delete* it;
		*it = nullptr;
	}
	entManager_.getScene().clear();
}

GameState::~GameState()
{
	empty();
	clearHitboxes();

	delete world;
	delete resJumpListener;
#if _DEBUG
	delete debugInstance;
#endif 
}
