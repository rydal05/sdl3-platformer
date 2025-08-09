#ifndef SPRITE_H_
#define SPRITE_H_

#include <SDL3/SDL.h>
#include <string>

struct Sprite{
	Sprite(const std::string& file_path, int source_x, int source_y, int width, int height);
	~Sprite();
	private:
	SDL_Surface* sprite_sheet_;
};

#endif