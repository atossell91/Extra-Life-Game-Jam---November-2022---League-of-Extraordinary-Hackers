//  Copyright 2022 Anthony Tossell
#include "../include/ObstacleSpawner.h"
#include "../include/Obstacle.h"

#include <iostream>


ObstacleSpawner::ObstacleSpawner(std::vector<IOverlappable*>* physicals,
std::vector<IOverlappable*>* nonPhysicals,
std::vector<IDrawable*>* drawables,
RandomNumGenerator* rg) {
    this->phsyicals = physicals;
    this->nonPhysicals = nonPhysicals;
    this->drawables = drawables;
    this->rGen = rg;
}

bool ObstacleSpawner::isCollision(IOverlappable* o) {
    for (auto p : *phsyicals) {
        if (o->isOverlap(*p, false)) {
            return true;
        }
    }
    return false;
}

Obstacle* ObstacleSpawner::spawnObstacle(int xMin, int xMax, int yMin, int yMax) {
    bool overlap = true;
    int count = 0;
    int maxTries = 10;
    GameRectangle r;
    r.setWidth(Obstacle::WIDTH);
    r.setHeight(Obstacle::HEIGHT);
    int x =0;
    int y =0;
    do {
        x = rGen->generate(xMin, xMax);
        y = rGen->generate(yMin, yMax);
        r.setX(x);
        r.setY(y);
        ++count;
    } while (isCollision(&r) && count < maxTries);

    if (count == maxTries) {
        return NULL;
    }
    else {
        Obstacle* optr = new Obstacle(phsyicals, nonPhysicals);
        optr->setX(x);
        optr->setY(y);
        drawables->push_back(optr);
        return optr;
    }
}
