#pragma once

#include <string>
#include <vector>
#include <iostream>

std::string ReadLine() {
	std::string s;
	std::getline(std::cin, s);
	return s;
}

std::vector<std::string> SplitIntoWords(const std::string& textSaf) {
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

bool CheckIsNum(std::string str) {
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

int GetPositiveNum(std::string message, std::string error_message) {
	while (true) {
		std::cout << message;
		std::string str = ReadLine();
		std::vector<std::string> words = SplitIntoWords(str);
		if (words.size() == 1 && CheckIsNum(words[0]) && std::stoi(words[0]) != 0
			&& std::stoi(words[0]) == std::abs(std::stoi(words[0]))) 
		{
			return std::stoi(str);
		}
		std::cout << error_message << std::endl;
	}
}
