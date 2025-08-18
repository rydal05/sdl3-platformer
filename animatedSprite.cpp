#include "animatedSprite.h"
#include "game.h"


AnimatedSprite::AnimatedSprite(const std::string& file_path,
	int source_x, int source_y, int width, int height,
	SDL_Renderer* renderer, int fps, int num_frames
) : Sprite(file_path, source_x, source_y, width, height, renderer),
m_frameTime(1000 / fps), m_numFrames(num_frames),
m_currentFrame(0), m_elapsedTime(0){

}

void AnimatedSprite::update(int elapsed_time_ms){
	m_elapsedTime += elapsed_time_ms;
	if(m_elapsedTime > m_frameTime){
		++m_currentFrame;
		m_elapsedTime = 0;
		if(m_currentFrame < m_numFrames){
			m_sourceFRect->x += Game::kTileSize;
		}
		else{
			m_sourceFRect->x -= Game::kTileSize * (m_numFrames - 1);
			m_currentFrame = 0;
		}
	}
}