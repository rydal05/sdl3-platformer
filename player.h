#ifndef PLAYER_H_
#define PLAYER_H_

#include <boost/scoped_ptr.hpp>

struct Sprite;
struct Graphics;


struct Player{
	Player(int x, int y);
	void update(int elapsed_time_ms);
	void draw(Graphics& graphics);

	private:
	int x_, y_;
	boost::scoped_ptr<Sprite> sprite_;
};

#endif
