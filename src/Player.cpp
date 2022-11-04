/*
 * Player.cpp
 *
 *  Created on: Nov. 3, 2022
 *      Author: Liam
 */
#include "Player.h"

void Player::travel() {
}

void Player::travel(const Uint8 *state) {
  if (state[SDL_SCANCODE_UP]) {
    moveY(-speed);
  }
  if (state[SDL_SCANCODE_DOWN]) {
    moveY(speed);
  }
  if (state[SDL_SCANCODE_LEFT]) {
    moveX(-speed);
  }
  if (state[SDL_SCANCODE_RIGHT]) {
    moveX(speed);
  }
}
