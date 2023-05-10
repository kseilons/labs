#pragma once

#include <Windows.h>
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
	ConsoleColor(Color color) {
		out = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(out, &start_attribute);
		SetColor(color);
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