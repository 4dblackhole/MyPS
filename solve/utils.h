#pragma once
#include <iostream>
#include <array>
#include <cmath>
#include <vector>
#include <unordered_map>

using namespace std;
using uint = unsigned int;
using int64 = long long;
using uint64 = unsigned long long;
using float128 = long double;

#define STRWRITE(str) str, sizeof(str)/sizeof(str[0]) - 1

template <typename T>
static inline T CrossPt3(const pair<T, T> from, const pair<T, T> to1, const pair<T, T> to2)
{
	const T& x1 = from.first;
	const T& y1 = from.second;

	const T& x2 = to1.first;
	const T& y2 = to1.second;

	const T& x3 = to2.first;
	const T& y3 = to2.second;

	return (x1 * y2 + x2 * y3 + x3 * y1 - x2 * y1 - x3 * y2 - x1 * y3);
}

template <typename T>
static inline T CCW(const pair<T, T> from, const pair<T, T> to1, const pair<T, T> to2)
{
	if (CrossPt3(from, to1, to2) > 0)return 1;
	if (CrossPt3(from, to1, to2) < 0)return -1;
	return 0;
}

bool OrderedLineCrossCheck(const pair<int64, int64>(&pt)[4])
{
	const int64 val1 = CCW(pt[0], pt[1], pt[2]);
	const int64 val2 = CCW(pt[0], pt[1], pt[3]);
	const int64 val3 = CCW(pt[2], pt[3], pt[0]);
	const int64 val4 = CCW(pt[2], pt[3], pt[1]);

	const int64 ccw1 = val1 * val2;
	const int64 ccw2 = val3 * val4;

	if (ccw1 > 0 || ccw2 > 0) return false;
	if (ccw1 != 0 || ccw2 != 0) return true;
	if (pt[0] <= pt[3] && pt[2] <= pt[1]) return true;
	return false;
}

using Line = pair<pair<int64, int64>, pair<int64, int64>>;
bool OrderedLineCrossCheck(const Line(&l)[2])
{
	return OrderedLineCrossCheck({ l[0].first,l[0].second,l[1].first,l[1].second });
}
bool GetIntersectionPoint(const pair<int64, int64>(&pt)[4], pair<float128, float128>& result)
{
	const int64& x1 = pt[0].first;
	const int64& x2 = pt[1].first;
	const int64& x3 = pt[2].first;
	const int64& x4 = pt[3].first;

	const int64& y1 = pt[0].second;
	const int64& y2 = pt[1].second;
	const int64& y3 = pt[2].second;
	const int64& y4 = pt[3].second;

	const int64 a = y2 - y1;
	const int64 b = x1 - x2;
	const int64 c = y4 - y3;
	const int64 d = x3 - x4;
	const int64 x = x1 * y2 - x2 * y1;
	const int64 y = x3 * y4 - x4 * y3;

	const int64 det = a * d - b * c;
	if (det == 0)
	{
		if (pt[1] == pt[2] && pt[0] <= pt[2])
		{
			result = pt[1];
			return true;
		}
		if (pt[0] == pt[3] && pt[2] <= pt[0])
		{
			result = pt[0];
			return true;
		}
		return false;
	}
	const int64 rxNominator = x * d - y * b;
	const int64 ryNominator = y * a - x * c;
	result = { float128(rxNominator) / float128(det), float128(ryNominator) / float128(det) };
	return true;
}

template <typename T>
static inline T DotPt3(const pair<T, T> from, const pair<T, T> to1, const pair<T, T> to2)
{
	const pair<T, T>& v1 = { to1.first - from.first, to1.second - from.second };
	const pair<T, T>& v2 = { to2.first - from.first, to2.second - from.second };
	return v1.first * v2.first + v1.second * v2.second;
}

static inline bool IsInclude(const int& sourceFlag, const int& findFlag) //src>=find
{
	int f1 = sourceFlag;
	int f2 = findFlag;
	while (f1 || f2)
	{
		if ((f1 & 1) < (f2 & 1)) return false;
		f1 >>= 1;
		f2 >>= 1;
	}
	return true;
}
static inline void FlagOn(int& f, char c)
{
	const int& flagOn = c - 'a';
	f |= 1 << flagOn;
}

static inline void FlagOff(int& f, char c)
{
	const int& flagOff = c - 'a';
	f &= (~(1 << flagOff));
}

