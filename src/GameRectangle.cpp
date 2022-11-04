#include <SDL.h>

#include "../include/GameRectangle.h"
#include <iostream>

GameRectangle::~GameRectangle() {
    if (img_surface != NULL) {
        SDL_FreeSurface(img_surface);
        img_surface = NULL;
    }
}

void GameRectangle::draw(SDL_Surface* surface) {

    SDL_Rect r;
    r.w = width;
    r.h = height;
    r.x = xPos;
    r.y = yPos;

    if (sprites.size() < 1) {
        SDL_FillRect(surface, &r, SDL_MapRGB(surface->format, red, green, blue));
    }
    else {
        if (drawCounter >= 3) {
            drawCounter = 0;
            currentFrame = (currentFrame +1) % sprites.size();
        }
        SDL_BlitSurface(sprites[currentFrame], NULL, surface, &r);
    }
    ++drawCounter;
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

void GameRectangle::setWidth(int n) {
    width = n;
}

void GameRectangle::setHeight(int n) {
    height = n;
}

void GameRectangle::moveX(const int amt) {
    xPos += amt;
    if (!isValidMove()) {
        xPos -= amt;
    }
    SDL_PushEvent(&OverlapEvent);
}

void GameRectangle::moveY(const int amt) {
    yPos += amt;
    if (!isValidMove()) {
        yPos -= amt;
    }
    SDL_PushEvent(&OverlapEvent);
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

void GameRectangle::loadImage(const std::string& img) {
    sprites.clear();
    // TODO: Add checks to ensure this loads properly and handle it of it doesn't
    sprites.push_back(SDL_LoadBMP(img.c_str()));
}

void GameRectangle::loadSpriteFiles(const std::vector<std::string>& files) {
    sprites.clear();
    for (std::string file : files) {
        sprites.push_back(SDL_LoadBMP(file.c_str()));
    }
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
