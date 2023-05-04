#include "Hash_Function.h"
namespace hash {

	int GetHashCode(std::string key)
	{
		double k = 0;
		for (char ch : key) {
			k += abs(ch);
		}

		int N = 13; double A = 0.618033;
		int h = N * fmod(k * A, 23);
		return h;
	}
}