#include <stdio.h>
#include <SDL3/SDL.h>

#include "game.h"
#include "graphics.h"
#include "player.h"
#include "input.h"

namespace{
	const int kFps = 60;
}

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
	player_.reset(new Player(320, 240, m_renderer, graphics));


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

		//player horizontal movement
		if(input.isKeyHeld(SDLK_LEFT) && input.isKeyHeld(SDLK_RIGHT)){
			player_->stopMoving();
		}
		else if(input.isKeyHeld(SDLK_LEFT)){
			player_->startMovingLeft();
		}
		else if(input.isKeyHeld(SDLK_RIGHT)){
			player_->startMovingRight();
		}
		else{
			player_->stopMoving();
		}

		if(input.isKeyHeld(SDLK_UP) && input.isKeyHeld(SDLK_DOWN)){
			player_->lookHorizontal();
		}
		else if(input.isKeyHeld(SDLK_UP)){
			player_->lookUp();
		}
		else if(input.isKeyHeld(SDLK_DOWN)){
			player_->lookDown();
		}
		else{
			player_->lookHorizontal();
		}

		//player jump
		if(input.wasKeyPressed(SDLK_Z)){
			player_->startJump();
		}
		else if(input.wasKeyReleased(SDLK_Z)){
			player_->stopJump();
		}

		//	ensure this loop lasts 1/60th of a second / runs 1000/60ths of a ms

		const int current_time_ms = SDL_GetTicks();
		update(current_time_ms - last_update_time);
		last_update_time = current_time_ms;

		draw(graphics);
		SDL_RenderPresent(m_renderer);

		const int ms_per_frame = 1000 / kFps;
		const int elapsed_time_ms = SDL_GetTicks() - start_time_ms;
		if(elapsed_time_ms < ms_per_frame){
			SDL_Delay(ms_per_frame - elapsed_time_ms);
		}
		const float seconds_per_frame = (SDL_GetTicks() - start_time_ms) / 1000.0;
		const float fps = 1 / (seconds_per_frame);
		//printf("fps=%f\n", fps);

	}
	//while running ~ 60hz
	//	handle inputs. handle timer callbacks.
	//	update(). handle player movement projectiles collisions etc etc
	//	draw(). draw everything all at once
}

void Game::update(int elapsed_time_ms){
	player_->update(elapsed_time_ms);
}

void Game::draw(Graphics& graphics){
	SDL_RenderClear(m_renderer);
	SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
	player_->draw(graphics);

	//graphics.flip();
}

