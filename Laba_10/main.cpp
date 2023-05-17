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
	void Write(string path, const string& text) {
		ofstream fout;
		fout.open(path, 'w');
		fout << text << endl;
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
	static void PrintText(vector<string> text, string message = "Текущее состояние файла:", Color color = Color::primary) {
		ConsoleColor Console(color);
		cout << endl << message << endl;
		for (size_t line_count = 0; line_count < text.size(); ++line_count) {
			PrintLine(line_count, text[line_count]);
		}
	}
private:
	static void PrintLine(size_t line, string str) {
		cout << line + 1 << "." << str << endl;
	}
};

namespace IndividualTasks {

	void Capitalize(vector<string>& text) {
		for (string& line : text) {
			bool IsCap = true;
			for (char& ch : line) {
				if (ch == ' ' || ch == '('  || ch == '\\' || ch == '/' || ch == '"' || ch == '.' || ch == ',') {
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

	void Copy(vector<string>& text, Position pos_begin, Position pos_end) {
		vector<string> result;
		result.reserve(text.size());

		if (pos_begin > pos_end) {
			std::swap(pos_begin, pos_end);
		}
		size_t row_size = text[pos_begin.row - 1].size();
		size_t end_column = pos_end.column - 1;

		if (pos_begin.row == pos_end.row) {
			result.push_back(text[pos_begin.row - 1].substr(pos_begin.column - 1, pos_end.column -1));
		}
		else {
			result.push_back(text[pos_begin.row - 1].substr(pos_begin.column - 1, row_size - (pos_begin.column - 1)));
		}
		
		size_t end_row = pos_end.row - 1;
		for (size_t row = pos_begin.row; row < end_row; row++) {
			result.push_back(text[row]);
		}

		if (pos_begin.row != pos_end.row) {
			result.push_back(text[pos_end.row - 1].substr(0, end_column));
		}
		swap(text, result);
	}

	void Selection(vector<string>& text) {
		auto [pos_begin, pos_end] = GetSelectionPosition(text);
		Copy(text, pos_begin, pos_end);
	}

	string ToLower(const string& str) {
		string result;
		for (char c : str) {
			result += tolower(c);
		}
		return result;
	}

	void Search(const vector<string>& text) {
		cout << "Выберите действие.\n1. Для поиска в конкретной строке\n2. Для поиска во всем тексте\nДля выхода любое другое число\n"s;
		int a = Read::GetIntNum("Введите число:");
		if (a == 1) {
			int search_line = 0;
			while (true)
			{
				search_line = Read::GetIntNum("Ввидите номер строки для поиска:");
				if (search_line > text.size() || search_line <= 0) {
					cout << "ошибка доступа к строке\n"s;
					continue;
				}
				break;
			}
			cout << "Введите запрос:"s;
			string query = Read::ReadLine();

			ConsoleColor color(second);
			bool is_find = false;
			string to_search = ToLower(text[search_line-1]);
			size_t ind = to_search.find(ToLower(query));
			while (ind < text[search_line-1].size()) {
				is_find = true;
				cout << '"' << query << "\" найденно начиная с " << ind + 1 << " символа" << endl;
				ind = to_search.find(ToLower(query), ind + 1);
			}
			if (!is_find) {
				cout << "По вашему запросу ничего не найдено"s << endl;
			}
		}
		else if (a == 2) {
			cout << "Введите запрос:"s;
			string query = Read::ReadLine();
			ConsoleColor color(second);
			bool find = false;
			for (size_t i = 0; i < text.size(); i++) {
				string to_search = ToLower(text[i]);
				size_t ind = to_search.find(ToLower(query));
				while (ind < text[i].size()) {
					find = true;
					cout << '"' << query << "\" найденно в \"" << text[i] << "\". На " << i + 1
						<< " строке, первый символ " << ind + 1 << endl;
					ind = to_search.find(ToLower(query), ind + 1);
				}
			}
			if (!find) {
				cout << "По вашему запросу ничего не найдено"s << endl;
			}
		}
	}


}

namespace Client {
	void Begin(string& path, const string& buffer_path) {
		File::InputFile fin(path); // Возвращает путь
		vector<string> text = fin.ReadFile();
		File::Write(buffer_path, text);
	}
	void Current(string path) {
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
		File::Write(path, text);
	}
}

int main()

{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	locale loc("");
	
	string path;
	string buffer_path = "output.txt";
	Client::Begin(path, buffer_path);
	
	while (true) {
		Client::Current(buffer_path);
	}
	return 0;

}