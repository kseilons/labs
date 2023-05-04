#include "Data.h"

std::ostream& operator<<(std::ostream& out, Data data) {
	out << data.surname << ' ' << data.name << ' ' << data.patronymic;
	return out;
}

