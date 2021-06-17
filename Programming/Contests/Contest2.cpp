#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define N 100

int count_neighbs(int f[N][N], int i, int j, int n, int m)
{
	int res = 0;
	int l = j - 1;
	if (l < 0)
		l = m - 1;
	int r = j + 1;
	if (r > m - 1)
		r = 0;
	int u = i - 1;
	if (u < 0)
		u = n - 1;
	int d = i + 1;
	if (d > n - 1)
		d = 0;

	res += f[u][j];
	res += f[u][r];
	res += f[i][r];
	res += f[d][r];
	res += f[d][j];
	res += f[d][l];
	res += f[i][l];
	res += f[u][l];

	return res;
}

int alives_cells(int field[N][N], int n, int m)
{
	int res = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (field[i][j] == 1)
				res++;
	return res;
}

int cmp_matrix(int field[N][N], int game[N][N], int n, int m)
{
	for (int i = 0; i < n + 2; i++)
		for (int j = 0; j < m + 2; j++)
			if (field[i][j] != game[i][j])
				return 0;
	return 1;
}

int main()
{
	int last[N][N];
	int cur[N][N];
	int m, n;

	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &cur[i][j]);

	int step = 0, res;
	int cells = alives_cells(cur, n, m);
	while (step <= 1000 && cells > 0)
	{
		if (step == 1 || step == 10 || step == 100 || step == 1000)
		{
			printf("Step %d: alives %d\n", step, cells);
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j <= m; j++)
					if (cur[i][j] == 1)
						printf("%c", 'x');
					else
						printf("%c", ' ');
				printf("\n");

			}
		}

		if (cmp_matrix(last, cur, n, m))
			break;

		for (int k = 0; k < n; k++)
			for (int l = 0; l < m; l++)
				last[k][l] = cur[k][l];

		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
			{
				res = count_neighbs(last, i, j, n, m);
				if (last[i][j] == 1 && (res > 3 || res < 2))
					cur[i][j] = 0;
				if (last[i][j] == 1 && (res == 2 || res == 3))
					cur[i][j] = 1;
				if (last[i][j] == 0 && res == 3)
					cur[i][j] = 1;
				if (last[i][j] == 0 && res != 3)
					cur[i][j] = 0;
			}

		step++;
		cells = alives_cells(cur, n, m);
	}

	if (step > 1000)
		step--;

	printf("End life step %d", step);

	return 0;
}
