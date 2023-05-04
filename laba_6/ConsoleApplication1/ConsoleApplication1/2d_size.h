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
        size.column = GetPositiveNum("������� n:");
        size.row = GetPositiveNum("������� m:");
        if (size.row * size.column <= 100000000) {
            return size;
        }
        std::cout << "������� ������� ������, ������������ ������ ������� 100000000 ���������"s << std::endl;
    } while (true);
    
}
