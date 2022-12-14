#ifndef INCLUDE_IDRAWABLE_H_
#define INCLUDE_IDRAWABLE_H_

#include <SDL2/SDL.h>

class IDrawable {
 public:
  virtual void draw(SDL_Surface *surface) = 0;
};

#endif  // INCLUDE_IDRAWABLE_H_
