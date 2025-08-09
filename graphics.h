#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <SDL3/SDL.h>

struct Graphics {
	Graphics();
	~Graphics();
	
	void blitSurface(SDL_FRect* destination_rectangle){
		SDL_RenderRect(m_renderer, destination_rectangle);
	}

	private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
};


#endif