static inline bool IsFlagOn(const int& f, char c)
{
	const int& flagIdx = c - 'a';
	return (f & (1 << flagIdx)) != 0;
}
int GetBitCount(const int& f)
{
	int result = f;
	static constexpr int mask[] = { 0x55555555,0x33333333,0x0f0f0f0f,0x00ff00ff,0x0000ffff };
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

/*
위상정렬
진입차수를 계산하고 진입차수가 0인 노드에서 시작해서 순회돌면서 진입차수 1씩 빼주기
사이클이면 빼도 0이안돼서 출력이안됨
*/

unordered_map<uint64, uint64> fibo;

uint64 GetFivoMod(uint64 idx, uint64 mod)
{
	if (idx == 0)return 0;
	if (idx <= 2)return 1;
	if (fibo.find(idx) != fibo.cend()) return fibo[idx];

	if (idx % 2 == 1)
	{
		fibo[idx]
			=
			(
				((GetFivoMod(idx / 2 + 1, mod) * GetFivoMod(idx / 2 + 1, mod)) % mod)
				+
				((GetFivoMod(idx / 2, mod) * GetFivoMod(idx / 2, mod)) % mod)
				) % mod;
	}
	else
	{
		fibo[idx]
			=
			(
				((GetFivoMod(idx / 2 + 1, mod) * GetFivoMod(idx / 2, mod)) % mod)
				+
				((GetFivoMod(idx / 2, mod) * GetFivoMod(idx / 2 - 1, mod)) % mod)
				) % mod;
	}
	return fibo[idx];
}

int64 ExGCD(int64 a, int64 b, int64& m1, int64& m2)
{
	if (b == 0)
	{
		m1 = 1, m2 = 0;
		return a;
	}

	int64 t = ExGCD(b, a % b, m2, m1);
	m2 -= (a / b) * m1;

	return t;
}

template<integral Int>
Int IntSqrt(Int val)
{
	Int r = std::sqrt(val);
	if ((r * r) < val)++r;
	return r;
}

static int Combination(int n, int m) // nCm
{
	if (m > n / 2) m = n - m;

	int result = 1;
	for (int i = n; i != m; --i)
	{
		result *= i;
		result /= n - i + 1;
	}
	return result;
}

static void dfs(int maxnum, int currentDepth, int maxDepth, array<int, 8>& arr)
{
	if (currentDepth == maxDepth)
	{
		for (int i = 0; i < currentDepth; ++i)cout << arr[i] << ' ';
		cout << '\n';
		return;
	}
	for (int i = 0; i < maxnum; ++i)
	{
		arr[currentDepth] = i + 1;
		dfs(maxnum, currentDepth + 1, maxDepth, arr);

	}
}

static void RC(int num, int maxnum, int size, std::vector<int> list)
{
	list.emplace_back(num);
	if (size == 0)
	{
		for (const int& it : list) std::cout << it << " ";
		std::cout << '\n';
		return;
	}

	for (int i = num + 1; i <= maxnum; ++i)
	{
		RC(i, maxnum, size - 1, list);
	}
}

static uint64 PowMod(uint64 val, uint64 pow, uint64 mod)
{
	uint64 result = 1u;
	uint64 rate = val % mod;
	while (pow)
	{
		if (pow & 0b1) result = (result * rate) % mod;
		rate = (rate * rate) % mod;
		pow >>= 1;
	}
	return result;
}

void InitOneCount(uint64* ptr, int len)
{
	uint64 ap = 1;
	for (int i = 1; i < len; ++i)
	{
		ptr[i] = ptr[i - 1] * 2 + ap;
		ap *= 2;
	}
}

uint64 GetOne(uint64* ptr, int len, uint64 val)
{
	uint64 result = 0;
	for (int i = len - 1; i >= 0; --i)
	{
		uint64 twoPow = 1ull << i;
		if ((val & twoPow) != 0)
		{
			val -= twoPow;
			result += ptr[i] + val + 1;
		}
	}

	return result;
}
namespace MyMatrix
{
	class Matrix
	{
	public:
		static constexpr uint MaxSize = 5;
		Matrix(const uint lv = MaxSize) : size(lv) {}
		uint val[MaxSize][MaxSize]{};
		uint size;

		Matrix operator%(const uint& modval) const
		{
			const uint& matSize = this->size;
			Matrix result(matSize);
			for (int y = 0; y < matSize; ++y)
			{
				for (int x = 0; x < matSize; ++x)
				{
					result.val[y][x] = this->val[y][x] % modval;
				}
			}
			return result;
		}

		Matrix operator*(const Matrix& mat) const
		{
			const uint& matSize = this->size;
			Matrix result(matSize);
			for (int y = 0; y < matSize; ++y)
			{
				for (int x = 0; x < matSize; ++x)
				{
					for (int idx = 0; idx < matSize; ++idx)
					{
						result.val[y][x] += this->val[y][idx] * mat.val[idx][x];
					}
				}
			}
			return result;

		}

		void PrintMatrix() const
		{
			for (int y = 0; y < size; ++y)
			{
				for (int x = 0; x < size; ++x)
				{
					std::cout << val[y][x] << ' ';
				}
				std::cout << '\n';
			}
		}
	};


	static Matrix MultiMod(const Matrix& mat1, const Matrix& mat2, uint64 mod)
	{
		const uint64& matSize = mat1.size;
		Matrix result(matSize);
		for (int y = 0; y < matSize; ++y)
		{
			for (int x = 0; x < matSize; ++x)
			{
				for (int idx = 0; idx < matSize; ++idx)
				{
					result.val[y][x] = (result.val[y][x] + mat1.val[y][idx] * mat2.val[idx][x]) % mod;
				}
			}
		}
		return result;

	}

	static Matrix MatrixPowMod(const Matrix& m, uint64 pow, uint64 mod)
	{
		// I Matrix initialization
		Matrix result(m.size);
		for (int idx = 0; idx < m.size; ++idx) result.val[idx][idx] = 1;

		Matrix rate = m % mod;
		while (pow)
		{
			if (pow & 0b1) result = (result * rate) % mod;
			rate = (rate * rate) % mod;
			pow >>= 1;
		}
		return result;
	}
};

