#ifndef GAME_H_
#define GAME_H_

#include <SDL3/SDL.h>
#include <boost/scoped_ptr.hpp>

#include "graphics.h"
#include "sprite.h"

struct Game{
	public:
	Game();
	~Game();

	private:
	void eventLoop();
	void update();
	void draw(Graphics &graphics);

	SDL_Renderer* m_renderer;
	boost::scoped_ptr<Sprite> sprite_;
};

#endif 