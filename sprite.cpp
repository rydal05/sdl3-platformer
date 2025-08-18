#include "sprite.h"

Sprite::Sprite(const std::string& file_path, int x, int y, int width, int height, SDL_Renderer* renderer){
	m_sourceFRect = new SDL_FRect{
		(float)x,
		(float)y,
		(float)width,
		(float)height
	};
	m_renderer = renderer;
	m_spritesheet = SDL_LoadBMP(file_path.c_str());
	
	m_texture = SDL_CreateTextureFromSurface(renderer, m_spritesheet);
	SDL_DestroySurface(m_spritesheet);
}

Sprite::~Sprite(){
	SDL_DestroyTexture(m_texture);
}

void Sprite::draw(Graphics& graphics, int x, int y){
	m_destinationFRect = new SDL_FRect{(float)x,(float)y,m_sourceFRect->w,m_sourceFRect->h};

	graphics.blitSurface(m_renderer,m_texture,m_sourceFRect, m_destinationFRect);
}