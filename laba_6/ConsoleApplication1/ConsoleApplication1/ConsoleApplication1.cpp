#include <iostream>
#include <vector>

#include "fillrandom.h"
#include "sortMethod.h"

int main()
{
    using namespace std::literals;
    setlocale(LC_ALL, "ru");
    Size v_size = GetSize();
    std::vector<std::vector<int>> v(v_size.row, std::vector<int> (v_size.column));
    FillRandom(v, v_size);
    СomparisonSortMethod(v);
    
}





