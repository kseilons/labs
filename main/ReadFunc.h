#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace std::literals;
class Read {
public:
	static std::string ReadLine()
	{
		std::string s;
		std::getline(std::cin, s);
		return s;
	}
	static double GetNum(std::string message, std::string error_message = "Неккоректное значение"s)
	{
		while (true) {
			std::cout << message;
			std::string str = ReadLine();
			std::vector<std::string> words = SplitIntoWords(str);
			if (words.size() == 1 && CheckIsFloat(words[0]))
			{
				return std::stod(str);
			}
			std::cout << error_message << std::endl;
		}
	}
	static double GetPositivNum(std::string message, std::string error_message = "Неккоректное значение"s)
	{
		while (true) {
			double epsilon = GetNum(message, error_message);
			if (epsilon > 0) {
				return epsilon;
			}
			std::cout << error_message << std::endl;
		}
	}

	static void ReadlineInterval(double& tb_epsilon, double& x_start, double& x_end, double& x_del, double& a) {
		tb_epsilon = Read::GetPositivNum("Введите точность (ее значение должно быть больше 0):"s);
		do {
			x_start = Read::GetNum("Введите x_start:"s);
			x_end = Read::GetNum("Введите x_end : "s);
			do {
				x_del = Read::GetNum("Введите шаг интервала (его значение не должно быть равно нулю):"s);
			} while (x_del == 0);
			if (!(x_start < x_end && x_del < 0) || (x_start > x_del && x_del > 0)) {
				break;
			}
			std::cout << "Интервал введен неверно, проход невозможен\n"s;
		} while (true);
		a = Read::GetNum("Введите значение a:"s);
	}
private:
	static std::vector<std::string> SplitIntoWords(const std::string& textSaf)
	{
		std::vector<std::string> words;
		std::string word;
		for (const char c : textSaf) {
			if (c == ' ') {
				if (!word.empty()) {
					words.push_back(word);
					word.clear();
				}
			}
			else {
				word += c;
			}
		}
		if (!word.empty()) {
			words.push_back(word);
		}

		return words;
	}

	static bool CheckIsNum(std::string str)
	{
		if (str[0] == '+' || str[0] == '-')
			str = str.substr(1, str.length());

		bool have_dots = false;
		for (char ch : str) {
			if (ch == '.' || ch == ',') {
				have_dots = true;
			}
			else if (have_dots && ch != '0' || ch > '9' || ch < '0') {
				return false;
			}
		}
		return true;
	}
	static bool CheckIsFloat(std::string str)
	{
		if (str[0] == '+' || str[0] == '-')
			str = str.substr(1, str.length());

		bool have_dots = false;
		for (char ch : str) {
			if (ch == '.' || ch == ',') {
				if (have_dots) {
					return false;
				}
				have_dots = true;
			}
			else if (ch > '9' || ch < '0') {
				return false;
			}
		}
		return true;
	}
};

