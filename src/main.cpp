#include <SDL2/SDL.h>
#include <iostream>

/// DLLS have 3 parts
// 1. The header files *.h
// 2. The library files *.lib || *.a
// 3. The binrary files *.dll || *.so

int height = 480;
int width = 640;

SDL_Window *mainWindow;
SDL_Renderer *renderer;
SDL_Event event;

namespace Colors {
const SDL_Color BLACK = {0, 0, 0, 255};
const SDL_Color BLUE = {11, 29, 42, 255};
} // namespace Colors

void Cleanup() {
  SDL_DestroyRenderer(renderer);
  renderer = nullptr;
  SDL_DestroyWindow(mainWindow);
  mainWindow = nullptr;
  SDL_Quit();
}

int main() {

  std::cout << "CDLR Graphics" << std::endl;

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cout << "failed sdl2 init: " << SDL_GetError() << std::endl;
    return 1;
  } else {
    std::cout << "sdl2 init success" << std::endl;
  }

  mainWindow = SDL_CreateWindow(
      "CDLR", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
      SDL_WindowFlags::SDL_WINDOW_SHOWN | SDL_WindowFlags::SDL_WINDOW_OPENGL);

  if (mainWindow == nullptr) {
    std::cout << "failed to create sdl2 window: " << SDL_GetError()
              << std::endl;
    SDL_Quit();
    return 1;
  }

  renderer =
      SDL_CreateRenderer(mainWindow, -1,
                         SDL_RendererFlags::SDL_RENDERER_ACCELERATED |
                             SDL_RendererFlags::SDL_RENDERER_PRESENTVSYNC);

  if (renderer == nullptr) {
    std::cout << "failed sdl2 init: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }
  // might be able to take out of loop
  SDL_SetRenderDrawColor(renderer, Colors::BLACK.r, Colors::BLACK.g,
                         Colors::BLACK.b, Colors::BLACK.a);

  // main loop
  for (;;) {
    // check events
    if (SDL_PollEvent(&event)) {
      switch (event.type) {

      case SDL_EventType::SDL_QUIT:
        Cleanup();
        return 0;

      case SDL_KEYDOWN:
        if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
          Cleanup();
          return 0;
        }
      }
    }

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
  }

  return 0;
}
