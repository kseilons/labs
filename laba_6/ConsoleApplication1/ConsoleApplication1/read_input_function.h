#pragma once

#include <string>
#include <optional>

std::string ReadLine();
std::optional<int> GetPositiveNumInner();
void CatSpace(std::string& str);
int GetPositiveNum(std::string message = "������� �����", std::string error_message = "�� ����� �� ���������� ��������, ���������� ��� ���");
