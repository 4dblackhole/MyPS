#pragma once

using int64 = long long;
static constexpr int Size = 1000001;
static constexpr int ModVal = 1000000007;

int arr[Size];
int64 tree[4 * Size];

const void BuildTree(int left, int right, int idx)
{
	if (left == right)
	{
		tree[idx] = arr[left];
		return;
	}
	const int tL = idx * 2 + 1;
	const int tR = idx * 2 + 2;

	const int mid = (left + right) / 2;
	BuildTree(left, mid, tL);
	BuildTree(mid + 1, right, tR);
	tree[idx] = (tree[tL] * tree[tR]) % ModVal;
}

const void UpdateTree(int nIdx, int left, int right, int idx)
{
	if (nIdx < left || right < nIdx) return;
	if (left == right)
	{
		tree[idx] = arr[left];
		return;
	}
	const int tL = idx * 2 + 1;
	const int tR = idx * 2 + 2;

	const int mid = (left + right) / 2;
	UpdateTree(nIdx, left, mid, tL);
	UpdateTree(nIdx, mid + 1, right, tR);
	tree[idx] = (tree[tL]* tree[tR]) % ModVal;
}

const int64 GetTree(int qL, int qR, int left, int right, int idx)
{
	if (right < qL || qR < left) return 1;
	if (qL <= left && right <= qR) return tree[idx];

	const int lIdx = idx * 2 + 1;
	const int rIdx = idx * 2 + 2;

	const int mid = (left + right) / 2;
	const int64& LeftTree = GetTree(qL, qR, left, mid, lIdx);
	const int64& RightTree = GetTree(qL, qR, mid + 1, right, rIdx);
	return (LeftTree * RightTree) % ModVal;
}
