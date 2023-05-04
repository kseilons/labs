#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <Windows.h>
#include <sstream>
#include <algorithm>
#include "ConsoleRead.h"
using namespace std;


enum Color {
	primary,
	second
};


class ConsoleColor {
public:
	ConsoleColor() {
		out = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(out, &start_attribute);
	}
	void SetColor(Color color) {
		if (color == Color::primary) {
			SetConsoleTextAttribute(out, 3);
		}
		else if (color == Color::second) {
			SetConsoleTextAttribute(out, 10);
		}
	}

	~ConsoleColor() {
		SetDefaultColor();
	}

	void SetDefaultColor() {
		SetConsoleTextAttribute(out, start_attribute.wAttributes);
	}


private:
	HANDLE out;
	CONSOLE_SCREEN_BUFFER_INFO start_attribute;
};

class Print {
public:
	static void PrintText(vector<string> text, string message= "Текущее состояние файла:", Color color = Color::primary) {
		ConsoleColor Console;
		cout << message << endl;
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

namespace StrPreproces {

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


}


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

		cout << "Меню:" << endl;
		cout << "1.Отбор (с N до M символа)." << endl
			<< "2.Замена всех первых строчных букв слов прописными" << endl
			<< "3.Поиск в строке." << endl
			<< "-Любую другую цифру для выхода" << endl;

		string str = Read::ReadLine();
		int a = stoi(str);
		if (a == 1) {
			cout << 1;
		}
		else if (a == 2) {
			StrPreproces::Capitalize(text);
		}
		else if (a == 3) {
			cout << 2;
		}
		else {
			exit(1);
		}
		File::Write(path, text);
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
	ConsoleColor Console;
	setlocale(LC_ALL, "Russian");
	locale loc("");
	
	string path;
	Client::Begin(path);

	while (true) {
		Client::Current(path);
	}
//menu:
//
//
//
//
//	cout << "Меню:\n";
//
//
//	cout << "1.Копирование строк\n2.Замена всех первых строчных букв слов прописными\n3.Вставка текста из файла.\n--Любую другую цифру для выхода\n";

	//string s;
	//double a;
	//cin >> a;
	//int q, flag = 0;
	//double p, k, y;
	//cout << endl;
	//if ((a != 1) && (a != 2) && (a != 3) || (cin.fail()))
	//{
	//	exit(0);
	//}

	//if (a == 1)  //   Копирование строк                               
	//{
	//	cout << "Введите номер строки, которую хотите скопировать " << endl;
	//	do
	//	{
	//		cin >> p;
	//		if (p < 0 || p != floor(p) || p>text.size() - 1)
	//		{
	//			cout << "Введите корректное значение " << endl;
	//		}
	//	} while (p < 0 || p != floor(p) || p>text.size() - 1);
	//	cout << "Введите номер строки, после которой хотите вставить скопированную строку " << endl;
	//	do
	//	{
	//		cin >> k;
	//		if (k < 0 || k != floor(k) || k>text.size() - 1)
	//		{
	//			cout << "Введите корректное значение " << endl;
	//		}
	//	} while (k < 0 || k != floor(k) || k>text.size() - 1);
	//	fout.open("222.txt");
	//	for (q = 0; q <= k; q++)
	//	{
	//		fout << text[q] << endl;;
	//	}
	//	fout << text[p] << endl;
	//	for (int q = k + 1; q < text.size(); q++)
	//	{
	//		fout << text[q] << endl;;
	//	}
	//	fout.close();
	//	goto menu;
	//}

	//if (a == 2)
	//{
	//	fout.open("222.txt");
	//	string w;//Будет содержать текущее слово из текста
	//	string t;
	//	vector <string> array;//Вектор, каждый элемент которого слово из текста
	//	cout << "Введите номер строки, в которой хотите произвести преобразования " << endl;
	//	do
	//	{
	//		cin >> y;
	//		if (y< 0 || y != floor(y) || y>text.size() - 1)
	//		{
	//			cout << "Введите корректное значение " << endl;
	//		}
	//	} while (y < 0 || y != floor(y) || y>text.size() - 1);
	//	for (q = 0; q < y; q++)
	//	{
	//		fout << text[q] << endl;;
	//	}
	//	t = text[y];
	//	stringstream ss(t);
	//	while (ss >> w)
	//	{
	//		array.push_back(w);
	//	}
	//	for (j = 0; j < array.size(); j++)
	//	{
	//		if (array[j].length() == 1)
	//		{
	//			array[j][0] = toupper(array[j][0]);
	//		}
	//		else
	//		{
	//			for (int l = 0; l < array[j].length() - 1; l++)
	//			{
	//				if (array[j][0] > 96 && array[j][0] < 123)
	//				{
	//					array[j][0] = toupper(array[j][0]);
	//				}
	//				else
	//					if (array[j][l + 1] > 96 && array[j][l + 1] < 123 && array[j][l]>64 && array[j][l] < 91)
	//					{
	//						array[j][l + 1] = toupper(array[j][l + 1]);
	//						break;
	//					}
	//			}
	//		}
	//		fout << array[j] << ' ';
	//	}
	//	fout << endl;
	//	for (int q = y + 1; q < text.size(); q++)
	//	{
	//		fout << text[q] << endl;;
	//	}
	//	array.clear();
	//	fout.close();
	//	goto menu;
	//}


	//if (a == 3)
	//{
	//	fin.open("111.txt");
	//	if (!fin.is_open()) cout << "Ошибка открытия файла\n";
	//	while (getline(fin, str))
	//	{
	//		new_txt.push_back(str);
	//	}
	//	fin.close();
	//	fout.open("222.txt");
	//	cout << "Введите номер строки, после которой хотите вставить текст из файла " << endl;
	//	do
	//	{
	//		cin >> k;
	//		if (k < 0 || k != floor(k) || k>text.size() - 1)
	//		{
	//			cout << "Введите корректное значение " << endl;
	//		}
	//	} while (k < 0 || k != floor(k) || k>text.size() - 1);
	//	for (i = 0; i <= k; i++) fout << text[i] << endl;
	//	for (i = 0; i < new_txt.size(); i++) fout << new_txt[i] << endl;
	//	for (i = k + 1; i < text.size(); i++) fout << text[i] << endl;
	//	fout.close();
	//	goto menu;
	//}


	return 0;

}