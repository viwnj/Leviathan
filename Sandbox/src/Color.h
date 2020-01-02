#pragma once
#include <SDL.h>

class Color {
	public:
		static SDL_Color rgba(unsigned int r, unsigned int g, unsigned  int b, unsigned  int a) {
			return SDL_Color{
				static_cast<Uint8>(r),
				static_cast<Uint8>(g),
				static_cast<Uint8>(b),
				static_cast<Uint8>(a),
			};
		}

		static SDL_Color rgb(unsigned int r, unsigned int g, unsigned  int b, unsigned  int a) {
			return SDL_Color{
				static_cast<Uint8>(r),
				static_cast<Uint8>(g),
				static_cast<Uint8>(b),
				255,
			};
		}
};
