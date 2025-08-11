#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <SDL3/SDL.h>

struct Graphics{
	public:
	Graphics();
	~Graphics();

	SDL_Renderer* getRenderer(){
		return m_renderer;
	}

	void blitSurface(SDL_Renderer* renderer, SDL_Texture* texture,SDL_Rect* source_rectangle, SDL_Rect* destination_rectangle);

	private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
};


#endif