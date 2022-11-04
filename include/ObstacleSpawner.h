//  Copyright 2022 Anthony Tossell
#ifndef INCLUDE_BLOCKSPAWNER_H_
#define INCLUDE_BLOCKSPAWNER_H_

#include <SDL2/SDL.h>
#include <vector>

#include "Obstacle.h"
#include "IOverlappable.h"
#include "IDrawable.h"

class ObstacleSpawner {
 private:
    std::vector<IDrawable*> drawables;
    std::vector<IOverlappable*> phsyicals;
    std::vector<IOverlappable*> nonPhysicals;
 public:
    void spawnObstacle();
};

#endif  // INCLUDE_BLOCKSPAWNER_H_
