#ifndef INPUT_H_
#define INPUT_H_

#include <SDL3/SDL.h>
#include <map>

struct Input{
	void beginNewFrame();

	void keyDownEvent(const SDL_Event& event);
	void keyUpEvent(const SDL_Event& event);

	bool wasKeyPressed(SDL_Keycode key);
	bool wasKeyReleased(SDL_Keycode key);
	bool isKeyHeld(SDL_Keycode key);

	private:
	std::map<SDL_Keycode, bool> mHeldKeys;
	std::map<SDL_Keycode, bool> mPressedKeys;
	std::map<SDL_Keycode, bool> mReleasedKeys;
};

#endif