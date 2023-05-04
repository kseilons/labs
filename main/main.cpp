#define _USE_MATH_DEFINES 
#include <iostream> 

#include <Windows.h> 
#include <iomanip> 

#include "Data.h"
#include "ReadFunc.h"
#include "round.h"

typedef void(*calcFunc)(SafonovInfoType info, void*, ...);
typedef const char* (*functionName)();


using namespace std;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
ColorSaf MyColor = { 12,3 };

int openDll(HINSTANCE& dll, calcFunc& calculator, functionName& fName) {
	if (dll == nullptr) {
		cout << "Библиотека не была открыта.\n"s;
		system("pause");
		return 1;
	}
	calculator = (calcFunc)GetProcAddress(dll, "calculator");
	if (calculator == nullptr) {
		cout << "Функция \"calculator\" не обнаружена в библиотеке."s << endl;
		system("pause");
		return 1;
	}

	fName = (functionName)GetProcAddress(dll, "FName");

	if (fName == nullptr) {
		cout << "Функция \"FName\" не обнаружена в библиотеке."s << endl;
		system("pause");
		return 1;
	}

	cout << endl;
	return 0;
}

void SetColor(ColorSaf color) {
	SetConsoleTextAttribute(h, (WORD)((color.bgSaf << 4) | color.textSaf));
}

void SetupDefaultColor(CONSOLE_SCREEN_BUFFER_INFO defaultColor) {
	SetConsoleTextAttribute(h, defaultColor.wAttributes);
}

namespace Drow {
	void DrowLine(SafonovInfoType infoTable, ColorSaf color, ...) {
		SetColor(color);
		cout << string(100, '-') << endl;
		if (infoTable == Table1Saf) {
			va_list arguments;
			va_start(arguments, color);
			int numberLine = va_arg(arguments, int);
			double x = va_arg(arguments, double);
			double f_row = va_arg(arguments, double);
			double f_math = va_arg(arguments, double);
			double delta = va_arg(arguments, double);
			va_end(arguments);

			cout << "| " << left << setw(7)  << numberLine << " | ";
			if (x != 0 && (double_round(x) == 0 || abs(x) > 99999)) {
				cout << left << scientific << setw(21)  << x << " | ";
			}
			else {
				cout << left << fixed  << setprecision(7) << setw(21) << x << " | ";
			}
			if (f_row != 0 && (double_round(f_row) == 0 || abs(f_row) > 99999)) {
				cout << left << scientific << setw(19) << f_row << " | ";
			}
			else {
				cout << left << fixed << setprecision(7)<< setw(19)<< f_row << " | ";
			}
			if (f_math != 0 && (double_round(f_math) == 0 || abs(f_math) > 99999)) {
				cout << left << scientific << setw(19) << f_math << " | ";
			}
			else {
				cout << left << fixed << setprecision(7) << setw(19) << f_math << " | ";
			}
			if (delta != 0 && (double_round(delta) == 0 || delta > 99999)) {
				cout << left << scientific << setw(18) << delta << " |\n";
			}
			else {
				cout << left << fixed << setprecision(7)<< setw(18)<< delta << " |\n";
			}
		}
		else if (infoTable == Table2Saf) {
			va_list arguments;
			va_start(arguments, color);
			int numberLine = va_arg(arguments, int);

			double tb_epsilon = va_arg(arguments, double);
			double f_row = va_arg(arguments, double);
			double f_math = va_arg(arguments, double);
			double delta = va_arg(arguments, double);
			va_end(arguments);
			SetColor(color);
			cout << "| " << setw(7) << left << numberLine << " | " 
				<< setw(21) << left << tb_epsilon << " | ";

			if (f_row != 0 && (double_round(f_row) == 0 || f_row > 99999)) {
				cout << left << scientific << setw(19)<< f_row << " | ";
			}
			else {
				cout << left << fixed << setprecision(6) << setw(19) << f_row << " | ";
			}
			if (f_math != 0 && (double_round(f_math) == 0 || f_math > 99999)) {
				cout << left << scientific << setw(19) << f_math << " | ";
			}
			else {
				cout << left << fixed << setprecision(6) << setw(19) << f_math << " | ";
			}
			if (delta != 0 && (double_round(delta) == 0 || delta > 99999)) {
				cout << left << scientific << setw(18) << delta << " |\n";
			}
			else {
				cout << left << fixed << setprecision(6) << setw(18) << delta << " |\n";
			}
		}
		else if (infoTable == ErrorSaf) {
			va_list arguments;
			va_start(arguments, color);
			int numberLine = va_arg(arguments, int);
			double arg = va_arg(arguments, double);
			va_end(arguments);
			SetColor(color);
			cout << "| " << setw(7) << left << numberLine << " | ";
			if (arg != 0 && (double_round(arg) == 0 || arg > 99999)) {
				cout << left << scientific << setw(21)<< arg;
			}
			else {
				cout << left << fixed << setprecision(7) << setw(21) << arg;
			}
			cout << " |                   ошибка вычисления функции                    |\n";
		}
	}


	void DrowUpTable(string funcName) {
		string myFName = funcName + "_my(x)";
		funcName += "(x)";
		cout << "\nТаблица 1.\n";
		SetColor(MyColor);
		cout << string(100, '-') << endl;
		cout << "|    №    |           x           | " << left << setw(19) << myFName << " | " << left << setw(19) << funcName << " |          del       |\n";
	
	}

	void DrowUpTableIdeal(string funcName) {

		string myFName = funcName + "_my(x_ideal)";
		cout << endl;
		cout << "\nТаблица 2.\n";
		funcName += "(x_ideal)";
		SetColor(MyColor);
		cout << string(100, '-') << endl;
		cout << "|    №    |          eps          | " << left << setw(19) << myFName << " | " << left << setw(19) << funcName << " |          del       |\n";
	}

	void DrowDownTable(CONSOLE_SCREEN_BUFFER_INFO startColor) {
		SetColor(MyColor);
		cout << string(100, '-');
		SetupDefaultColor(startColor);
		cout << endl << endl;
	}
}

int main() {

	setlocale(LC_CTYPE, "Russian");

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO startColor;
	GetConsoleScreenBufferInfo(h, &startColor);

	HINSTANCE dll = LoadLibraryA("Safonov.dll");

	calcFunc calculator;
	functionName fName;
	if (openDll(dll, calculator, fName)) {
		return 1;
	}
	


	double x_start, x_end, x_del, tb_epsilon, a, x_ideal;
	Read::ReadlineInterval(tb_epsilon, x_start, x_end, x_del, a);


	string funcName = fName();
	Drow::DrowUpTable(funcName);
	
	calculator(Table1Saf, Drow::DrowLine, x_start, x_end, x_del, tb_epsilon, a);
	Drow::DrowDownTable(startColor);
	
	x_ideal = Read::GetNum("Введите x_ideal:");

	Drow::DrowUpTableIdeal(funcName);
	calculator(Table2Saf, Drow::DrowLine, x_ideal, a);
	Drow::DrowDownTable(startColor);
	system("pause");
	return 0;
}