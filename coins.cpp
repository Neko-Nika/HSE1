#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
using namespace std;
struct coord
{
	int row;
	int column;
};

int find_max(vector <vector <int>>& v, int x, int y)
{
	int res;
	if (v[x - 1][y] >= v[x][y - 1])
		res = v[x - 1][y];
	else
		res = v[x][y - 1];
	return res;
}

void get_path(vector <vector <int>>& v, vector <coord>& path, int x, int y, int iS, int jS)
{
	if (y - 1 >= jS && v[x][y - 1] == -1 || x - 1 >= iS && v[x - 1][y] == -1)
		return;
	if (x - 1 >= iS && y - 1 >= jS)
	{
		if (v[x - 1][y] >= v[x][y - 1])
		{
			coord a;
			a.row = x - 1;
			a.column = y;
			path.push_back(a);
			get_path(v, path, x - 1, y, iS, jS);
		}
		else
		{
			coord a;
			a.row = x;
			a.column = y - 1;
			path.push_back(a);
			get_path(v, path, x, y - 1, iS, jS);
		}
	}
	if (x - 1 >= iS && y - 1 < jS)
	{
		coord a;
		a.row = x - 1;
		a.column = y;
		path.push_back(a);
		get_path(v, path, x - 1, y, iS, jS);
	}
	if (x - 1 < iS && y - 1 >= jS)
	{
		coord a;
		a.row = x;
		a.column = y - 1;
		path.push_back(a);
		get_path(v, path, x, y - 1, iS, jS);
	}
}

int main()
{
	int n, m;
	cin >> n >> m;
	vector <vector <int>> v(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			string s;
			cin >> s;
			if (s != "S")
				v[i].push_back(stoi(s));
			else
				v[i].push_back(-1);
		}
	/*for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (v[i][j] != -1)
				cout << v[i][j] << " ";
			else
				cout << "S ";
		}
		puts("");
	}*/

	int iS, jS, flag = 0;
	for (int i = 0; i < n; i++)
	{
		if (flag)
			break;
		for (int j = 0; j < m; j++)
			if (v[i][j] == -1)
			{
				iS = i;
				jS = j;
				flag = 1;
			}
	}
	if (jS + 2 < m)
	{
		for (int i = jS + 1; i < m - 1; i++)
			v[iS][i + 1] += v[iS][i];
	}
	if (iS + 2 < n)
	{
		for (int i = iS + 1; i < n - 1; i++)
			v[i + 1][jS] += v[i][jS];
	}
	for (int i = iS + 1; i < n; i++)
	{
		for (int j = jS + 1; j < m; j++)
		{
			int res;
			res = find_max(v, i, j);
			v[i][j] += res;
		}
	}
	int coins = v[n - 1][m - 1];
	vector <coord> path;
	coord a;
	a.row = n - 1;
	a.column = m - 1;
	path.push_back(a);
	get_path(v, path, n - 1, m - 1, iS, jS);
	cout << "Path:" << endl;
	a.row = iS;
	a.column = jS;
	path.push_back(a);
	reverse(path.begin(), path.end());
	for (int i = 0; i < path.size(); i++)
		printf("(%d,%d) ", path[i].row, path[i].column);
	cout << endl;
	cout << "Coins: " << coins;
	return 0;
}
