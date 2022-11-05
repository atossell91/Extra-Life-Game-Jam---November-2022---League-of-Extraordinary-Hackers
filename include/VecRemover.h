//  Copyright 2022 Anthony Tossell
#ifndef INCLUDE_VECFINDER_H_
#define INCLUDE_VECFINDER_H_

#include <vector>

class VecRemover {
 public:
    template <typename T>
    static void remove(std::vector<T>& vec, T elem) {
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

    template <typename T>
    static bool isInVector(std::vector<T>& vec, T elem) {
        for (auto e : vec) {
            if (e == elem) {
                return true;
            }
        }
        return false;
    }

};
#endif  // INCLUDE_VECFINDER_H_
