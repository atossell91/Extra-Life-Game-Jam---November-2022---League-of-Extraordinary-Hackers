//  Copyright 2022 Anthony Tossell
#ifndef INCLUDE_RANDOMNUMGENERATOR_H_
#define INCLUDE_RANDOMNUMGENERATOR_H_

#include <random>

class RandomNumGenerator {
 private:
    std::random_device randomDevice;
    std::mt19937 rng;
 public:
    RandomNumGenerator();
    int generate(int min, int max);
};

#endif  // INCLUDE_RANDOMNUMGENERATOR_H_
