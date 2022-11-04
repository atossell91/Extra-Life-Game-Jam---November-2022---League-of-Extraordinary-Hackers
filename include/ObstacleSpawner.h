//  Copyright 2022 Anthony Tossell
#ifndef INCLUDE_BLOCKSPAWNER_H_
#define INCLUDE_BLOCKSPAWNER_H_

#include <SDL2/SDL.h>
#include <vector>

#include "Obstacle.h"
#include "IOverlappable.h"
#include "IDrawable.h"
#include "RandomNumGenerator.h"

class ObstacleSpawner {
 private:
    std::vector<IDrawable*>* drawables;
    std::vector<IOverlappable*>* phsyicals;
    std::vector<IOverlappable*>* nonPhysicals;
    RandomNumGenerator rGen;
    
 public:
   ObstacleSpawner(std::vector<IOverlappable*>* physicals,
   std::vector<IOverlappable*>* nonPysicals,
   std::vector<IDrawable*>* drawables);
   bool isCollision(IOverlappable* o);
    Obstacle* spawnObstacle(int xMin, int xMax, int yMin, int yMax);
};

#endif  // INCLUDE_BLOCKSPAWNER_H_
