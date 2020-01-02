#include "Application.h"
#include "Renderer.h"
SDL_Event Application::event;
SDL_Renderer* Renderer::renderer;

Application::Application() {
  SDL_Init(SDL_INIT_EVERYTHING);              // Initialize SDL2
  IMG_Init(IMG_INIT_PNG);
  TTF_Init();
  // Initialize the Window
  win = SDL_CreateWindow(
    "Sandbox",
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
  Renderer::Init(win);
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
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
}
