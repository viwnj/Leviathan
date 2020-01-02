#ifndef LABEL_H
#define LABEL_H

#include <SDL.h>
#include "../Component.h"
#include "../Font.h"
#include "../Renderer.h"

class Label : public Component {
	private:
		SDL_Rect destRect;
		std::string text;
		std::string fontFamily;
		SDL_Color color;
		SDL_Texture* texture;
	public:
		Label(std::string fontId, std::string text, const SDL_Color& color, int x, int y ) {
			this->destRect.x = x;
			this->destRect.y = y;
			this->text = text;
			this->fontFamily = fontFamily;
			this->color = color;
			
			SetLabelText(AssetManager::GetFont(fontId), text);
		}

		void SetLabelText(TTF_Font* font, std::string text) {
			SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
			texture = SDL_CreateTextureFromSurface(Renderer::renderer, surface);
			SDL_FreeSurface(surface);
			SDL_QueryTexture(texture, NULL, NULL, &destRect.w, &destRect.h);
		}

		void Render(SDL_Renderer* renderer) override {
			Font::Draw(texture, destRect);
		}
};

#endif