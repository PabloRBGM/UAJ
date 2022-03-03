#pragma once
#include "Component.h"
#include "Texture.h"
//#include "Transform.h"
#include "PhysicsTransform.h"

#include "Entity.h"

class RenderImage : public Component
{
public:
	//constructor
	RenderImage(Texture* tex) : Component(ecs::RenderImage), texture_(tex) { };
	RenderImage(Texture* tex, SDL_Color col) : Component(ecs::RenderImage), texture_(tex), color_(col) { };
	inline void setFrame(size_t x, size_t y) { curX = x; curY = y; }
	//destructor
	~RenderImage();

	inline void setTexture(Texture* tex) { texture_ = tex; }
	inline void setColor(SDL_Color col) { color_ = col; }
	void init() override;
	//method overrided from Component
	virtual void render() override;
	inline void setRendered(bool r) { rendered = r; }
	inline bool getRendered() { return rendered; }
private:
	size_t curX = 0, curY = 0;
	Transform* transform_ = nullptr;
	Texture* texture_ = nullptr;
	SDL_Color color_ = { 255, 255, 255, 255 };
	bool rendered = true;
};

