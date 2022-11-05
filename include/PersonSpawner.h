//  Copyright 2022 Anthony Tossell
#ifndef INCLUDE_PERSONSPAWNER_H_
#define INCLUDE_PERSONSPAWNER_H_

#include "Person.h"
#include "IOverlappable.h"
#include "IDrawable.h"
#include "RandomNumGenerator.h"
#include <vector>

class PersonSpawner {
 private:
    std::vector<IOverlappable*>* physicals;
    std::vector<IOverlappable*>* nonPhysicals;
    std::vector<IOverlappable*>* playerNonPhysicals;
    std::vector<IDrawable*>* drawables;
    RandomNumGenerator* rGen;
 public:
    PersonSpawner(std::vector<IOverlappable*>* physicals,
    std::vector<IOverlappable*>* nonPhysicals,
    std::vector<IOverlappable*>* playerNonPhysicals,
    std::vector<IDrawable*>* drawables,
    RandomNumGenerator* rg);
    bool isCollision(IOverlappable* o);
    Person* spawnPerson();
    std::vector<Person*> spawnPeople(int n, int minX, int maxX);
};

#endif  // INCLUDE_PERSONSPAWNER_H_
