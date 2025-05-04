#pragma once
#include <concepts>

template <std::integral INT>
static INT IntPowMod(INT val, INT pow, INT mod)
{
	INT result = 1u;
	INT rate = val % mod;
	while (pow)
	{
		if (pow & 0b1) result = (result * rate) % mod;
		rate = (rate * rate) % mod;
		pow >>= 1;
	}
	return result;
}

template <std::integral INT>
static INT IntPow(INT val, INT pow)
{
	INT result = 1u;
	INT rate = val;
	while (pow)
	{
		if (pow & 0b1) result = (result * rate);
		rate = (rate * rate);
		pow >>= 1;
	}
	return result;
}
