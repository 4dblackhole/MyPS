#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int n;
int arr[200001]; //diff
int tree[800001]; //sum of total diff

constexpr int Alpha = 26;

static void UpdateTree(int qI, int left, int right, int idx, int val)
{
	if (qI < left || right < qI) return;
	if (left == right)
	{
		tree[idx] = val;
		return;
	}
	const int tL = idx * 2 + 1;
	const int tR = idx * 2 + 2;

	const int mid = (left + right) / 2;
	UpdateTree(qI, left, mid, tL, val);
	UpdateTree(qI, mid + 1, right, tR, val);
	tree[idx] = tree[tL] + tree[tR];
}

static int GetTree(int qL, int qR, int left, int right, int idx)
{
	if (right < qL || qR < left) return 0;
	if (qL <= left && right <= qR) return tree[idx];

	const int tL = idx * 2 + 1;
	const int tR = idx * 2 + 2;

	const int mid = (left + right) / 2;
	const int treeLeft = GetTree(qL, qR, left, mid, tL);
	const int treeRight = GetTree(qL, qR, mid + 1, right, tR);
	return treeLeft + treeRight;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	string str;
	int q;
	cin >> n >> q >> str;
	
	arr[0] = 1;
	for (int i = 1; i < n; ++i) arr[i] = ((str[i] - str[i - 1]) + Alpha) % Alpha;

	for (int i = 0; i < n; ++i)
	{
		if (arr[i] != 0) UpdateTree(i, 0, n - 1, 0, 1);
	}

	vector<int> result;
	while (q--)
	{
		int type, a, b;
		cin >> type >> a >> b;
		--a, --b;
		if (type == 1)
		{
			const int val = 1 + GetTree(0, b, 0, n - 1, 0) - GetTree(0, a, 0, n - 1, 0);
			result.emplace_back(val);
		}
		else
		{
			if (a != 0)
			{
				arr[a] = (arr[a] + 1) % Alpha;
				UpdateTree(a, 0, n - 1, 0, arr[a] != 0);
			}
			if (b != n - 1)
			{
				const int nb = b + 1;
				arr[nb]= (arr[nb] + 25) % Alpha;
				UpdateTree(nb, 0, n - 1, 0, arr[nb] != 0);
			}
		}
	}
	for (int i = 0; i < result.size(); ++i)cout << result[i] << '\n';
	return 0;
}