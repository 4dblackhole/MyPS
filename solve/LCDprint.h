#pragma once
#include <vector>
using namespace std;

char board[23][136]{};
void DrawHorizontal(int x, int y, int len)
{
	for (int i = 0; i < len; ++i)
		board[y][x + 1 + i] = '-';
}

void DrawVertical(int x, int y, int len)
{
	for (int i = 0; i < len; ++i)
		board[y + 1 + i][x] = '|';
}

const vector<pair<pair<int, int>, void(*)(int, int, int)>> numInfo[10] =
{
	{ {{0,0}, DrawHorizontal}, {{0,0}, DrawVertical}, {{0,1}, DrawVertical}, {{ 1,0 }, DrawVertical}, {{1,1}, DrawVertical},{{0,2}, DrawHorizontal} },
	{ {{1,0}, DrawVertical}, {{1,1}, DrawVertical} },
	{ {{0,0}, DrawHorizontal}, {{1,0}, DrawVertical}, {{0,1}, DrawHorizontal}, {{ 0,1 }, DrawVertical}, {{0,2}, DrawHorizontal} },
	{ {{0,0}, DrawHorizontal}, {{0,1}, DrawHorizontal}, {{0,2}, DrawHorizontal}, {{ 1,0 }, DrawVertical}, {{1,1}, DrawVertical} },
	{ {{0,0}, DrawVertical}, {{1,0}, DrawVertical}, {{0,1}, DrawHorizontal}, {{1,1}, DrawVertical} },

	{ {{0,0}, DrawHorizontal}, {{0,0}, DrawVertical}, {{0,1}, DrawHorizontal}, {{1,1}, DrawVertical}, {{0,2}, DrawHorizontal} },
	{ {{0,0}, DrawHorizontal}, {{0,0}, DrawVertical}, {{0,1}, DrawHorizontal}, {{0,1}, DrawVertical}, {{0,2}, DrawHorizontal}, {{1,1}, DrawVertical} },
	{ {{0,0}, DrawHorizontal}, {{1,0}, DrawVertical}, {{1,1}, DrawVertical} },
	{ {{0,0}, DrawHorizontal}, {{0,0}, DrawVertical}, {{0,1}, DrawHorizontal}, {{0,1}, DrawVertical}, {{0,2}, DrawHorizontal}, {{1,0}, DrawVertical}, {{1,1}, DrawVertical} },
	{ {{0,0}, DrawHorizontal}, {{0,0}, DrawVertical}, {{0,1}, DrawHorizontal}, {{0,2}, DrawHorizontal}, {{1,0}, DrawVertical}, {{1,1}, DrawVertical} }
};
