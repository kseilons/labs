#pragma once

struct SortInfo {
	SortInfo() = default;
	SortInfo(size_t n, size_t m) : comparisons(n), permutations(m)
	{
	}
	size_t comparisons = 0;
	size_t permutations = 0;
};

SortInfo operator+ (SortInfo left, SortInfo right) {
	return SortInfo{ left.comparisons + right.comparisons, left.permutations + right.permutations };
}