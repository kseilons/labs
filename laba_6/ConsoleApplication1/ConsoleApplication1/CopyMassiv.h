#pragma once
#include <vector>

template<typename Elem>
std::vector<std::vector<Elem>> CopyMassiv(const std::vector<std::vector<Elem>>& v) {
	std::vector<std::vector<Elem>> result;
	if (v.empty()) {
		return result;
	}
	size_t row = v.size();
	size_t column = v[0].size();
	for (size_t i = 0; i < row; ++i) {
		std::vector<Elem> row;
		for (size_t j = 0; j < column; ++j) {
			row.push_back(v[i][j]);
		}
		result.push_back(row);
	}
	return result;
}