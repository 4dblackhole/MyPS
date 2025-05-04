#pragma once
#include <vector>
#include <concepts>
using namespace std;

#include "utils.h"

template<std::integral Int>
vector<Int> GetPrime(Int n)
{
	vector<bool>primeFlag;
	primeFlag.resize(n + 1, true);
	primeFlag[0] = primeFlag[1] = false;
	const Int sqrtN = IntSqrt(n);
	for (Int d = 2; d <= sqrtN; ++d)
	{
		if (!primeFlag[d]) continue;
		for (Int i = 2; ; ++i)
		{
			const Int mult = i * d;
			if (mult > n) break;
			primeFlag[mult] = false;
		}
	}

	vector<Int>result;
	result.reserve(sqrtN);
	for (Int i = 2; i <= n; ++i)if (primeFlag[i])result.emplace_back(i);
	return result;
}
