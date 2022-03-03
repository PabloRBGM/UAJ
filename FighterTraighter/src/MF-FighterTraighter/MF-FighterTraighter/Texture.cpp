#include "Texture.h"
#include <assert.h>
#include "AssetsExceptions.h"

void Texture::cleanTexture() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture); // delete current texture
		texture = nullptr;
		width = 0;
		height = 0;
	}
}

void Texture::load(string filename, int cols, int rows) {
	SDL_Surface* tempSurface;
	tempSurface = IMG_Load(filename.c_str());
	if (tempSurface == nullptr)
		throw AssetsExceptions::TextureException("Unable to load texture: ", filename);
	else {
		cleanTexture();
		texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		//assert(texture == nullptr); // For debugging

		nCols = cols;
		nRows = rows;
		width = tempSurface->w;
		height = tempSurface->h;
		fWidth = width / cols;
		fHeight = height / rows;

		SDL_FreeSurface(tempSurface);
	}
}

void Texture::setColor(SDL_Color col)
{
	SDL_SetTextureColorMod(texture, col.r, col.g, col.b);
	SDL_SetTextureAlphaMod(texture, col.a);
}

// Render whole image, or first frame
void Texture::render(const SDL_Rect& destRect, SDL_RendererFlip flip) const{
	render(destRect, 0, 0, 0, flip);
}

void Texture::render(Vector2D pos, int widthMul, int heightMult, SDL_RendererFlip flip) const
{
	SDL_Rect rect = { pos.getX(), pos.getY(), width * widthMul, height *  heightMult };
	render(rect, 0, 0, 0, flip);
}

// Render only a frame, or at an angle
void Texture::render(const SDL_Rect& destRect, int row, int col, int angle, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = fWidth * col; srcRect.y = fHeight * row;
	srcRect.w = fWidth; srcRect.h = fHeight;
	render(srcRect, destRect, angle, flip);
}

// Render whatever rectangle of the texture
void Texture::render(const SDL_Rect& srcRect, const SDL_Rect& destRect, int angle, SDL_RendererFlip flip) const
{
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, 0, flip);
}
