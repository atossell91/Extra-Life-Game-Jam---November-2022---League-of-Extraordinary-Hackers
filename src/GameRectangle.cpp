#include <SDL.h>

#include "../include/GameRectangle.h"
#include <iostream>

void GameRectangle::draw(SDL_Surface* surface) const {
    SDL_Rect r;
    r.w = width;
    r.h = height;
    r.x = xPos;
    r.y = yPos;
    SDL_FillRect(surface, &r, SDL_MapRGB(surface->format, red, green, blue));
}

bool GameRectangle::isValidMove() const {
    if (physicals == NULL){
        return true;
    }
    for (auto object : *physicals) {
        if (object == this) {
            continue;
        }
        else if (isOverlap(*object, true)) {
            return false;
        }
    }
    return true;
}


void GameRectangle::moveX(const int amt) {
    xPos += amt;
    if (!isValidMove()) {
        xPos -= amt;
    }
}

void GameRectangle::moveY(const int amt) {
    yPos += amt;
    if (!isValidMove()) {
        yPos -= amt;
    }
}

void GameRectangle::setX(const int val) {
    xPos = val;
}

void GameRectangle::setY(const int val) {
    yPos = val;
}

void GameRectangle::setColour(const int r, const int g, const int b) {
    red = r;
    green = g;
    blue = b;
}

void GameRectangle::setPhysicalsList(std::vector<IOverlappable*>* list) {
    this->physicals = list;
}

void GameRectangle::setNonPhysicalsList(std::vector<IOverlappable*>* list) {
    this->nonPhysicals = list;
}

// Takes a point (x,y) and checks if it's inside the object
bool GameRectangle::isIntersect(const int x, const int y) const {
    return (x >= (xPos) && x <= (xPos + width)) &&
    (y >= (yPos) && y <= (yPos + height));
}

// Compares with another IOverlappable to see an overlap occurs
//  Uses isIntersect for each point
bool GameRectangle::isOverlap(const IOverlappable& other, bool reverseCheck) const {
    return other.isIntersect(xPos + OVERLAP_AMT, yPos + OVERLAP_AMT) ||
    other.isIntersect(xPos + width - OVERLAP_AMT, yPos + OVERLAP_AMT) ||
    other.isIntersect(xPos + width - OVERLAP_AMT, yPos + height - OVERLAP_AMT) ||
    other.isIntersect(xPos + OVERLAP_AMT, yPos + height - OVERLAP_AMT) ||
    (reverseCheck && other.isOverlap(*this, false));
}
