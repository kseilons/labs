#pragma once
#include <utility>

struct Position {
	size_t row = 0;
	size_t column = 0;
	void operator=(std::pair<size_t, size_t> date);	

};
bool operator>(Position rhs, Position lhs);
bool operator==(Position rhs, Position lhs);