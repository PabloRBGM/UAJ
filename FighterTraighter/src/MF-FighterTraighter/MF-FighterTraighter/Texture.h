#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Vector2D.h"
#include <iostream>

using namespace std;

class Texture {
protected:
	SDL_Texture* texture = nullptr;
	SDL_Renderer* renderer = nullptr;

	int width = 0;
	int height = 0;

	int fWidth = 0;
	int fHeight = 0;

	int nCols = 0;
	int nRows = 0;

public:
	Texture(SDL_Renderer* rend) : renderer(rend) {};
	Texture(SDL_Renderer* rend, string fileName, int cols, int fils) : renderer(rend) {
		load(fileName, cols, fils);
	};
	Texture(Texture& tex) = delete; // No copy constructor
	Texture operator=(Texture& tex) = delete; // No assignment operator
	~Texture() { cleanTexture(); };

	inline int getWidth() { return width; }
	inline int getHeight() { return height; }

	inline int getCols() { return nCols; }
	inline int getRows() { return nRows; }

	void load(string filename, int cols, int fils);
	void setColor(SDL_Color col);
	void cleanTexture();
	void render(const SDL_Rect& rect, SDL_RendererFlip flip = SDL_FLIP_NONE) const; 
	void render(Vector2D pos, int widthMul, int heightMult, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	void render(const SDL_Rect& destRect, int row, int col, int angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	void render(const SDL_Rect& srcRect, const SDL_Rect& destRect, int angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
};