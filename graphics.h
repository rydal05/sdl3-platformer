#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <SDL3/SDL.h>
#include <map>
#include <string>

typedef SDL_Texture* TextureID;
typedef std::map<std::string, SDL_Texture*> TextureMap;

struct Graphics{

	Graphics();
	~Graphics();

	TextureID loadTexture(const std::string& file_path);

	SDL_Renderer* getRenderer(){
		return m_renderer;
	}

	void blitSurface(SDL_Renderer* renderer, TextureID texture, SDL_FRect* source_rectangle, SDL_FRect* destination_rectangle);

	private:
	TextureMap texture_storage_;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Surface* m_tempSurface;
};


#endif