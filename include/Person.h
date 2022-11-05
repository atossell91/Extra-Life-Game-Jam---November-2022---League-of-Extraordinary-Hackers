/*
 * Person.h
 *
 *  Created on: Nov. 3, 2022
 *      Author: Liam
 */

#ifndef INCLUDE_PERSON_H_
#define INCLUDE_PERSON_H_
#include "Characters.h"
#include <vector>

class Person : public Characters {
 public:
  static const int WIDTH = 27;
  static const int HEIGHT = 30;

  Person(std::vector<IOverlappable*>* phys, std::vector<IOverlappable*>* nonPhys);
  void travel();
  void respawn();
 private:
  int score = 0;
  int spawntimer = 0;
};

#endif /* INCLUDE_PERSON_H_ */
