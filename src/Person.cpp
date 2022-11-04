/*
 * Person.cpp
 *
 *  Created on: Nov. 3, 2022
 *      Author: Liam
 */

#include "Person.h"
#include <thread>
#include <chrono>
Person::Person(int x, int y)
    :
    spawnx(x),
    spawny(y) {
}

void Person::travel() {
  moveY(speed);
}

void Person::respawn() {
  setX(8000);
  setY(4000);
  spawntimer = (rand() % 2) + 1;  //Timer for 1-3 seconds
  std::this_thread::sleep_for(std::chrono::seconds(spawntimer));
  setX(spawnx);
  setY(spawny);
  score++;
}
