//  Copyright 2022 Anthony Tossell
#ifndef INCLUDE_OBSTACLE_H_
#define INCLUDE_OBSTACLE_H_

#include <SDL2/SDL.h>

#include "GameRectangle.h"
#include "IDrawable.h"

class Obstacle : public IDrawable {
 private:
    const int BLOCK_WIDTH = 81;
    const int BLOCK_HEIGHT = 46;
    const int MARGIN = 3;
    GameRectangle* block;
    GameRectangle* area;

    std::vector<IOverlappable*>* physicals;
    std::vector<IOverlappable*>* nonPhysicals;
 public:
    void setX(int x);
    void setY(int Y);
    void addFunc(std::function<void (GameRectangle*)> func);
    Obstacle(std::vector<IOverlappable*>* phys,
    std::vector<IOverlappable*>* nonPhys);
    void removeAll();

    void draw(SDL_Surface* surface);
};

#endif  // INCLUDE_OBSTACLE_H_
