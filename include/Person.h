/*
 * Person.h
 *
 *  Created on: Nov. 3, 2022
 *      Author: Liam
 */

#ifndef INCLUDE_PERSON_H_
#define INCLUDE_PERSON_H_
#include "Characters.h"

class Person : public Characters {
 public:
  Person(int x, int y);
  void travel();
  void respawn();
 private:
  int score = 0;
  const int spawnx;
  const int spawny;
  int spawntimer = 0;
};

#endif /* INCLUDE_PERSON_H_ */
