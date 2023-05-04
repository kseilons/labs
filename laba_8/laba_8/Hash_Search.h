#pragma once
#include <string>
#include <vector>
#include "Data.h"
#include "FileClient.h"
#include "ConsoleRead.h"


class Hash_Search
{
public:
	Hash_Search();

	void Start();
	void Search(const Data&, const int& );
private:
	std::vector<Data> data_;
	std::vector<int> hash_fulls;
	std::vector<int> hash_initials;
	void Hashing();
	struct Result {
		Data data;
		int hash;
		bool IsCoincid;
	};
	void PrintSearchResult (std::vector<Result>);
	Data GetRequest();
};

