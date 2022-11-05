/*
 * Player.cpp
 *
 *  Created on: Nov. 3, 2022
 *      Author: Liam
 */
#include "Player.h"
#include <iostream>

Player::Player(std::vector<IOverlappable*>* physicals,
  std::vector<IOverlappable*>* nonPhysicals) {
    setSpeed(PLAYER_SPEED);
    setWidth(PLAYER_WIDTH);
    setHeight(PLAYER_HEIGHT);
    this->physicals = physicals;
    this->nonPhysicals = nonPhysicals;
}

void Player::travel() {
}

void Player::travel(const Uint8 *state) {
  if (state[SDL_SCANCODE_UP] && playerNo == 1) {
    moveY(-speed);
    CurrentDirection = EnumDirection::Up;
  }
  if (state[SDL_SCANCODE_DOWN] && playerNo == 1) {
    moveY(speed);
    CurrentDirection = EnumDirection::Down;
  }
  if (state[SDL_SCANCODE_LEFT] && playerNo == 1) {
    moveX(-speed);
    CurrentDirection = EnumDirection::Left;
  }
  if (state[SDL_SCANCODE_RIGHT] && playerNo == 1) {
    moveX(speed);
    CurrentDirection = EnumDirection::Right;
  }
  if (state[SDL_SCANCODE_W] && playerNo == 2) {
    moveY(-speed);
    CurrentDirection = EnumDirection::Up;
  }
  if (state[SDL_SCANCODE_S] && playerNo == 2) {
    moveY(speed);
    CurrentDirection = EnumDirection::Down;
  }
  if (state[SDL_SCANCODE_A] && playerNo == 2) {
    moveX(-speed);
    CurrentDirection = EnumDirection::Left;
  }
  if (state[SDL_SCANCODE_D] && playerNo == 2) {
    moveX(speed);
    CurrentDirection = EnumDirection::Right;
  }
}

void Player::draw(SDL_Surface* surface) {
  SDL_Rect r;
  r.w = width;
  r.h = height;
  r.x = xPos;
  r.y = yPos;
  switch(CurrentDirection) {
    case(EnumDirection::Up):
    SDL_BlitSurface(sprites[0], NULL, surface, &r);
    break;
    case(EnumDirection::Down):
    SDL_BlitSurface(sprites[1], NULL, surface, &r);
    break;
    case(EnumDirection::Left):
    SDL_BlitSurface(sprites[2], NULL, surface, &r);
    break;
    case(EnumDirection::Right):
    SDL_BlitSurface(sprites[3], NULL, surface, &r);
    break;
  }
}
