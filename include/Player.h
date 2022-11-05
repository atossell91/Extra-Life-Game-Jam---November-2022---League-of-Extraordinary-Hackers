/*
 * Player.h
 *
 *  Created on: Nov. 3, 2022
 *      Author: Liam
 */

#ifndef INCLUDE_PLAYER_H_
#define INCLUDE_PLAYER_H_
#include "Characters.h"

class Player : public Characters {
 public:
  enum EnumDirection {Up, Down, Left, Right};
  EnumDirection CurrentDirection = EnumDirection::Up;
  int playerNo = 1;
  const int PLAYER_WIDTH = 30;
  const int PLAYER_HEIGHT = 30;
  const int PLAYER_SPEED = 3;
  Player(std::vector<IOverlappable*>* physicals,
  std::vector<IOverlappable*>* nonPhysicals);
  void travel();
  void travel(const Uint8 *state);
  void draw(SDL_Surface* surface);
};

#endif /* INCLUDE_PLAYER_H_ */
