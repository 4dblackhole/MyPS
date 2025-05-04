#pragma once
#include <concepts>
#include "FastPow.h"

using namespace std;

template <std::integral INT>
static INT Combination(INT n, INT m) // nCm
{
	if (m > n / 2) m = n - m;

	INT result = 1;
	for (int i = n; i != m; --i)
	{
		result *= i;
		result /= n - i + 1;
	}
	return result;
}

template <std::integral INT, int FacSize>
class CombinationMod
{
private:
	static constexpr int Size = FacSize;
	INT facMod[Size]{ 1,1,2 };
	INT facModInv[Size];

public:
	CombinationMod()
	{
		for (int i = 1; i < Size; ++i) facMod[i] = (facMod[i - 1] * i) % ModVal;
		facModInv[Size-1] = IntPowMod(facMod[Size-1], ModVal - 2, ModVal);
		for (int i = Size-1; i > 0; --i) facModInv[i - 1] = (facModInv[i] * i) % ModVal;
	}

	INT Get(INT n, INT m) // nCm
	{
		if (m > n / 2) m = n - m;
		if (m < 0) return 0;

		INT result = (facMod[n] * facModInv[m]) % ModVal;
		result = (result * facModInv[n - m]) % ModVal;

		return result;
	}
};