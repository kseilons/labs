#include "Position.h"

void Position::operator=(std::pair<size_t, size_t> date)
{
	row = date.first;
	column = date.second;
}

bool operator>(Position rhs, Position lhs) {
	return rhs.row > lhs.row || rhs.row == lhs.row && rhs.column > lhs.column;
}
bool operator==(Position rhs, Position lhs)
{
	return rhs.column == lhs.column && rhs.row == lhs.row;
}