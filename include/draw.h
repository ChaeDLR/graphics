#pragma once
#include <SDL2/SDL.h>

struct Pixel {
  Sint32 x;
  Sint32 y;
  SDL_Color color;
};

void DrawPixel(Sint32 x, Sint32 y, SDL_Color color, SDL_Renderer *renderer);