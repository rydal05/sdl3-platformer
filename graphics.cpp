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


