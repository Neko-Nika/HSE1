#include <iostream>
#include <vector>
#include <queue>
#define SIZE 1000
using namespace std;

void graph(vector <vector <int>>& vg, vector <vector <int>>& g, vector <vector <char>>& v, int row, int col, int x, int y)
{
	if (v[x][y] == '#')
	{
		vg[g[x][y]].push_back(-1);
		return;
	}
	if (x > 0 && v[x - 1][y] != '#')
		vg[g[x][y]].push_back(g[x - 1][y]);
	if (y > 0 && v[x][y - 1] != '#')
		vg[g[x][y]].push_back(g[x][y - 1]);
	if (y < col - 1 && v[x][y + 1] != '#')
		vg[g[x][y]].push_back(g[x][y + 1]);
	if (x < row - 1 && v[x + 1][y] != '#')
		vg[g[x][y]].push_back(g[x + 1][y]);

	if (vg[g[x][y]].size() < 1)
		vg[g[x][y]].push_back(-1);
}

void BFS(vector <vector <int>>& matrix, int start, int range[], int finish)
{
	queue <int> q;
	vector <int> color(matrix.size(), 0);
	q.push(start);
	range[start] = 0;
	color[start] = 1;
	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		color[v] = 1;
		if (color[finish] == 1)
			break;
		for (int i = 0; i < matrix[v].size(); i++)
		{
			if (matrix[v][i] == 1)
				if (color[i] == 0)
				{
					range[i] = range[v] + 1;
					q.push(i);
				}
		}
	}
}

int main()
{
	int row, col, xS, yS, xF, yF, start, finish;
	cin >> row;
	cin >> col;
	char symbol;
	vector <vector <char>> v(row);
	vector <vector <int>> g(row);
	vector <vector <int>> vg(row * col);
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			cin >> symbol;
			v[i].push_back(symbol);
			if (symbol == 'S')
			{
				xS = i;
				yS = j;
			}
			if (symbol == 'F')
			{
				xF = i;
				yF = j;
			}
		}
	int k = 0;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			g[i].push_back(k++);
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			graph(vg, g, v, row, col, i, j);
	cout << "Initial labyrinth:" << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			cout << v[i][j];
		puts("");
	}
	cout << "Graph:" << endl;
	for (int i = 0; i < row * col; i++)
	{
		cout << i << " - ";
		for (int j = 0; j < vg[i].size(); j++)
		{
			if (vg[i][j] != -1)
				cout << vg[i][j] << " ";
			else
				cout << "None";
		}
		puts("");
	}
	vector <vector <int>> matrix(row * col, vector <int>(row * col, 0));
	for (int i = 0; i < row * col; i++)
		for (int j = 0; j < vg[i].size(); j++)
		{
			if (vg[i][j] != -1)
				matrix[i][vg[i][j]] = 1;
			else
				break;
		}
	start = xS * col + yS;
	finish = xF * col + yF;
	int range[SIZE];
	int color[SIZE];
	for (int i = 0; i < row * col; i++)
	{
		range[i] = -1;
		color[i] = 0;
	}
	color[start] = 1;
	BFS(matrix, start, range, finish);
	vector <vector <int>> result(row, vector <int>(col));
	for (int i = 0; i < row * col; i++)
		result[i / col][i % col] = range[i];

	cout << "BFS result is:" << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			cout << result[i][j] << " ";
		puts("");
	}
	return 0;
}
