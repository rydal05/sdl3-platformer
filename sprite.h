#ifndef SPRITE_H_
#define SPRITE_H_

#include <SDL3/SDL.h>
#include <string>

#include "graphics.h"

struct Sprite{
	public:
	Sprite(const std::string& file_path, int source_x, int source_y, int width, int height,SDL_Renderer* renderer);
	virtual ~Sprite();

	virtual void update(int/*elapsed_time_ms*/){}
	void draw(Graphics& graphics, int x, int y);
	
	protected:
	SDL_FRect* m_sourceFRect;

	private:
	SDL_Surface* m_spritesheet;
	SDL_Texture* m_texture;
	SDL_FRect* m_destinationFRect;
	SDL_Renderer* m_renderer;
	
};

#endif