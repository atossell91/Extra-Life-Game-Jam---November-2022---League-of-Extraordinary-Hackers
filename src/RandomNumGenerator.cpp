//  Copyright 2022 Anthony Tossell
#include "../include/RandomNumGenerator.h"

RandomNumGenerator::RandomNumGenerator() {
    rng = std::mt19937(randomDevice());
}

// Generate a random number. The upper and lower bounds are inclusive
int RandomNumGenerator::generate(int min, int max) {
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
    return dist(rng);
}

