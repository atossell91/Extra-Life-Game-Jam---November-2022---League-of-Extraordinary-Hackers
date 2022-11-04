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
  void travel();
  void travel(const Uint8 *state);
};

#endif /* INCLUDE_PLAYER_H_ */
