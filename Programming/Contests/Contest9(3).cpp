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
	if (n % 2 != 0)
		n--;
	for (int i = 0; i < n; i++)
	{
		fscanf(in, "%lf %lf", &(points[k].x), &(points[k].y));
		points[k].order = k + 1;
		k++;
	}

	LINE lines[50];
	k = 0;
	for (int i = 0; i < n; i += 2)
	{
		LINE tmp = createline(points[i], points[i + 1]);
		int res;
		if ((res = exist(tmp, lines, k)) > -1)
		{
			lines[res].points[lines[res].size] = points[i];
			lines[res].points[lines[res].size + 1] = points[i + 1];
			lines[res].size += 2;
		}
		else
			lines[k++] = tmp;
	}

	for (int i = 0; i < k; i++)
	{
		fprintf(out, "Line%d: %.2lf*x + %.2lf = %.2lf*y Points with numbers: ", i + 1, lines[i].A, lines[i].C, lines[i].B);
		for (int j = 0; j < lines[i].size; j++)
			fprintf(out, "[%.2lf, %.2lf] (%d) ", lines[i].points[j].x, lines[i].points[j].y, lines[i].points[j].order);

		double max = -1;
		int minindex = -1, maxindex = -1;
		for (int c = 0; c < lines[i].size - 1; c++)
			for (int j = c + 1; j < lines[i].size; j++)
				if (lengthline(lines[i].points[c], lines[i].points[j]) > max)
				{
					max = lengthline(lines[i].points[c], lines[i].points[j]);
					minindex = c;
					maxindex = j;
				}
		fprintf(out, "\nMax length is %.2lf, [%.2lf, %.2lf] (%d) - [%.2lf, %.2lf] (%d)\n", max, lines[i].points[minindex].x, lines[i].points[minindex].y,
			lines[i].points[minindex].order,
			lines[i].points[maxindex].x, lines[i].points[maxindex].y,
			lines[i].points[maxindex].order);
	}

	fclose(in);
	fclose(out);
	return 0;
}
