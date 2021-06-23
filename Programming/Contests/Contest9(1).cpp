#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct point
{
	double x;
	double y;
	int order;

}POINT;

typedef struct line
{
	double A;
	double B;
	double C;
	POINT points[100];
	int size;

} LINE;

LINE createline(POINT a, POINT b)
{
	LINE* tmp = (LINE*)calloc(1, sizeof(LINE));
	tmp->A = a.y - b.y;
	tmp->B = a.x - b.x;
	tmp->C = a.x * b.y - b.x * a.y;
	if (tmp->C == -0)
		tmp->C = fabs(tmp->C);
	if (tmp->A == -0)
		tmp->A = fabs(tmp->A);
	if (tmp->B == -0)
		tmp->B = fabs(tmp->B);

	if (tmp->B != (double)0)
	{
		if (tmp->A != 0)
			tmp->A /= tmp->B;
		if (tmp->C != 0)
			tmp->C /= tmp->B;
		if (tmp->B != 0)
			tmp->B /= tmp->B;
	}
	else
	{
		if (tmp->C != 0)
			tmp->C /= tmp->A;
		if (tmp->A != 0)
			tmp->A /= tmp->A;
	}
	tmp->points[0] = a;
	tmp->points[1] = b;
	tmp->size = 2;

	return *tmp;
}

int exist(LINE l, LINE* lines, int k)
{
	for (int i = 0; i < k; i++)
	{
		if (l.A == lines[i].A && l.B == lines[i].B && l.C == lines[i].C)
			return i;
	}
	return -1;
}

int existpoint(POINT* p, POINT a, int k)
{
	for (int i = 0; i < k; i++)
	{
		if (p[i].x == a.x && p[i].y == a.y)
			return 1;
	}
	return 0;
}

double lengthline(POINT a, POINT b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x)
		+ (b.y - a.y) * (b.y - a.y)));
}

int main()
{
	char name1[] = "input.txt";
	char name2[] = "output.txt";

	FILE* in = fopen(name1, "rt");
	FILE* out = fopen(name2, "rt+");

	POINT points[100];
	int k = 0;

	int n;
	fscanf(in, "%d", &n);
	for (int i = 0; i < n; i++)
	{
		fscanf(in, "%lf %lf", &(points[k].x), &(points[k].y));
		points[k].order = k + 1;
		k++;
	}

	LINE lines[1000];
	k = 0;

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			LINE tmp = createline(points[i], points[j]);
			int res;
			if ((res = exist(tmp, lines, k)) > -1)
			{
				if (existpoint(lines[res].points, points[i], lines[res].size) < 1)
				{
					lines[res].points[lines[res].size] = points[i];
					(lines[res].size)++;
				}

				if (existpoint(lines[res].points, points[j], lines[res].size) < 1)
				{
					lines[res].points[lines[res].size] = points[j];
					(lines[res].size)++;
				}
			}
			else
				lines[k++] = tmp;
		}
	}

	int flag = 0;
	for (int i = 0; i < k; i++)
	{
		if (lines[i].size >= 3)
		{
			flag++;
			fprintf(out, "Line %.2lf*x + %.2lf = %.2lf*y Points with numbers: ", lines[i].A, lines[i].C, lines[i].B);
			for (int j = 0; j < lines[i].size; j++)
				fprintf(out, "[%.2lf, %.2lf] (%d) ", lines[i].points[j].x, lines[i].points[j].y, lines[i].points[j].order);
			fprintf(out, "\n");
		}
	}

	if (flag < 1)
		fprintf(out, "No three points on one line");

	fclose(in);
	fclose(out);
	return 0;
}
