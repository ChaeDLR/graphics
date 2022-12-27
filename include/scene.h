#pragma once
#include <SDL2/SDL.h>

#include <cstdint>

struct {
  struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
  } Componenets;

  struct {
    SDL_DisplayMode mode;
  } Info;
} App;

class Scene {
 public:
  struct Camera {
    int16_t x = 0;
    int16_t y = 0;
    int16_t z = 0;
  } camera;

  struct Canvas {
    int16_t x = 0;
    int16_t y = 0;
    int16_t w;
    int16_t h;
    int16_t halfw;
    int16_t halfh;
  } canvas;

  struct Viewport {
    // size and distance determine the angle
    // visible through the camera @1 -> 53˙
    // FOV
    // 2d plane embedded in 3d space at distance d
    int16_t w = 1;
    int16_t h = 1;
    int16_t d = 1;
  } viewport;

  /// @brief convert default SDL2 axis to
  /// the standards axis with origin
  /// at the center of the screen
  /// @param x
  /// @param y
  inline void ConvertAxis(int &x, int &y) {
    x += this->canvas.halfw;
    y = this->canvas.halfh - y;
  }

  /// @brief convert canvas coords to viewport coords
  /// for each pixel on the canvas determine its
  /// corresponging point on the viewport
  /// @param x
  /// @param y
  inline void CanvasToViewport(int x, int y) {
    x *= (this->viewport.w / this->canvas.w);
    y *= (this->viewport.h / this->canvas.h);
  }

  SDL_Point RayPoint(int t, int vx, int vy) {
    SDL_Point p{camera.x + t * (vx - this->camera.x),
                camera.y + t * (vy - this->camera.y)};
    return p;
  }
};