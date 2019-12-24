#include "Texture.h"


SDL_Texture* Texture::LoadTexture(const char* fileName, SDL_Renderer* renderer) {
  SDL_RWops* io = SDL_RWFromFile(fileName, "r");
  SDL_Surface* surface = IMG_Load(fileName);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  std::cout << IMG_isPNG(io) << std::endl;

  return texture;

}

void Texture::Draw(
  SDL_Renderer* renderer, 
  SDL_Texture* texture, 
  SDL_Rect sourceRect, 
  SDL_Rect destRect, 
  SDL_RendererFlip flip
) {

  SDL_RenderCopyEx(renderer, texture, &sourceRect, &destRect, 0.0, NULL, flip);
 
}