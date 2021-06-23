#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>
using namespace std;

int minimum(vector <vector<int>>& v, vector <int>& used, int cur)
{
	int min = INT_MAX - 1, imin = -1, j;
	for (int i = 0; i < v[cur].size(); i++)
	{
		if (v[cur][i] == 0)
			continue;
		if (v[cur][i] < min)
		{
			for (j = 0; j < used.size(); j++)
				if (used[j] == i)
					break;
			if (j == used.size())
			{
				min = v[cur][i];
				imin = i;
			}
		}
	}
	return imin;
}

int main()
{
	int n;
	cin >> n;
	vector <vector <int>> v(n, vector <int>(n));
	vector <int> now_path;
	vector <int> min_path;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> v[i][j];
	int flag, cur, cost, min_cost, cur_cost;
	min_cost = INT_MAX - 1;


	for (int i = 0; i < n; i++)
	{
		now_path.clear();
		now_path.push_back(i);
		cur = i;
		cost = 0;
		while (now_path.size() < n)
		{
			cur_cost = minimum(v, now_path, cur);
			if (cur_cost == -1)
				break;
			cost += v[cur][cur_cost];
			now_path.push_back(cur_cost);
			cur = cur_cost;
		}
		if (now_path.size() == n)
		{
			if (v[cur][i] == 0)
				continue;
			if (cost + v[cur][i] < min_cost)
			{
				now_path.push_back(i);
				min_cost = cost + v[cur][i];
				min_path = now_path;
			}
		}
	}
	if (min_cost == INT_MAX - 1)
		cout << "Lost" << endl;
	else
	{
		cout << "Path:" << endl;
		for (int i = 0; i < min_path.size(); i++)
			cout << min_path[i] << " ";
		cout << endl << "Cost: " << min_cost;
	}

	return 0;
}
