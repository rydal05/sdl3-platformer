#include <stdio.h>
#include <SDL3/SDL.h>

#include "game.h"
#include "graphics.h"
#include "animatedSprite.h"
#include "input.h"

int Game::kTileSize = 32;

Game::Game(){
	SDL_Init(0);
	SDL_HideCursor();
	
	eventLoop();
}
Game::~Game(){
	SDL_Quit();
}

void Game::eventLoop(){
	Graphics graphics;
	SDL_Event event;
	Input input;

	m_renderer = graphics.getRenderer();
	sprite_.reset(new AnimatedSprite("C:\\Users\\maste\\Downloads\\MyChar.bmp",0,0,kTileSize,kTileSize, m_renderer,15,3));


	bool running = true;
	int last_update_time = SDL_GetTicks();
	while(running){
		const Uint32 start_time_ms = SDL_GetTicks();
		input.beginNewFrame();
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_EVENT_QUIT:
				{
					running = false;
					break;
				}
				case SDL_EVENT_KEY_DOWN:
				{
					input.keyDownEvent(event);
					break;
				}
				case SDL_EVENT_KEY_UP:
				{
					input.keyUpEvent(event);
					break;
				}
				default: { break; }
			}
		}

		if(input.wasKeyPressed(SDLK_ESCAPE)){
			running = false;
		}

		SDL_RenderClear(m_renderer);
		SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
		//	ensure this loop lasts 1/60th of a second / runs 1000/60ths of a ms
		
		const int current_time_ms = SDL_GetTicks();
		update(current_time_ms - last_update_time);
		last_update_time = current_time_ms;
		
		draw(graphics);
		SDL_RenderPresent(m_renderer);
		Uint32 elapsed_time_ms = SDL_GetTicks() - start_time_ms;
		if((1000 / 60) >= elapsed_time_ms){
			SDL_Delay(1000 / 60 - elapsed_time_ms);
		}
		const float seconds_per_frame = (SDL_GetTicks() - start_time_ms) / 1000.0;
		const float fps = 1 / (seconds_per_frame);
		printf("fps=%f\n", fps);
		
	}
	//while running ~ 60hz
	//	handle inputs. handle timer callbacks.
	//	update(). handle player movement projectiles collisions etc etc
	//	draw(). draw everything all at once
}

void Game::update(int elapsed_time_ms){
	sprite_->update(elapsed_time_ms);
}

void Game::draw(Graphics &graphics){
	sprite_->draw(graphics, 320, 240);
	
	//graphics.flip();
}

