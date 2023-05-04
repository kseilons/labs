//#include "ReadFunc.h"
//
//static std::string Read::ReadLine()
//{
//	std::string s;
//	std::getline(std::cin, s);
//	return s;
//}
//
//
//
//static double Read::GetNum(std::string message, std::string error_message) {
//	while (true) {
//		std::cout << message;
//		std::string str = ReadLine();
//		std::vector<std::string> words = SplitIntoWords(str);
//		if (words.size() == 1 && CheckIsFloat(words[0]))
//		{
//			return std::stod(str);
//		}
//		std::cout << error_message << std::endl;
//	}
//}
//
//static double GetPositivNum(std::string message, std::string error_message) {
//	while (true) {
//		double epsilon = GetNum(message, error_message);
//		if (epsilon > 0) {
//			return epsilon;
//		}
//		std::cout << error_message << std::endl;
//	}
//}
//
//static std::vector<std::string> SplitIntoWords(const std::string& text) {
//	std::vector<std::string> words;
//	std::string word;
//	for (const char c : text) {
//		if (c == ' ') {
//			if (!word.empty()) {
//				words.push_back(word);
//				word.clear();
//			}
//		}
//		else {
//			word += c;
//		}
//	}
//	if (!word.empty()) {
//		words.push_back(word);
//	}
//
//	return words;
//}
//
//
//static bool CheckIsNum(std::string str) {
//	if (str[0] == '+' || str[0] == '-')
//		str = str.substr(1, str.length());
//
//	bool have_dots = false;
//	for (char ch : str) {
//		if (ch == '.' || ch == ',') {
//			have_dots = true;
//		}
//		else if (have_dots && ch != '0' || ch > '9' || ch < '0') {
//			return false;
//		}
//	}
//	return true;
//}
//static bool CheckIsFloat(std::string str) {
//	if (str[0] == '+' || str[0] == '-')
//		str = str.substr(1, str.length());
//
//	bool have_dots = false;
//	for (char ch : str) {
//		if (ch == '.' || ch == ',') {
//			if (have_dots) {
//				return false;
//			}
//			have_dots = true;
//		}
//		else if (ch > '9' || ch < '0') {
//			return false;
//		}
//	}
//	return true;
//}
