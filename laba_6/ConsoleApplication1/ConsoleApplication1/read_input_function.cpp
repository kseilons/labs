#include "read_input_function.h"

#include <iostream>
#include <optional>

std::string ReadLine() {
    std::string s;
    std::getline(std::cin, s);
    return s;
}
void CutSpace(std::string& str) {
    int start_index = 0;
    int end_index = str.length();
    for (start_index; str[start_index] == ' '; start_index++);
    for (end_index; str[end_index] == ' '; end_index--);
    str = str.substr(start_index, end_index);
}

bool isValid(std::string& str) {
    if (str[0] == '-')
        return false;
    else if (str[0] == '+')
        str = str.substr(1, str.length());
    bool have_dots = false;
    for (char ch : str) {
        if (ch == '.' || ch == ',') {
            if (ch == str[0]) {
                return false;
            }
            have_dots = true;
        }
        else if (have_dots && ch != '0' || ch > '9' || ch < '0') {
            return false;
        }
    }
    return true;
}


int GetPositiveNum(std::string message, std::string error_message) {
    while (true) {
        std::cout << message;
        std::string str = ReadLine();
        CutSpace(str);
        if (!str.empty() && isValid(str) && std::stoi(str) != 0) {
            return std::stoi(str);
        }
        std::cout << error_message << std::endl;
    }
}