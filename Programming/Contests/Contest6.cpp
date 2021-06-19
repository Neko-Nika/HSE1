#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1000
#define RIGHT 3
#define DOWN 6
#define LEFT 9
#define UP 12

int move(char game[SIZE][SIZE], int rows, int cols)
{
	int dir = RIGHT;
	int i = 1, j = 1;
	int step = 0, res = 0;

	while (step < (rows - 2) * (cols - 2))
	{
		switch (dir)
		{
		case RIGHT: j++; break;
		case DOWN: i++; break;
		case LEFT: j--; break;
		case UP: i--; break;
		}

		if (game[i][j] == '#')
			dir = (dir % 12 + 6) % 12;

		if (game[i][j] == '/')
		{
			switch (dir)
			{
			case UP: dir = RIGHT; break;
			case RIGHT: dir = UP; break;
			case LEFT: dir = DOWN; break;
			case DOWN: dir = LEFT; break;
			}
		}

		if (game[i][j] == '\\')
		{
			switch (dir)
			{
			case UP: dir = LEFT; break;
			case RIGHT: dir = DOWN; break;
			case LEFT: dir = UP; break;
			case DOWN: dir = RIGHT; break;
			}
		}

		if (game[i][j] == '*')
			res++;

		if ((i == 5) && (j == 41))
			return res;

		step++;
	}

	return -1;
}

int prise_count(char game[SIZE][SIZE], int rows, int cols)
{
	int res = 0;
	for (int i = 1; i < rows - 1; i++)
		for (int j = 1; j < cols - 1; j++)
		{
			if (game[i][j] == '*')
				res++;
		}
	return res;
}

int main()
{
	char name1[] = "input.txt";
	char name2[] = "output.txt";

	FILE* in = fopen(name1, "rt");
	FILE* out = fopen(name2, "rt+");

	char game[SIZE][SIZE];
	int rows = 0, cols = 0;
	char c;

	while (!feof(in))
	{
		fgets(game[rows], SIZE, in);
		game[rows][strlen(game[rows]) - 1] = '\0';
		rows++;
	}

	cols = strlen(game[0]);

	int prises = prise_count(game, rows, cols);
	int res = move(game, rows, cols);

	if (res > -1)
	{
		fprintf(out, "%s", "yes\n");
		if (prises == res)
			fprintf(out, "%s", "yes");
		else
			fprintf(out, "%s", "no");
	}
	else
		fprintf(out, "%s", "no\n");

	fclose(out);
	fclose(in);

	return 0;
}
