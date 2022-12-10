#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <iostream>

struct {
  const uint16_t WIDTH = 640;
  const uint16_t HEIGHT = 480;
} ScreenSettings;

struct {
  SDL_Window *mainWindow;
  SDL_Renderer *renderer;
} AppComps;

struct Colors {
  const SDL_Color BLACK = {0, 0, 0, 255};
  const SDL_Color BLUE = {22, 58, 84, 255};
} Colors;

typedef struct Square {
  size_t size = 10;
  size_t x = 0;
  size_t y = 0;
};

/// @brief cleanup render and window objects
void Cleanup() {
  SDL_DestroyRenderer(AppComps.renderer);
  AppComps.renderer = nullptr;
  SDL_DestroyWindow(AppComps.mainWindow);
  AppComps.mainWindow = nullptr;
  SDL_Quit();
}

/// @brief render a square to the screen
/// @param x position
/// @param y position
/// @param pixsize width and height
void PutSqr(size_t x, size_t y, size_t pixsize, SDL_Color color) {
  SDL_Rect _rect;
  _rect.x = x;
  _rect.y = y;
  _rect.w = pixsize;
  _rect.h = pixsize;

  SDL_SetRenderDrawColor(AppComps.renderer, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(AppComps.renderer, &_rect);
}

int main(int argc, char *argv[]) {

  std::cout << "CDLR Graphics" << std::endl;

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cout << "failed sdl2 init: " << SDL_GetError() << std::endl;
    return 1;
  } else {
    std::cout << "sdl2 init success" << std::endl;
  }

  AppComps.mainWindow = SDL_CreateWindow(
      "CDLR", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      ScreenSettings.WIDTH, ScreenSettings.HEIGHT,
      SDL_WindowFlags::SDL_WINDOW_SHOWN | SDL_WindowFlags::SDL_WINDOW_OPENGL);

  if (AppComps.mainWindow == nullptr) {
    std::cout << "failed to create sdl2 window: " << SDL_GetError()
              << std::endl;
    SDL_Quit();
    return 1;
  }

  AppComps.renderer =
      SDL_CreateRenderer(AppComps.mainWindow, -1,
                         SDL_RendererFlags::SDL_RENDERER_ACCELERATED |
                             SDL_RendererFlags::SDL_RENDERER_PRESENTVSYNC);

  if (AppComps.renderer == nullptr) {
    std::cout << "failed sdl2 init: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_Event event;
  Square pix;

  for (;;) {
    SDL_SetRenderDrawColor(AppComps.renderer, Colors.BLACK.r, Colors.BLACK.g,
                           Colors.BLACK.b, Colors.BLACK.a);
    SDL_RenderClear(AppComps.renderer);

#pragma region checkevents
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

      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == 1) {
          PutSqr(event.button.x, event.button.y, 10, Colors.BLUE);
          pix.x = event.button.x;
          pix.y = event.button.y;
        }
      }
    }
#pragma endregion

    PutSqr(pix.x, pix.y, pix.size, Colors.BLUE);
    SDL_RenderPresent(AppComps.renderer);
  }

  return 0;
}
