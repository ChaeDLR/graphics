#include <SDL2/SDL.h>

void ChangeIntensity(SDL_Color& color, int intensity) {
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

/// @brief add two SDL_Colors
/// @param _color1
/// @param _color2
/// @return new SDL_Color with (r+r,g+g,b+b,a+a) values
SDL_Color AddColors(SDL_Color _color1, SDL_Color _color2) {
  SDL_Color newColor;
  Uint16 tempColor;

  Uint8* newColorLoc = &newColor.a;
  Uint8* structOneStart = &_color1.a;
  Uint8* structTwoStart = &_color2.a;

  for (int i = 0; i <= 3; i++) {
    tempColor = *(structOneStart - i) + *(structTwoStart - i);

    if (tempColor > 255) {
      *newColorLoc = 255;
    } else {
      *newColorLoc = tempColor;
    }
    newColorLoc -= 1;
  }

  return newColor;
}
