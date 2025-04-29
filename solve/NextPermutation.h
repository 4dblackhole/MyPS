#pragma once
#include <algorithm>

bool NextPermutation(int* const arr, int n)
{
	int i = n - 1;
	while (i > 0 && arr[i - 1] > arr[i]) --i;
	if (i == 0) return false;

	int ptr = n - 1;
	while (arr[ptr] < arr[i - 1]) --ptr;
	std::swap(arr[i - 1], arr[ptr]);
	std::reverse(arr + i, arr + n);
}

bool NextPermutation(int* const arr, int* const arrEnd)
{
	int n = arrEnd - arr;
	int i = n - 1;
	while (i > 0 && arr[i - 1] > arr[i]) --i;
	if (i == 0) return false;

	int ptr = n - 1;
	while (arr[ptr] < arr[i - 1]) --ptr;
	std::swap(arr[i - 1], arr[ptr]);
	std::reverse(arr + i, arr + n);
}