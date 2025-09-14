#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "sprite.h"
#include "game.h"

struct AnimatedSprite: public Sprite{
	AnimatedSprite(Graphics& graphics, const std::string& file_path,
		int source_x, int source_y,
		int width, int height,
		SDL_Renderer* renderer,
		int fps, int num_frames
	);

	void update(int elapsed_time_ms);

	private:
	const int m_frameTime;
	const int m_numFrames;
	int m_currentFrame;
	int m_elapsedTime;
};

#endif