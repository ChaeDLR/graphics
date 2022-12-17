#include <SDL2/SDL.h>

/// @brief draw pixel at given position
/// @param x
/// @param y
/// @param color
void pixel(Sint32 x, Sint32 y, SDL_Color color, SDL_Renderer *renderer) {
  SDL_Rect _rect;
  _rect.x = x;
  _rect.y = y;
  _rect.w = 10;
  _rect.h = 10;
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(renderer, &_rect);
}