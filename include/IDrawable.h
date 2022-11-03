#ifndef INCLUDE_IDRAWABLE_H_
#define INCLUDE_IDRAWABLE_H_

#include <SDL.h>

class IDrawable {
 public:
    virtual void draw(SDL_Surface* surface) const = 0;
};

#endif  // INCLUDE_IDRAWABLE_H_