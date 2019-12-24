#pragma once
#include "Core.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

namespace Leviathan {
	class LV_API Application
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

}

