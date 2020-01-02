#ifndef APPLICATION_H
#define APPLICATION_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Application
{

public:
	int ticksLastFrame;
	Application();
	SDL_Window* win;
	static SDL_Event event;
	bool isActive = false;
	float GetDeltaTime();
	void Destroy();
};

#endif