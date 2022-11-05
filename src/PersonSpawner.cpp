//  Copyright 2022 Anthony Tossell
#include "../include/PersonSpawner.h"

#include <vector>
#include <SDL2/SDL.h>
#include "GameRectangle.h"
#include "Person.h"
#include "PersonSpawner.h"

PersonSpawner::PersonSpawner(std::vector<IOverlappable*>* physicals,
    std::vector<IOverlappable*>* nonPhysicals,
    std::vector<IOverlappable*>* playerNonPhysicals,
    std::vector<IDrawable*>* drawables,
    RandomNumGenerator* rg) {
        this->drawables = drawables;
        this->nonPhysicals = nonPhysicals;
        this->playerNonPhysicals = playerNonPhysicals;
        this->physicals = physicals;
        this->rGen = rg;
}

Person* PersonSpawner::spawnPerson() {
  Person* p = new Person(physicals, playerNonPhysicals);
  drawables->push_back(p);
  return p;
}

bool PersonSpawner::isCollision(IOverlappable* o) {
    for (auto p : *physicals) {
        if (o->isOverlap(*p, false)) {
            return true;
        }
    }
    return false;
}

std::vector<Person*> PersonSpawner::spawnPeople(int n, int minX, int maxX) {
    int count = 0;
    GameRectangle* g;
    std::vector<Person*> people;
    int x =0;
    for (; count < n; ++count) {
        do {
            g = new GameRectangle();
            x = rGen->generate(minX, maxX);
            g->setWidth(Person::WIDTH);
            g->setHeight(Person::HEIGHT);
            g->setX(x);
            g->setY(-Person::HEIGHT);
        } while (isCollision(static_cast<IOverlappable*>(g)));
        Person* p = spawnPerson();
        p->setX(x);
        p->setY(-Person::HEIGHT);
        people.push_back(p);
    }
    return people;
}
