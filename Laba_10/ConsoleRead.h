#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace std::literals;
class Read {
public:
	static std::string ReadLine(std::string message = "Неккоректное значение"s)
	{
		while (true) {
			std::string s;
			std::getline(std::cin, s);
			if (!s.empty()) {
				return s;
			}
			std::cout << message;

		}
		
	}
	static double GetNum(std::string message, std::string error_message = "Неккоректное значение"s)
	{
		while (true) {
			std::cout << message;
			std::string str = ReadLine(message);
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
	static int GetIntNum(std::string message, std::string error_message = "Неккоректное значение"s)
	{
		while (true) {
			std::cout << message;
			std::string s = ReadLine(message);
			std::vector<std::string> split_word = SplitIntoWords(s);
			if (split_word.size() == 1 && CheckIsNum(split_word[0])) {
				return std::stoi(split_word[0]);
			}
			std::cout << error_message << std::endl;
		}
	}

	static std::pair<size_t, size_t> GetPosition(std::string message = "Введите номер строки и символ:",
		std::string error_message = "Неккоректное значение"s) {
		while (true) {
			std::cout << message;
			std::string s = ReadLine(message);
			size_t column = 0, row = 0;
			std::vector<std::string> split_word = SplitIntoWords(s);
			if (split_word.size() == 2 && CheckIsNum(split_word[0]) && CheckIsNum(split_word[1]) &&
				std::stoi(split_word[0]) > 0 && std::stoi(split_word[1]) > 0 ) {
				return { std::stoi(split_word[0]), std::stoi(split_word[1]) };
			}
			std::cout << error_message << std::endl;
		}
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

