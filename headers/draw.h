#pragma once
#include <SDL2/SDL.h>

typedef struct Pixel {
  Sint32 x;
  Sint32 y;
};

struct Colors {
  const SDL_Color BLACK = {0, 0, 0, 255};
  const SDL_Color WHITE = {225, 225, 225, 255};
  const SDL_Color BLUE = {44, 116, 168, 255};
  const SDL_Color RED = {210, 116, 44, 255};
} colors;

void pixel(Sint32 x, Sint32 y, SDL_Color color, SDL_Renderer *renderer);