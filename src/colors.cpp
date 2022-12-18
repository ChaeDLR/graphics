#include <SDL2/SDL.h>

void ChangeIntensity(SDL_Color &color, int intensity) {
  int tempColor;

  tempColor = color.r * intensity;
  if ((tempColor / intensity) != color.r) {
    // clamp if overflow
    intensity >= 1 ? color.r = 255 : color.r = 0;
  } else {
    color.r *= intensity;
  }

  tempColor = color.g * intensity;
  if ((tempColor / intensity) != color.g) {
    intensity >= 1 ? color.g = 255 : color.g = 0;
  } else {
    color.g *= intensity;
  }

  tempColor = color.b * intensity;
  if ((tempColor / intensity) != color.b) {
    intensity >= 1 ? color.b = 255 : color.b = 0;
  } else {
    color.b *= intensity;
  }
};
