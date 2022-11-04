//  Copyright 2022 Anthony Tossell
#include "../include/VecFinder.h"

#include <vector>

template <typename T>
void VecFinder::find(std::vector<T>& vec, T elem) {
    auto i = vec.begin();
    for (; i != vec.end(); ++i) {
        if (*i == elem) {
            break;
        }
    }
    if (i != vec.end()) {
        vec.erase(i);
    }
}
