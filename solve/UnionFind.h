#pragma once

constexpr int Size = 30001;
int parent[Size];

int FindParent(int idx)
{
	return (parent[idx] == idx) ? idx : parent[idx] = FindParent(parent[idx]);
}

void UnionParent(int a, int b)
{
	a = FindParent(a);
	b = FindParent(b);
	parent[b] = a;
}
void UnionParent2(int a, int b)
{
	a = FindParent(a);
	b = FindParent(b);
	if (a == b)return;
	a < b ? parent[b] = a : parent[a] = b;
}