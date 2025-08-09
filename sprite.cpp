#include "sprite.h"

Sprite::Sprite(const std::string& file_path, int source_x, int source_y, int width, int height){
	sprite_sheet_ = SDL_LoadBMP(file_path.c_str());
}

Sprite::~Sprite(){
	SDL_DestroySurface(sprite_sheet_);
}