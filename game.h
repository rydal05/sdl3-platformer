#ifndef GAME_H_
#define GAME_H_

#include <SDL3/SDL.h>
#include <boost/scoped_ptr.hpp>


#include "graphics.h"
#include "player.h"

struct Player;

struct Game{
	public:
	Game();
	~Game();

	static int kTileSize;

	private:
	void eventLoop();
	void update(int elapsed_time_ms);
	void draw(Graphics &graphics);

	SDL_Renderer* m_renderer;
	boost::scoped_ptr<Player> player_;
	boost::scoped_ptr<Player> player_2_;
};

#endif 