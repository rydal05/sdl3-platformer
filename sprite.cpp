#include "sprite.h"

Sprite::Sprite(const std::string& file_path, int x, int y, int width, int height, SDL_Renderer* renderer){
	m_renderer = renderer;
	m_spritesheet = SDL_CreateSurface(width, height, SDL_PIXELFORMAT_UNKNOWN);
	m_spritesheet = SDL_LoadBMP(file_path.c_str());
	m_source_rect.x = x;
	m_source_rect.y = y;
	m_source_rect.w = width;
	m_source_rect.w = height;
	m_texture = SDL_CreateTextureFromSurface(renderer, m_spritesheet);
	SDL_DestroySurface(m_spritesheet);
}

Sprite::~Sprite(){
	SDL_DestroyTexture(m_texture);
}

void Sprite::draw(Graphics& graphics, int x, int y){
	m_destination_rect.x = x;
	m_destination_rect.y = y;
	m_destination_rect.w = NULL;
	m_destination_rect.h = NULL;
	
	graphics.blitSurface(m_renderer,m_texture,m_source_rect, m_destination_rect);
}