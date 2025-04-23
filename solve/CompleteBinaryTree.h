#pragma once
#include <iostream>
using namespace std;

class CompleteBinaryTree
{
private:
	static constexpr int MaxTree = (1 << 15);
public:

	void BuildTree()
	{
		tree[1] = 1;
		for (int lv = 1; lv < n; ++lv)
		{
			const int stIdx = (1 << lv);
			const int pstIdx = stIdx / 2;
			const int pMid = pstIdx / 2;

			for (int i = 0; i < pMid; ++i) swap(tree[pstIdx + i], tree[stIdx - 1 - i]);

			for (int i = 0; i < pstIdx; ++i)
			{
				const int cIdx = stIdx + i * 2;
				const int pIdx = cIdx / 2;
				const int pOrder = tree[pIdx] - pstIdx;
				const int pOrderInv = pstIdx - pOrder - 1;

				tree[cIdx] = pOrderInv + stIdx;
				tree[cIdx + 1] = pOrderInv + stIdx + pstIdx;
			}
		}
	}

	void Input()
	{
		cin >> n;
	}

	void PrintTree()const
	{
		PrintTree_Internal(1, 0);
	}

private:
	int n;
	int tree[MaxTree]{};

	void PrintTree_Internal(int idx, int lv) const
	{
		cout << tree[idx] << ' ';
		if (lv == n - 1) return;
		PrintTree_Internal(idx * 2, lv + 1);
		PrintTree_Internal(idx * 2 + 1, lv + 1);
	}
};