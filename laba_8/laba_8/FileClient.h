#pragma once

#include <string>
#include <locale.h>
#include <fstream>
#include <vector>
#include <deque>
#include <regex>
#include "Data.h"
#include <iostream>


class FileClient
{
public:
	FileClient();

	std::vector<Data> Read();

private:
	std::deque<std::string> buffer;

	std::ifstream file;
	std::string path_to_file_;
	bool end_flag = false;

	std::string ReadWord();
	bool ReadFileToBuffer();
	void GetFilePath();
	bool CheckPath(const std::string& path);
};

