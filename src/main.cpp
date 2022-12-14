#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <iostream>

struct {
  struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
  } Componenets;

  struct {
    SDL_DisplayMode mode;
  } Info;
} App;

static struct Colors {
  const SDL_Color BLACK = {0, 0, 0, 255};
  const SDL_Color BLUE = {44, 116, 168, 255};
  const SDL_Color RED = {210, 116, 44, 255};
} Colors;

typedef struct Pixel {
  Sint32 x = 0;
  Sint32 y = 0;
};

uint16_t halfw;
uint16_t halfh;

/// @brief cleanup render and window objects
void Cleanup() {
  SDL_DestroyRenderer(App.Componenets.renderer);
  App.Componenets.renderer = nullptr;
  SDL_DestroyWindow(App.Componenets.window);
  App.Componenets.window = nullptr;
  SDL_Quit();
}

/// @brief fill rect in the renderer. with offset
/// @param x position
/// @param y position
/// @param pixsize width and height
void FillPixel(size_t x, size_t y, SDL_Color color) {
  SDL_Rect _rect;
  _rect.x = halfw + x;
  _rect.y = halfh - y;
  _rect.w = 1;
  _rect.h = 1;
  SDL_SetRenderDrawColor(App.Componenets.renderer, color.r, color.g, color.b,
                         color.a);
  SDL_RenderFillRect(App.Componenets.renderer, &_rect);
}

/// @brief draw pixel at giver position
/// @param x
/// @param y
/// @param color
void DrawPixel(Sint32 x, Sint32 y, SDL_Color color) {
  SDL_Rect _rect;
  _rect.x = x;
  _rect.y = y;
  _rect.w = 10;
  _rect.h = 10;
  SDL_SetRenderDrawColor(App.Componenets.renderer, color.r, color.g, color.b,
                         color.a);
  SDL_RenderFillRect(App.Componenets.renderer, &_rect);
}

int main(int argc, char *argv[]) {

  std::cout << "CDLR Graphics" << std::endl;

  SDL_Init(SDL_INIT_VIDEO)
      ? std::cout << "failed sdl2 init: " << SDL_GetError() << std::endl
      : std::cout << "sdl2 init success" << std::endl;

  SDL_GetDesktopDisplayMode(0, &App.Info.mode);

  halfw = App.Info.mode.w / 4;
  halfh = App.Info.mode.h / 4;

  App.Componenets.window = SDL_CreateWindow(
      "CDLR", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      App.Info.mode.w / 2, App.Info.mode.h / 2,
      SDL_WindowFlags::SDL_WINDOW_SHOWN | SDL_WindowFlags::SDL_WINDOW_OPENGL);

  if (App.Componenets.window == nullptr) {
    std::cout << "failed to create sdl2 window: " << SDL_GetError()
              << std::endl;
    SDL_Quit();
    return 1;
  }

  App.Componenets.renderer =
      SDL_CreateRenderer(App.Componenets.window, -1,
                         SDL_RendererFlags::SDL_RENDERER_ACCELERATED |
                             SDL_RendererFlags::SDL_RENDERER_PRESENTVSYNC);

  if (App.Componenets.renderer == nullptr) {
    std::cout << "failed sdl2 init: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_Event event;
  Pixel pix;

  for (;;) {
    SDL_SetRenderDrawColor(App.Componenets.renderer, Colors.BLACK.r,
                           Colors.BLACK.g, Colors.BLACK.b, Colors.BLACK.a);
    SDL_RenderClear(App.Componenets.renderer);

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
          pix.x = event.button.x;
          pix.y = event.button.y;
        }
      }
    }
#pragma endregion

    DrawPixel(pix.x, pix.y, Colors.BLUE);
    FillPixel(0, 0, Colors.RED);
    SDL_RenderPresent(App.Componenets.renderer);
  }

  return 0;
}
