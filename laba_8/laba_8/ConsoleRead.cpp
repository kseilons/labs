#include "ConsoleRead.h"

namespace Console {


	std::string GetWord() {
		do
		{
			std::string word;
			std::cin >> word;
			if (!word.empty()) {
				std::string c;
				return word;
			}
			
		} while (true);

	}

	std::vector<std::string> SplitIntoDots(std::string str) {
		std::string sep = ".";
		std::vector<std::string> result;

		std::string word;
		for (const auto& ch : str) {
			if (sep.find(ch) != sep.npos) {
				if (!word.empty()) {
					result.push_back(word);
					word.clear();
				}
			}
			else {
				word += ch;
			}
		}
		if (!word.empty()) {
			result.push_back(word);
			word.clear();
		}
		return result;
	}
	std::vector<std::string> GetWordReduc() {
		std::string word = GetWord();		
		return SplitIntoDots(word);
	}
}