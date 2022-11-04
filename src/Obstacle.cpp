//  Copyright 2022 Anthony Tossell
#include "../include/Obstacle.h"
#include "../include/VecRemover.h"

#include <SDL2/SDL.h>

Obstacle::Obstacle(std::vector<IOverlappable*>* phys,
std::vector<IOverlappable*>* nonPhys) {
    block = new GameRectangle();
    block->setWidth(BLOCK_WIDTH);
    block->setHeight(BLOCK_HEIGHT);
    block->loadSpriteFiles({
        "assets/block/block-small-0.bmp",
      "assets/block/block-small-1.bmp"
    });
    if (phys != NULL) {
        physicals = phys;
        phys->push_back(static_cast<IOverlappable*>(block));
    }

    area = new GameRectangle();
    area->setWidth(BLOCK_WIDTH + MARGIN*2);
    area->setHeight(BLOCK_HEIGHT + MARGIN*2);
    if (nonPhys != NULL) {
        nonPhysicals = nonPhys;
        nonPhys->push_back(static_cast<IOverlappable*>(area));
    }
}

void Obstacle::draw(SDL_Surface* surface) {
    block->draw(surface);
}

void Obstacle::removeAll() {
    VecRemover::remove(*nonPhysicals, static_cast<IOverlappable*>(area));
    VecRemover::remove(*physicals, static_cast<IOverlappable*>(block));
}

void Obstacle::setX(int x) {
    block->setX(x);
    area->setX(x-MARGIN);
}
void Obstacle::setY(int y) {
    block->setY(y);
    area->setY(y-MARGIN);
}
void Obstacle::addFunc(std::function<void (GameRectangle*)> func) {
    area->addOverlapFunc(func);
}
