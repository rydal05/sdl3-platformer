#include "graphics.h"

namespace{
	const int kScreenWidth = 640;
	const int kScreenHeight = 480;
	const int kBitsPerPixel = 32;
}

Graphics::Graphics(){
	SDL_CreateWindowAndRenderer("GameWin", kScreenWidth, kScreenHeight, NULL, &m_window, &m_renderer);
}

Graphics::~Graphics(){
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
}

void Graphics::blitSurface(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect source_rectangle, SDL_Rect destination_rectangle){
	destination_rectangle.x = 300;
	destination_rectangle.y = 300;
	source_rectangle.x = 0;
	source_rectangle.y = 0;
	source_rectangle.w = 16;
	source_rectangle.h = 16;

	SDL_RenderTexture(renderer, texture, (const SDL_FRect*)&source_rectangle, (const SDL_FRect*)&destination_rectangle);
}
