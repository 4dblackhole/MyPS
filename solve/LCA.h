#pragma once
#include <algorithm>
using namespace std;

class LCA
{
private:
	static constexpr int NoParent = -1;
	static constexpr int Size = 50001;
	struct Node
	{
		int p = NoParent;
		int lv;
	};

	Node tree[Size];
public:
	int GetLCA(int a, int b)
	{
		int lvA = tree[a].lv;
		int lvB = tree[b].lv;
		if (lvA < lvB) //A is lower
		{
			swap(a, b);
			swap(lvA, lvB);
		}
		while (lvA != lvB)
		{
			a = tree[a].p;
			lvA = tree[a].lv;
		}
		while (a != b)
		{
			a = tree[a].p;
			b = tree[b].p;
		}
		return a;
	}
};