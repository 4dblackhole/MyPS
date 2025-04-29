#pragma once

int GetBitCount(const int& f)
{
	int result = f;
	static constexpr int mask[] = { 0x55555555, 0x33333333, 0x0f0f0f0f, 0x00ff00ff, 0x0000ffff };
	int amp = 1;
	for (const auto& m : mask)
	{
		const int& f1 = result & m;
		const int& f2 = (result >> amp) & m;
		result = f1 + f2;
		amp *= 2;
	}
	return result;
}

using uint64 = unsigned long long;

uint64 GetBitCount(const uint64& f)
{
	int result = f;
	static constexpr uint64 mask[] = { 
		0x5555555555555555,
		0x3333333333333333,
		0x0f0f0f0f0f0f0f0f,
		0x00ff00ff00ff00ff,
		0x0000ffff0000ffff,
		0x00000000ffffffff
	};

	int amp = 1;
	for (const auto& m : mask)
	{
		const int& f1 = result & m;
		const int& f2 = (result >> amp) & m;
		result = f1 + f2;
		amp *= 2;
	}
	return result;
}
