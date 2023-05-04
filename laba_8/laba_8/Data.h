
#pragma once
#include <string>
#include <iostream>
struct Data {
	std::string name = "Unknown";
	std::string surname = "surname";
	std::string patronymic = "patronymic";
};

std::ostream& operator<<(std::ostream& out, Data data);