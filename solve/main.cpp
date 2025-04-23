#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class MaxFlow
{
private:
	static constexpr int MaxPipe = 52;
	static constexpr int MaxVal = 77777777;
	static constexpr int NoVal = -1;
public:
	static inline int GetIdx(char c)
	{
		if (isupper(c))return c - 'A';
		if (islower(c))return c - 'a' + 26;
		return MaxFlow::MaxPipe;
	}

	int GetFlow(int a, int b)
	{
		int result = 0;
		int flow[MaxPipe][MaxPipe]{};
		while (true)
		{
			vector<int> parent(MaxFlow::MaxPipe, MaxFlow::NoVal);
			queue<int> q;
			parent[a] = a;
			q.emplace(a);
			while (!q.empty() && parent[b] == MaxFlow::NoVal)
			{
				const int cIdx = q.front();
				q.pop();

				for (int nIdx = 0; nIdx < MaxFlow::MaxPipe; ++nIdx)
				{
					if (capa[cIdx][nIdx] - flow[cIdx][nIdx] > 0 && parent[nIdx] == MaxFlow::NoVal)
					{
						q.emplace(nIdx);
						parent[nIdx] = cIdx;
					}
				}
			}

			// Not Found
			if (parent[b] == MaxFlow::NoVal) break;

			int maxFlow = MaxFlow::MaxVal;
			for (int p = b; p != a; p = parent[p])
				maxFlow = min(maxFlow, capa[parent[p]][p] - flow[parent[p]][p]);

			for (int p = b; p != a; p = parent[p])
			{
				flow[parent[p]][p] += maxFlow;
				flow[p][parent[p]] -= maxFlow;
			}
			result += maxFlow;
		}
		return result;
	}

	void Input()
	{
		for (auto& cc : capa)for (int& cap : cc) cap = 0;
		int n;
		cin >> n;

		while (n--)
		{
			char a, b;
			int c;
			cin >> a >> b >> c;

			const int& aI = GetIdx(a);
			const int& bI = GetIdx(b);
			capa[aI][bI] += c;
			capa[bI][aI] += c;
		}

	}
private:
	int capa[MaxFlow::MaxPipe][MaxFlow::MaxPipe]{};
};

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	MaxFlow mf;
	mf.Input();

	cout << mf.GetFlow(MaxFlow::GetIdx('A'), MaxFlow::GetIdx('Z'));

	return 0;
}
