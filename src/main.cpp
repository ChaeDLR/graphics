#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <colors.h>
#include <draw.h>
#include <scene.h>

#include <iostream>

uint16_t halfw;
uint16_t halfh;

Scene scene;
SDL_Event event;
Pixel pix;
Pixel pix2;

/// @brief cleanup render and window objects
void Cleanup() {
  SDL_DestroyRenderer(App.Componenets.renderer);
  App.Componenets.renderer = nullptr;
  SDL_DestroyWindow(App.Componenets.window);
  App.Componenets.window = nullptr;
  SDL_Quit();
}

int main(int argc, char *argv[]) {
  std::cout << "CDLR Graphics" << std::endl;

  std::atexit(&Cleanup);

#pragma region INIT
  SDL_Init(SDL_INIT_VIDEO)
      ? std::cout << "failed sdl2 init: " << SDL_GetError() << std::endl
      : std::cout << "sdl2 init success" << std::endl;

  SDL_GetDesktopDisplayMode(0, &App.Info.mode);

  scene.canvas.w = App.Info.mode.w / 2;
  scene.canvas.h = App.Info.mode.h / 2;

  halfw = App.Info.mode.w / 4;
  halfh = App.Info.mode.h / 4;

  App.Componenets.window = SDL_CreateWindow(
      "CDLR", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, scene.canvas.w,
      scene.canvas.h,
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
#pragma endregion

  SDL_Color newColor;
  pix = {0, 0, colors.RED};
  pix2 = {0, 0, colors.BLUE};
  scene.ConvertAxis(pix.x, pix.y);

  for (;;) {
    SDL_SetRenderDrawColor(App.Componenets.renderer, colors.BLACK.r,
                           colors.BLACK.g, colors.BLACK.b, colors.BLACK.a);
    SDL_RenderClear(App.Componenets.renderer);

#pragma region checkevents
    if (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_EventType::SDL_QUIT:
          std::exit(0);
          return 0;

        case SDL_KEYDOWN:
          if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
            std::exit(0);
            return 0;
          } else if (event.key.keysym.scancode == SDL_SCANCODE_C) {
            ChangeIntensity(pix.color, 2);
          }

        case SDL_MOUSEBUTTONDOWN:
          if (event.button.button == 1) {
            pix.x = event.button.x;
            pix.y = event.button.y;
          }
      }
    }
#pragma endregion

    newColor = AddColors(pix.color, pix2.color);
    SDL_Color originColor = SubColors(newColor, pix2.color);
    DrawPixel(pix.x, pix.y, pix.color, App.Componenets.renderer);
    SDL_RenderPresent(App.Componenets.renderer);
  }

  return 0;
}
