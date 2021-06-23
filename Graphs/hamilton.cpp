include <iostream>
#include <vector>
#include <stack>
using namespace std;
#define SIZE 100

void graph(int x, int y, int a[SIZE][SIZE], int S, vector<vector<int>>& v)
{
	if (x > 1 && y > 0)
		v[a[x][y]].push_back(a[x - 2][y - 1]);
	if (x > 1 && y < S - 1)
		v[a[x][y]].push_back(a[x - 2][y + 1]);
	if (x > 0 && y > 1)
		v[a[x][y]].push_back(a[x - 1][y - 2]);
	if (x > 0 && y < S - 2)
		v[a[x][y]].push_back(a[x - 1][y + 2]);
	if (x < S - 1 && y > 1)
		v[a[x][y]].push_back(a[x + 1][y - 2]);
	if (x < S - 1 && y < S - 2)
		v[a[x][y]].push_back(a[x + 1][y + 2]);
	if (x < S - 2 && y > 0)
		v[a[x][y]].push_back(a[x + 2][y - 1]);
	if (x < S - 2 && y < S - 1)
		v[a[x][y]].push_back(a[x + 2][y + 1]);

}

void Result(int res[SIZE][SIZE], int S, vector <int>& prev)
{
	for (int i = 0; i < S * S; i++)
		res[prev[i] / S][prev[i] % S] = i;
}

bool findWay(int x, int y, int a[SIZE][SIZE], int S, vector<vector<int>>& v, int res[SIZE][SIZE], int count, vector <int> prev)
{
	int k;
	prev.push_back(a[x][y]);
	count++;
	if (count >= S * S)
	{
		Result(res, S, prev);
		return true;
	}
	for (k = 0; k < v[a[x][y]].size(); k++)
	{
		int t;
		for (t = 0; t < prev.size() && prev[t] != v[a[x][y]][k]; t++)
			;
		if (t == prev.size())
		{
			if (findWay(v[a[x][y]][k] / S, v[a[x][y]][k] % S, a, S, v, res, count, prev))
				return true;
		}
	}
	return false;
}

int main()
{
	int a[SIZE][SIZE];
	int S, x, y, k = 0;
	cin >> S;
	cin >> x;
	cin >> y;
	vector <vector<int>> g(S * S);
	for (int i = 0; i < S; i++)
		for (int j = 0; j < S; j++)
			a[i][j] = k++;
	cout << "Graph:";
	cout << endl;
	for (int i = 0; i < S; i++)
		for (int j = 0; j < S; j++)
			graph(i, j, a, S, g);
	for (int i = 0; i < S * S; i++)
	{
		cout << i << " - ";
		for (int j = 0; j < g[i].size(); j++)
			cout << g[i][j] << " ";
		puts("");
	}
	cout << "Hamiltonian path:" << endl;
	int res[SIZE][SIZE];
	vector<int> prev;
	if (findWay(x, y, a, S, g, res, 0, prev))
	{
		for (int i = 0; i < S; i++)
		{
			for (int j = 0; j < S; j++)
				cout << res[i][j] << " ";
			puts("");
		}
	}
	else
		cout << "No way" << endl;


	return 0;
}
