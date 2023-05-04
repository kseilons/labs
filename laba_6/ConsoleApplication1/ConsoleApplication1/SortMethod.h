#pragma once
#include <vector>
#include <unordered_map>
#include "CopyMassiv.h"
#include "write_output_function.h"
#include "SortInfo.h"
#include "log_duration.h"

template<typename Elem>
std::pair<Elem**, size_t> GetWhiteRow(std::vector<Elem>& v, bool FirstWhite) {
	int** result = new int* [v.size() / 2 + 1];
	int res_current = 0;
	for (int j = FirstWhite? 0 : 1; j < v.size(); j+=2) {
		result[res_current++] = &v[j];
	}
	return { result, res_current};
}

template<typename Elem>
std::pair<Elem**, size_t> GetBlackColumnReverse(std::vector<std::vector<Elem>>& v, size_t column) {
	Elem** result = new int* [v.size() / 2 + 1];
	size_t res_current = 0;		
	size_t start = (v.size() - column % 2) % 2? v.size() -1: v.size() >= 2 ? v.size() -2 : 0;
	for (int i = start; i>=0; i-= 2) {
		result[res_current++] = &v[i][column];
	}
	return { result, res_current };
}


template<typename Elem>
SortInfo BableSort(Elem*** v, size_t size) {
	SortInfo info;
	if (size <= 1) {
		return info;
	}
	size_t i, j;
	for (i = 0; i < size - 1; i++) {
		int current_swap = 0;
		for (j = 0; j < size - i - 1; j++) {
			if (*v[0][j] > *v[0][j + 1]) {
				std::swap(*v[0][j], *v[0][j + 1]);
				++current_swap;
			}
			++info.comparisons;
		}
		if (current_swap == 0) {
			break;
		}
		info.permutations = info.permutations + current_swap;
	}
	return info;
}
template<typename Elem>
SortInfo SelectionSort(Elem*** v, size_t size) {
	SortInfo info;
	if (size <= 1) {
		return info;
	}
	size_t i, j, min_idx;
	for (i = 0; i < size - 1; i++)
	{
		min_idx = i;
		for (j = i + 1; j < size; j++)
		{
			if (*v[0][j] < *v[0][min_idx]) {
				min_idx = j;
				
			}
			++info.comparisons;
		}

		if (min_idx != i) {
			std::swap(*v[0][i], *v[0][min_idx]);
			++info.permutations;
		}
	}
	
	return info;
}

template<typename Elem>
SortInfo InsertionSort(Elem*** v, size_t size) {
	SortInfo info;
	if (size <= 1) {
		return info;
	}
	for (size_t i = 1; i < size; i++) {
		size_t j = i;
		while (j > 0) {
			++info.comparisons;
			if (*v[0][j] < *v[0][j-1]) {
				std::swap(*v[0][j - 1], *v[0][j]);
				++info.permutations;
			}
			else {
				break;
			}
			j--;
		}
	}
	return info;
}


template<typename Elem>
SortInfo ShellSort(Elem*** v, size_t size) {
	SortInfo info;

	size_t temp, inc;
	for (inc = size / 2; inc > 0; inc /= 2) {
		for (size_t i = inc; i < size; i++)
		{
			for (int j = i - inc; j >= 0; j -= inc) {
				++info.comparisons;
				if (*v[0][j] > *v[0][j+inc]) {
					++info.permutations;
					std::swap(*v[0][j], *v[0][j + inc]);
				} 
				else {
					break;
				}
			}
		}
	}
	return info;
}


template<typename Elem>
SortInfo QuickSortInner(Elem*** v, int low, int high) {
	SortInfo info;
	int i = low;
	int j = high;
	int pivot_index = (i + j) / 2;
	int pivot = *v[0][pivot_index];

	while (i <= j)
	{
		while (*v[0][i] < pivot) {
			i++;
			++info.comparisons;
		}
		if (pivot_index != i) {
			++info.comparisons;
		}
		while (*v[0][j] > pivot) {
			j--;
			++info.comparisons;
		}
		if (pivot_index != j) {
			++info.comparisons;
		}
		if (i <= j)
		{
			if (*v[0][i] != *v[0][j]) {
				++info.permutations;
				std::swap(*v[0][i], *v[0][j]);
			}
			i++;
			j--;
		}
	}
	if (j > low)
		info = info + QuickSortInner(v, low, j);
	if (i < high)
		info = info + QuickSortInner(v, i, high);
	return info;
}

template<typename Elem>
SortInfo QuickSort(Elem*** v, size_t size) {
	return size <= 1 ? SortInfo{0, 0} : QuickSortInner(v, 0, size-1);
}




template<typename Elem>
SortInfo SortedChess(std::vector<std::vector<Elem>>& v, SortInfo SortFunction(Elem*** v, size_t size)) {
	SortInfo info;
	int row = v.size();
	int column = v[0].size();
	for (int i = 0; i < row; i++) {
		auto [white_row, size] = GetWhiteRow(v[i], i % 2 == 1);
		info = info + SortFunction(&white_row, size);
	}
	for (int j = 0; j < column; j++) {
		auto [black_column, size] = GetBlackColumnReverse(v, j);
		info = info + SortFunction(&black_column, size);
	}

	return info;
}

template<typename Elem>
void SortedPrint(const std::string& name , const std::vector<std::vector<Elem>>& massiv) {
	using namespace std::literals;
	std::cout << name << ":"s << std::endl << massiv;
}

template<typename Elem>
void ÑomparisonSortMethod(std::vector<std::vector<Elem>> v) {
	using namespace std::literals;
	SortedPrint("original array"s, v);
	std::unordered_map<std::string, SortInfo> info;

	auto for_sort_massiv = CopyMassiv(v);
	{
		LOG_DURATION("BubbleSortTime: "s);
		info["Bubble sort"s] = SortedChess(for_sort_massiv, BableSort);
	}
	SortedPrint("Bubble sort"s, for_sort_massiv);

	for_sort_massiv = CopyMassiv(v);
	{
		LOG_DURATION("Selection sort: ");
		info["Selection sort"] = SortedChess(for_sort_massiv, SelectionSort);
	}
	SortedPrint("Selection sort"s, for_sort_massiv);

	for_sort_massiv = CopyMassiv(v);
	{
		LOG_DURATION("Insertion sort: ");
		info["Insertion sort"] = SortedChess(for_sort_massiv, InsertionSort);
	}
	SortedPrint("Insertion sort"s, for_sort_massiv);

	for_sort_massiv = CopyMassiv(v);
	{
		LOG_DURATION("Shell sort: ");
		info["Shell sort"] = SortedChess(for_sort_massiv, ShellSort);
	}
	SortedPrint("Shell sort"s, for_sort_massiv);

	for_sort_massiv = CopyMassiv(v);
	{
		LOG_DURATION("Quick sort: ");
		info["Quick sort"] = SortedChess(for_sort_massiv, QuickSort);
	}
	SortedPrint("Quick sort"s, for_sort_massiv);

	PrintComparisentTable(info);
}