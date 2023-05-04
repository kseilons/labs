#include "Hash_Search.h"
#include "FileClient.h"
#include "Hash_Function.h"
#include <string>
#include <vector>

#include "Data.h"


Hash_Search::Hash_Search() {
	FileClient file;
	data_ = file.Read();

	Hashing();
	for (auto& elem : data_) {
		std::cout << elem << std::endl;
	}
}

void Hash_Search::Hashing() {
	for (Data& elem : data_) {
		std::string for_hash = elem.patronymic + elem.name + elem.surname;
		hash_fulls.push_back(hash::GetHashCode(for_hash));

		std::string for_initial_hash;
		for_initial_hash = elem.patronymic[0];
		for_initial_hash += elem.name[0];
		for_initial_hash += elem.surname;
		hash_initials.push_back(hash::GetHashCode(for_initial_hash));
	}
}

void Hash_Search::Search(const Data& request, const int& hash) {
	std::vector<Result> result;
	for (size_t i = 0; i < hash_fulls.size(); i++) {
		if (hash == hash_fulls[i]) {
			if (request.name == data_[i].name
				&& request.patronymic == data_[i].patronymic
				&& request.surname == data_[i].surname) {
				result.push_back(Result{ data_[i], hash, false });
			}
			else {
				result.push_back(Result{ data_[i], hash, true });
			}
		}
	}
	for (size_t i = 0; i < hash_initials.size(); i++) {
		if (hash == hash_initials[i]) {
			if (request.name[0] == data_[i].name[0] 
				&& request.patronymic[0] == data_[i].patronymic[0]
				&& request.surname == data_[i].surname) {
				result.push_back(Result{data_[i], hash, false });
			}
			else {
				result.push_back(Result{ data_[i], hash, true });
			}
		}
	}
	PrintSearchResult(result);
}


void Hash_Search::PrintSearchResult(std::vector<Result> date) {
	using namespace std;
	cout << endl;
	if (date.size()) {
		cout << "Вот что мне удалось найти: "s << endl;
		for (const auto res : date) {
			if (res.IsCoincid) {
				cout << "Произошла коллизия :"s;
			}
			else {
				cout << "искомый элемент: "s;
			}
			cout << res.data << " "s << res.hash << endl;
		}
	}
	else {
		cout << "В базе данных нет данных по этому человеку";
	}
	cout << endl;
}

void Hash_Search::Start() {
	Data request = GetRequest();
	int hash = hash::GetHashCode(request.patronymic + request.name + request.surname);
	Search(request, hash);
}


Data Hash_Search::GetRequest() {
	do {
		Data request;
		std::cout << std::endl << "Введите ФИО полностью, или через инициалы: ";
		request.surname = Console::GetWord();
		auto word_red = Console::GetWordReduc();
		if (word_red.size() == 1) {
			request.name = word_red.front();
			word_red = Console::GetWordReduc();
			if (word_red.size() == 1) {
				request.patronymic = word_red.back();
			}
			else {
				std::cout << "Вы ввели данные не в верном формате. Пожалуйста используйте один из слудующих формата ввода: Фамилия Имя Отчество, Фимилия И.О., Фамилия И О" << std::endl;
				std::string c;
				std::getline(std::cin, c);
				continue;
			}

		}
		else if (word_red.size() == 2) {
			request.name = word_red.front();
			request.patronymic = word_red.back();
		}
		else {
			std::cout << "Вы ввели данные не в верном формате. Пожалуйста используйте один из слудующих формата ввода: Фамилия Имя Отчество, Фимилия И.О., Фамилия И О" << std::endl;
			std::string c;
			std::getline(std::cin, c);
			continue;
		}
		std::transform(request.surname.begin(), request.surname.end(), request.surname.begin(), tolower);
		std::transform(request.name.begin(), request.name.end(), request.name.begin(), tolower);
		std::transform(request.patronymic.begin(), request.patronymic.end(), request.patronymic.begin(), tolower);
		return request;
	} while (true);
	
}