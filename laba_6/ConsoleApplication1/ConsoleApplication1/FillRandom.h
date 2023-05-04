#pragma once

#include <vector>
#include <random>
#include "2d_size.h"

template<typename Integer>
void FillRandom(std::vector<std::vector<Integer>>& v, Size size) {
    srand(static_cast<unsigned int> (time(NULL)));
    int hlopin = 1;
    for (size_t i = 0; i < size.row; ++i) {
        for (size_t j = 0; j < size.column; ++j) {
            Integer number = rand() % 3;
            //Integer number = hlopin;
            //hlopin = 1;
            v[i][j] = number;
        }
    }
}