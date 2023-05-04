#include <algorithm>
#include <fstream>
#include <codecvt>
#include "ConsoleRead.h"
#include "FileClient.h"

std::deque<std::string> SplitIntoWordsView(std::string str) {
	std::string sep = ";:/.,";
	std::deque<std::string> result;

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

FileClient::FileClient() {
	GetFilePath();
}



std::vector<Data> FileClient::Read() {
	do
	{
		file.open(path_to_file_);
		if (!file.is_open()) {
			std::cout << "Не удалось открыть файл" << std::endl;

			GetFilePath();
		}
		else {
			break;
		}

	} while (true);
	
	std::vector<Data> result;
	while (true) {
		Data date;
		date.surname = ReadWord();
		date.name = ReadWord();
		date.patronymic = ReadWord();
		if (end_flag) {
			if (!date.name.empty()) {
				result.push_back(date);
			}
			file.close();
			return result;
		}
		result.push_back(date);
	}
}

std::string FileClient::ReadWord() {
	if (buffer.empty()) {
		if (!ReadFileToBuffer()) return "";
	}

	std::string result = buffer.front();
	buffer.pop_front();
	return result;
}

bool FileClient::ReadFileToBuffer() {
	std::string word;
	if (file >> word)
	{
		std::transform(word.begin(), word.end(), word.begin(), tolower);
		buffer = SplitIntoWordsView(word);
	}
	else {
		end_flag = true;
		return false;
	}
	return true;
}

bool FileClient::CheckPath(const std::string& path)
{
	const char* reservedWords[] = { "CON", "CONSOLE", "PRN", "AUX", "COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9",
	"LPT1", "LPT2", "LPT3", "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9" };
	char name[_MAX_FNAME];
	char ext[_MAX_EXT];
	_splitpath_s(path.c_str(), nullptr, 0, nullptr, 0, name, _MAX_FNAME, ext, _MAX_EXT);
	std::transform(name, name + strlen(name), name, ::toupper);
	for (int i = 0; i < sizeof(reservedWords) / sizeof(reservedWords[0]); i++)
	{
		if (strcmp(name, reservedWords[i]) == 0)
		{
			return false;
		}
	}
	return true;
}



void FileClient::GetFilePath() {

	do
	{
		std::cout << "Введите имя файла: ";
		std::string path = Console::GetWord();
		std::string c;
		std::getline(std::cin, c);
		if (CheckPath(path)) {
			path_to_file_ = path;
			return;
		}
		std::cout << "Путь содержит запрещенные символы" << std::endl;

	} while (true);


}