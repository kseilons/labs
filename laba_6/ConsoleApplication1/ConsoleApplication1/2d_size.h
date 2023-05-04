#pragma once

#include "read_input_function.h"

struct Size {
    size_t row;
    size_t column;
};

Size GetSize() {
    using namespace std::string_literals;
    do {
        Size size;
        size.column = GetPositiveNum("введите n:");
        size.row = GetPositiveNum("введите m:");
        if (size.row * size.column <= 100000000) {
            return size;
        }
        std::cout << "Слишком большой массив, максимальный размер массива 100000000 элементов"s << std::endl;
    } while (true);
    
}
