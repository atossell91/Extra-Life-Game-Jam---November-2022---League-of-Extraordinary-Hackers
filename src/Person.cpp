/*
 * Person.cpp
 *
 *  Created on: Nov. 3, 2022
 *      Author: Liam
 */

#include "Person.h"
#include "IOverlappable.h"
#include <thread>
#include <chrono>
#include <iostream>
Person::Person(std::vector<IOverlappable*>* phys,
std::vector<IOverlappable*>* nonPhys) {
    physicals = phys;
    nonPhysicals = nonPhys;
    physicals->push_back(this);
    nonPhysicals->push_back(this);
    setWidth(WIDTH);
    setHeight(HEIGHT);
    loadSpriteFiles({
      "assets/person/person-small-0.bmp",
      "assets/person/person-small-1.bmp",
      "assets/person/person-small-2.bmp"
    });
}

void Person::travel() {
  moveY(speed);
}

void Person::respawn() {
  setX(8000);
  setY(4000);
  spawntimer = (rand() % 2) + 1;  //Timer for 1-3 seconds
  std::this_thread::sleep_for(std::chrono::seconds(spawntimer));
  //setX(spawnx);
  //setY(spawny);
  score++;
}
