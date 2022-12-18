#pragma once
#include <SDL2/SDL.h>

struct Colors {
  SDL_Color BLACK = {0, 0, 0, 255};
  SDL_Color WHITE = {225, 225, 225, 255};
  SDL_Color BLUE = {44, 116, 168, 255};
  SDL_Color RED = {210, 116, 44, 255};
} colors;

void ChangeIntensity(SDL_Color &color, int intensity);

SDL_Color AddColors(SDL_Color _color1, SDL_Color _color2);