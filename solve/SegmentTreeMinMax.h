#pragma once
#include <iostream>
using namespace std;
class SegmentTreeMinMax
{
private:
	static constexpr int MaxVal = 1000000007;
	static constexpr int MinVal = -MaxVal;

	static constexpr int Size = 100001;
	struct Node
	{
		int mn, mx;
	};

	int arr[Size];
	Node tree[4 * Size];
public:
	const Node& BuildTree(int left, int right, int idx)
	{
		if (left == right)
		{
			tree[idx] = { arr[left], arr[left] };
			return tree[idx];
		}
		const int lIdx = idx * 2 + 1;
		const int rIdx = idx * 2 + 2;

		const int mid = (left + right) / 2;
		const Node& LeftTree = BuildTree(left, mid, lIdx);
		const Node& RightTree = BuildTree(mid + 1, right, rIdx);
		tree[idx].mn = min(LeftTree.mn, RightTree.mn);
		tree[idx].mx = max(LeftTree.mx, RightTree.mx);
		return tree[idx];
	}

	const Node GetTree(int qL, int qR, int left, int right, int idx)
	{
		if (right < qL || qR < left) return { MaxVal, MinVal };
		if (qL <= left && right <= qR) return tree[idx];

		const int lIdx = idx * 2 + 1;
		const int rIdx = idx * 2 + 2;

		const int mid = (left + right) / 2;
		const Node& LeftTree = GetTree(qL, qR, left, mid, lIdx);
		const Node& RightTree = GetTree(qL, qR, mid + 1, right, rIdx);
		const int& mn = min(LeftTree.mn, RightTree.mn);
		const int& mx = max(LeftTree.mx, RightTree.mx);
		return { mn, mx };
	}

	void Input()
	{
		int n;
		cin >> n;
		for (int i = 1; i <= n; ++i) cin >> arr[i];
		BuildTree(1, n, 0);
	}
};
