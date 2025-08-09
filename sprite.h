#ifndef SPRITE_H_
#define SPRITE_H_

#include <SDL3/SDL.h>
#include <string>

#include "graphics.h"

struct Sprite{
	Sprite(const std::string& file_path, int source_x, int source_y, int width, int height,SDL_Renderer* renderer);
	~Sprite();

	void draw(Graphics& graphics, int x, int y);
	
	private:
	SDL_Surface* m_spritesheet;
	SDL_Texture* m_texture;
	SDL_Rect m_source_rect;
	SDL_Rect m_destination_rect;
	SDL_Renderer* m_renderer;
	
};

#endif