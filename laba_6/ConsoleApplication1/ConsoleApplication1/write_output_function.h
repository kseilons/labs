#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <unordered_map>
#include "SortInfo.h"
#include <locale.h>

#include "log_duration.h"

#define MIN_BORDER 2
#define MIN_ELEM_WIDTH 3
#define MAX_SIZE_OUTPUT_MASSIV 20

class PrintContainer {
public:
    PrintContainer(size_t n)
        :elem_width_((MIN_ELEM_WIDTH > n ? MIN_ELEM_WIDTH : n) + MIN_BORDER)
    {
    }

    template<typename Elem>
    std::ostream& Print2d(std::ostream& out, const std::vector<std::vector<Elem>>& container) {
        using namespace std::literals;
        for (auto line : container) {
            Print(out, line);
            out << std::endl;
        }
        return out;
    }

    template<typename Container>
    std::ostream& Print(std::ostream& out, const Container& container) {
        using namespace std::literals;
        for (const auto& elem : container) {
            PrintElem(out, elem);
        }
        return out;
    }

    template<typename Elem>
    std::ostream& PrintElem(std::ostream& out, const Elem& elem) {

        out << std::setw(elem_width_) << elem;
        return out;
    }
private:
    int elem_width_ = MIN_ELEM_WIDTH + MIN_BORDER;
};


template<typename Elem>
std::ostream& operator<< (std::ostream& out, const std::vector<std::vector<Elem>>& container) {
        
    if (container.size() > MAX_SIZE_OUTPUT_MASSIV || !container.empty() && container[0].size() > MAX_SIZE_OUTPUT_MASSIV) {
        using namespace std::literals;
        out << "   massiv..."s << std::endl;
        return out;
    } 

    long max_elem = 0;
    for (size_t i = 0; i < container.size(); i++) {
        long max_in_line = *std::max_element(container[i].begin(), container[i].end());
        if (max_in_line > max_elem) {
            max_elem = max_in_line;
        }
    }

    PrintContainer print(std::to_string(max_elem).length());
    print.Print2d(out, container);
    return out;
}

void PrintComparisentTable(const std::unordered_map<std::string, SortInfo>& info) {
    using namespace std;
    cout << endl << "Comparison table : " << endl;
    cout << "    ________________________________________________________"s << endl;
    cout << "    | "s << setw(14    ) << "   sortType  "s << " | " << std::setw(14) << "iteration quantity"s << " | " << setw(15) << "swap quantity"s << " |"s << endl;
    cout << "    |________________|____________________|_________________|" << endl;
    for (const auto& [name, sort_info] : info) {
        cout << "    | " << setw(14) << name << " | " << setw(18) << sort_info.comparisons
            << " | " << setw(15) << sort_info.permutations << " |" << endl;
    }
    cout << "    |" << "________________|____________________|_________________| ";

}