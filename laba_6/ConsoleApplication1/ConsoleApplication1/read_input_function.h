#pragma once

#include <string>
#include <optional>

std::string ReadLine();
std::optional<int> GetPositiveNumInner();
void CatSpace(std::string& str);
int GetPositiveNum(std::string message = "Введите число", std::string error_message = "Вы ввели не корректное значение, попробуйте еще раз");
