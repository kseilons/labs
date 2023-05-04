#pragma once 
#include <random>
#include <set>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

struct Coord {
	int column;
	int row;
};

std::ostream& operator<< (std::ostream& out, const Coord& coord) {
	out << "["s << coord.row << "]["s << coord.column << "]"s;
	return out;
}


template<typename Integer>
class Search {
public:
	Search() {
		CreateMas();
	}
	void Start() {
		GetQuery();
		LineSearch();
		BinarySearch();
	}

private:

	vector<vector<Integer>> origin_;
	Coord origin_size_;
	set<Integer> split_query_;



	void CreateMas() {
		GetSize();
		FillRandom();
		cout << origin_;
	};

	void GetSize() noexcept {
		do {
			origin_size_ = { GetPositiveNum("введите n:", "Некорректное значение n"), GetPositiveNum("введите m:", "Некорректное значение m") };
			if (origin_size_.row * origin_size_.column <= 100000000) {
				break;
			}
			cout << "Слишком большой массив, максимальный размер массива 100000000 элементов"s << std::endl;
		} while (true);
	}
	void FillRandom() {
		srand(static_cast<unsigned int> (time(NULL)));

		for (size_t i = 0; i < origin_size_.row; ++i) {
			vector<Integer> buffer;
			for (size_t j = 0; j < origin_size_.column; ++j) {
				Integer number = rand() % 200;
				buffer.push_back(number);
			}
			origin_.push_back(buffer);
		}
	}

	void GetQuery() {
		using namespace std::literals;
		std::cout << "Введите последовательность элементов: "s;
		std::string line = ReadLine();

		for (const std::string& elem : SplitIntoWords(line)) {
			if (!CheckIsNum(elem)) {
				std::cout << elem << " - не число" << std::endl;
			}
			else if (split_query_.contains(stoi(elem))) {
				std::cout << elem << " уже есть в запросе" << std::endl;
			}
			else {
				split_query_.insert(stoi(elem));
			}
		}
		std::cout << std::endl;
	}


	void Inicialize(std::map<Integer, std::vector<Coord>>& v) {
		for (Integer elem : split_query_) {
			v[elem];
		}
	}

	void LineSearch() {
		std::map<Integer, std::vector<Coord>> elem_to_coord;
		Inicialize(elem_to_coord);
		for (int row = 0; row < origin_size_.row; row += 2) {
			for (int column = 0; column < origin_size_.column; column++) {
				for (const Integer& query_elem : split_query_) {
					Integer elem = origin_[row][column];
					if (query_elem == elem) {
						elem_to_coord[query_elem].push_back({ column, row });
					}
				}
			}
		}
		PrintLineSearchResult(elem_to_coord);
	}

	void PrintLineSearchResult(const std::map<Integer, std::vector<Coord>>& data) {
		for (auto [elem, v_coords] : data) {
			std::cout << elem << ": "s;
			if (!v_coords.empty()) {
				std::cout << v_coords;
			}
			else {
				std::cout << "No"s;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	void BinarySearch() {
		Binary_Search binary_search(origin_, origin_size_);
		binary_search.Search(split_query_);
	}
	class Binary_Search {
	public:
		friend class Search;
		Binary_Search(const std::vector<std::vector<Integer>>& elems, Coord size) {
			ParseElemsForBinarySearch(elems, size);
			std::sort(for_search_.begin(), for_search_.end());
			cout << "Отсортированный массив для бинарного поиска: " << for_search_ << std::endl;
		}

		void Search(std::set<Integer> split_query) {
			for (const Integer& elem : split_query) {
				SearchElem(elem);
			}
			PrintBinarySearchResult();
		}
	private:
		struct Binary_Info {
			int amount = 0;
			int first_occurrence = 0;
			int last_occurrence = 0;
			int begin_index = 0;
			int end_index = 0;
		};

		std::vector<Integer> for_search_;
		std::map<int, Binary_Info > elem_to_step_;

		void ParseElemsForBinarySearch(std::vector<std::vector<Integer>> elems, Coord size) {
			for (int row = 0; row < size.row; row += 2) {
				for (int column = 0; column < size.column; column++) {
					for_search_.push_back(elems[row][column]);
				}
			}
		}

		struct Binary_Border {
			Binary_Border(int size) {
				high = size - 1;
				middle = high / 2;
			}
			void Up() {
				low = middle + 1;
				middle = (low + high) / 2;
			}
			void Down() {
				high = middle - 1;
				middle = (low + high + 1) / 2;
			}
			bool Stop() {
				return low <= high;
			}

			int low = 0;
			int high = 0;
			int middle = 0;
		};

		void SearchIdentical(Integer elem, int index, Binary_Info& info) {
			++info.amount;
			for (int i = index - 1; i >= 0 && for_search_[i] == elem; i--) {
				++info.amount;
			}
			for (int i = index + 1; i < for_search_.size() && for_search_[i] == elem; i++) {
				++info.amount;
			}
		}

		void SearchElem(Integer elem) {
			Binary_Info info;
			Binary_Border border(for_search_.size());
			while (border.Stop()) {
				++info.first_occurrence;
				if (for_search_[border.middle] == elem) {
					SearchIdentical(elem, border.middle, info);
					elem_to_step_[elem] = info;
					return;
				}
				else if (for_search_[border.middle] > elem) {
					border.Down();
				}
				else {
					border.Up();
				}
			}
			elem_to_step_[elem] = info;
		}
		void PrintBinarySearchResult() {
			for (const auto& [elem, elem_data] : elem_to_step_) {
				std::cout << elem << ": "s;

				if (elem_data.amount == 0) {
					std::cout << "элемента нет в массиве, было выполнено " << elem_data.first_occurrence << " сравнений.";
				}
				else {
					std::cout << "Первое вхождение было найдено за "s << elem_data.first_occurrence << " сравнений. Найдено "
						<< elem_data.amount << " элемент.";
				}
				std::cout << std::endl;
			}
		}
	};
};
