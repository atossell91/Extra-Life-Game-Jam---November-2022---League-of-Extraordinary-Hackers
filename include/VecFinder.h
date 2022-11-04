//  Copyright 2022 Anthony Tossell
#ifndef INCLUDE_VECFINDER_H_
#define INCLUDE_VECFINDER_H_

#include <vector>

class VecFinder {
 public:
    template <typename T>
    static void find(std::vector<T>& vec, T);
};

#endif  // INCLUDE_VECFINDER_H_
