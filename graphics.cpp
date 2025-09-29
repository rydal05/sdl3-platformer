#include "graphics.h"
#include <iostream>

#include "SDL3_image/SDL_image.h"

namespace{
	const int kScreenWidth = 640;
	const int kScreenHeight = 480;
	const int kBitsPerPixel = 32;
}

Graphics::Graphics(){
	SDL_CreateWindowAndRenderer("GameWin", kScreenWidth, kScreenHeight, NULL, &m_window, &m_renderer); 
}

Graphics::~Graphics(){
	for(TextureMap::iterator iter = texture_storage_.begin();
		iter != texture_storage_.end();
		++iter){
		SDL_DestroyTexture(iter->second);
	}


	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
}

TextureID Graphics::loadTexture(const std::string& file_path){
	//if we havent loaded in the sprite sheet
	if(texture_storage_.count(file_path) == 0){
		//loads it in here now
		m_tempSurface = IMG_Load(file_path.c_str());

		texture_storage_[file_path] = SDL_CreateTextureFromSurface(m_renderer, m_tempSurface);
	}
	return texture_storage_[file_path];
}