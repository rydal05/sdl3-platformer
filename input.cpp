#include "input.h"

void Input::beginNewFrame(){
	mPressedKeys.clear();
	mReleasedKeys.clear();
}

void Input::keyDownEvent(const SDL_Event& event){
	mPressedKeys[event.key.key] = true;
	mHeldKeys[event.key.key] = true;
}
void Input::keyUpEvent(const SDL_Event& event){
	mReleasedKeys[event.key.key] = true;
	mHeldKeys[event.key.key] = false;
}

bool Input::wasKeyPressed(SDL_Keycode key){
	return mPressedKeys[key];
}
bool Input::wasKeyReleased(SDL_Keycode key){
	return mReleasedKeys[key];
}
bool Input::isKeyHeld(SDL_Keycode key){
	return mHeldKeys[key];
}