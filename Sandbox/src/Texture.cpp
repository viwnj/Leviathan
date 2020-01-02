#include "Texture.h"


SDL_Texture* Texture::LoadTexture(const char* fileName) {
  SDL_RWops* io = SDL_RWFromFile(fileName, "r");
  SDL_Surface* surface = IMG_Load(fileName);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer::renderer, surface);
  SDL_FreeSurface(surface);
  std::cout << fileName  << " is PNG " << IMG_isPNG(io) << std::endl;

  return texture;

}

void Texture::Draw(
  SDL_Texture* texture, 
  SDL_Rect sourceRect, 
  SDL_Rect destRect, 
  SDL_RendererFlip flip
) {

  SDL_RenderCopyEx(Renderer::renderer, texture, &sourceRect, &destRect, 0.0, NULL, flip);
 
}