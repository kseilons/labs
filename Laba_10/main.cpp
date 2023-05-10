#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <Windows.h>
#include <sstream>
#include <algorithm>
#include "ConsoleRead.h"
#include "Position.h"
#include "ConsoleColor.h"
using namespace std;

namespace File {
	void Write(string path, const vector<string>& text) {
		ofstream fout;
		fout.open(path, 'w');
		for (const string& line : text) {
			fout << line << endl;
		}
		fout.close();
	}
	class InputFile {
	public:
		InputFile(string& path) {
			while (true) {
				if (path.empty()) {
					cout << "Введите путь к файлу: ";
					getline(cin, path);
					if (!checkPath(path.c_str())) {
						std::cout << "Некоректный путь до файла" << endl;
						continue;
					}
				}
				file.open(path);
				if (!file.is_open()) {
					std::cout << "Файл не открылся" << endl;
					path.clear();
					continue;
				}
				break;
			}
		}
		vector<string> ReadFile() {
			vector<string> result;
			string str;
			while (getline(file, str))
			{
				result.push_back(str);
			}
			return result;
		}

		~InputFile() {
			file.close();
		}
	private:
		ifstream file;
		bool checkPath(const char* path)
		{
			const char* reservedWords[] = { "CON", "CONSOLE", "PRN", "AUX", "COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9",
				"LPT1", "LPT2", "LPT3", "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9" };
			char name[_MAX_FNAME];
			char ext[_MAX_EXT];
			_splitpath_s(path, nullptr, 0, nullptr, 0, name, _MAX_FNAME, ext, _MAX_EXT);
			std::transform(name, name + strlen(name), name, ::toupper);
			for (int i = 0; i < 22; i++)
			{
				if (strcmp(name, reservedWords[i]) == 0)
				{
					return false;
				}
			}
			return true;
		}
	};
}


class Print {
public:
	static void PrintText(vector<string> text, string message= "Текущее состояние файла:", Color color = Color::primary) {
		ConsoleColor Console;
		cout << endl << message << endl;
		Console.SetColor(color);
		for (size_t line_count = 0; line_count < text.size(); ++line_count) {
			PrintLine(line_count, text[line_count]);
		}
	}
private:
	static void PrintLine(size_t line, string str) {
		cout << line + 1 << ". " << str << endl;
	}
};

namespace IndividualTasks {

	void Capitalize(vector<string>& text) {
		for (string& line : text) {
			bool IsCap = true;
			for (char& ch : line) {
				if (ch == ' ' || ch == '(' || ch == '"' || ch == '.' || ch == ',') {
					IsCap = true;
				}
				else if (IsCap) {
					ch = toupper(ch);
					IsCap = false;
				}
			}	
		}
	}

	

	pair<Position, Position> GetSelectionPosition(vector<string>& text) {
		Position pos_begin;
		Position pos_end;
		do
		{
			pos_begin = Read::GetPosition("Введите номер строки и символ, откуда начать копирование: ");
			pos_end = Read::GetPosition("Введите номер строки и символ, конца копирования: ");

			if (pos_end == pos_begin) {
				cout << "Введите хотя бы какой-то интервал пожалуйста :(" << endl;
			}
			else if (pos_begin.row < text.size() + 1 && pos_begin.column <= text[pos_begin.row - 1].size() + 1
				&& pos_end.row < text.size() + 1 && pos_end.column <= text[pos_end.row - 1].size() + 1) {
				return { pos_begin, pos_end };
			}
			else {
				cout << "Ошибка индексации, попробуйте еще раз" << endl;
			}
		} while (true);
	}
	string Copy(vector<string>& text, Position pos_begin, Position pos_end) {
		string result;
		if (pos_begin > pos_end) {
			std::swap(pos_begin, pos_end);
		}

		for (size_t column = pos_begin.column - 1; column < (pos_end.row == pos_begin.row ?
			pos_end.column - 1
			: text[pos_begin.row - 1].size()); column++) {
			result += text[pos_begin.row - 1][column];
		}
		for (size_t row = pos_begin.row; row < pos_end.row - 1; row++) {
			result += '\n';
			for (size_t column = 0; column < text[row].size(); column++) {
				result += text[row][column];
			}
			
		}
		if (pos_begin.row != pos_end.row) {
			result += '\n';
			for (size_t column = 0; column < pos_end.column - 1; column++) {
				result += text[pos_end.row - 1][column];
			}
		}
		
		return result;
	}

	void Selection(vector<string>& text) {
		auto [pos_begin, pos_end] = GetSelectionPosition(text);
		string copy = Copy(text, pos_begin, pos_end);
		cout << "Отобранное значение\n";
		ConsoleColor color;
		color.SetColor(second);
		cout<< copy << endl;
	}

	string ToLower(const string& str) {
		string result;
		for (char c : str) {
			result += tolower(c);
		}
		return result;
	}

	void Search(vector<string> text) {
		cout << "Введите запрос:"s;
		string query = Read::ReadLine();
		ConsoleColor color(second);
		bool find = false;
		for (size_t i = 0; i < text.size(); i++) {
			string to_search = ToLower(text[i]);
			size_t ind = to_search.find(ToLower(query));
			while (ind < text[i].size()) {
				find = true;
				cout <<'"' << query << "\" найденно в \"" << text[i] << "\". На " << i + 1
					<< " строке, первый символ " << ind + 1 << endl;
				ind = to_search.find(ToLower(query), ind + 1);
			}
		}
		if (!find) {
			cout << "По вашему запросу ничего не найдено"s << endl;
		}
	}


}




namespace Client {
	void Begin(string& path) {
		File::InputFile fin(path); // Возвращает путь
		vector<string> text = fin.ReadFile();
		Print::PrintText(text, "Начальный файл:", Color::second);
	}
	void Current(string& path) {
		File::InputFile fin(path); // Возвращает путь
		vector<string> text = fin.ReadFile();
		Print::PrintText(text);
		
		cout << endl << "Меню:" << endl;
		cout << "1.Отбор (с N до M символа)." << endl
			<< "2.Замена всех первых строчных букв слов прописными" << endl
			<< "3.Поиск в строке." << endl
			<< "-Любую другую цифру для выхода" << endl;

		int a = Read::GetIntNum("Введите число:");
		if (a == 1) {
			IndividualTasks::Selection(text);
		}
		else if (a == 2) {
			IndividualTasks::Capitalize(text);
		}
		else if (a == 3) {
			IndividualTasks::Search(text);
		}
		else {
			exit(1);
		}
		File::Write("output.txt", text);
	}
}

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

int main()

{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	locale loc("");
	
	string path;
	//Client::Begin(path);
	path = "1.txt";

	while (true) {
		Client::Current(path);
	}
	return 0;

}