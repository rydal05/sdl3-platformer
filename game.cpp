

#include "game.h"
#include "graphics.h"
#include <stdio.h>



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

	bool running = true;
	while(running){
		Uint32 start_time_ms = SDL_GetTicks();
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_EVENT_QUIT:
					running = false;
					break;
				case SDL_EVENT_KEY_DOWN:
					if(event.key.type == SDLK_ESCAPE){
						running = false;
					}
					break;
				default: break;
			}
		}
		//	ensure this loop lasts 1/60th of a second / runs 1000/60ths of a ms
		update();
		draw();

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

void Game::update(){

}

void Game::draw(){

}