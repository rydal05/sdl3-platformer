#include "sprite.h"

Sprite::Sprite(const std::string& file_path, int x, int y, int width, int height, SDL_Renderer* renderer){
	m_source_rect = new SDL_Rect{x,y,width,height};
	m_renderer = renderer;
	m_spritesheet = SDL_LoadBMP(file_path.c_str());
	
	m_texture = SDL_CreateTextureFromSurface(renderer, m_spritesheet);
	SDL_DestroySurface(m_spritesheet);
}

Sprite::~Sprite(){
	SDL_DestroyTexture(m_texture);
}

void Sprite::draw(Graphics& graphics, int x, int y){
	m_destination_rect = new SDL_Rect{x,y,m_source_rect->w,m_source_rect->h};

	graphics.blitSurface(m_renderer,m_texture,m_source_rect, m_destination_rect);

	delete m_destination_rect;
}