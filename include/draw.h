#pragma once
#include <SDL2/SDL.h>

#include <cinttypes>

struct Pixel {
  int x;
  int y;
  SDL_Color color;
};

void DrawPixel(Sint32 x, Sint32 y, SDL_Color color, SDL_Renderer *renderer);