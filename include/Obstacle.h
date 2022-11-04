//  Copyright 2022 Anthony Tossell
#ifndef INCLUDE_OBSTACLE_H_
#define INCLUDE_OBSTACLE_H_

#include <SDL2/SDL.h>

#include "GameRectangle.h"
#include "IDrawable.h"
#include "IOverlappable.h"

class Obstacle : public IDrawable, public IOverlappable {
 private:
    static const int BLOCK_WIDTH = 81;
    static const int BLOCK_HEIGHT = 46;
    static const int MARGIN = 3;
    GameRectangle* block;
    GameRectangle* area;

    std::vector<IOverlappable*>* physicals;
    std::vector<IOverlappable*>* nonPhysicals;
 public:
    static const int WIDTH = BLOCK_WIDTH + MARGIN*2;
    static const int HEIGHT = BLOCK_HEIGHT + MARGIN*2;
    void setX(int x);
    void setY(int Y);
    void addFunc(std::function<void (GameRectangle*)> func);
    Obstacle(std::vector<IOverlappable*>* phys,
    std::vector<IOverlappable*>* nonPhys);
    void removeAll();

    void draw(SDL_Surface* surface);

   bool isOverlap(const IOverlappable& other, bool) const;
   bool isIntersect(const int x, const int y) const;
   void callOverlapFuncs() {}
};

#endif  // INCLUDE_OBSTACLE_H_
