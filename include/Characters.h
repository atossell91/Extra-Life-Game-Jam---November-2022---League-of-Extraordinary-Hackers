/*
 * Characters.h
 *
 *  Created on: Nov. 3, 2022
 *      Author: terra
 */

#ifndef INCLUDE_CHARACTERS_H_
#define INCLUDE_CHARACTERS_H_
#include "GameRectangle.h"

class Characters : public GameRectangle {
 public:
  virtual void travel() = 0;
  void setSpeed(unsigned int spd);
 protected:
  unsigned int speed = 10;
};

#endif /* INCLUDE_CHARACTERS_H_ */
