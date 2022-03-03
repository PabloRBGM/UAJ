#pragma once
#include "Box2D/Box2D.h"
#include "SDL.h"
#include <iostream>

//clase para debuggear las hitbox con SDL, tiene que heredar de b2Draw
//para ver las fisicas tal y como las hace b2D
class SDLDebugDraw : public b2Draw
{
public:
	SDLDebugDraw(SDL_Renderer* r, float scale_factor) :  b2Draw(), renderer(r), scale_factor_(scale_factor) {}
	//draws debug polygons with the e_aabbBit flag
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
	//draws debug polygons with the e_shapeBit flag
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)override;
	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)override {}
	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {}
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)override {}
	void DrawTransform(const b2Transform& xf)override {}
private:
	SDL_Renderer* renderer;
	float scale_factor_ = 1;
};

