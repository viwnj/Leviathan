#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class Application
{

public:
	int ticksLastFrame;
	Application();
	SDL_Window* win;
	SDL_Renderer* renderer;
	bool isActive = false;
	float GetDeltaTime();
	void Destroy();
};