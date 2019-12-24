#include "Applcation.h"

Application::Application() {
  SDL_Init(SDL_INIT_EVERYTHING);              // Initialize SDL2
  IMG_Init(IMG_INIT_PNG);
  // Initialize the Window
  win = SDL_CreateWindow(
    "LEVI",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    800,
    600,
    SDL_WINDOW_OPENGL
  );

  if (this->win == NULL) {
    // In the case that the window could not be made...
    throw SDL_GetError();
  }

  isActive = true;

  // Initialize the Renderer
  renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    throw "The renderer could not be created";
  }

}

float Application::GetDeltaTime() {
  float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

  // Clamp deltaTime to a maximum value
  deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

  // Sets the new ticks for the current frame to be used in the next pass
  ticksLastFrame = SDL_GetTicks();

  return deltaTime;
}

void Application::Destroy() {
  this->isActive = false;
  SDL_DestroyWindow(win);
  SDL_Quit();
  IMG_Quit();
}
