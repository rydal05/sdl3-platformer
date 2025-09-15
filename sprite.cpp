#include "sprite.h"

Sprite::Sprite(Graphics& graphics, const std::string& file_path, int x, int y, int width, int height, SDL_Renderer* renderer){
	m_sourceFRect = new SDL_FRect{
		(float)x,
		(float)y,
		(float)width,
		(float)height
	};
	m_renderer = renderer;
	m_texture = graphics.loadTexture(file_path);
	SDL_SetTextureScaleMode(m_texture, SDL_SCALEMODE_NEAREST);
}

Sprite::~Sprite(){
	SDL_DestroyTexture(m_texture);
}

void Sprite::draw(Graphics& graphics, int x, int y){
	m_destinationFRect = new SDL_FRect{(float)x,(float)y,m_sourceFRect->w,m_sourceFRect->h};

	SDL_RenderTexture(m_renderer, m_texture, m_sourceFRect, m_destinationFRect);
}

void Sprite::scaled_draw(Graphics& graphics, int x, int y, int scale){
	m_destinationFRect = new SDL_FRect{(float)x,(float)y,m_sourceFRect->w*scale,m_sourceFRect->h*scale};


	SDL_RenderTexture(m_renderer, m_texture, m_sourceFRect, m_destinationFRect);
}