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

	int flag = 0;
	for (int i = 0; i < k - 1; i++)
	{
		for (int j = i + 1; j < k; j++)
		{
			if (lines[i].A * lines[j].A == -1 || (lines[i].B == 0 || lines[j].B == 0) && lines[i].A * lines[j].A == lines[j].B * lines[i].B)
			{
				flag = 1;
				fprintf(out, "Line%d and line%d are perpendicular\n", i + 1, j + 1);
				fprintf(out, "Line%d: %.2lf*x + %.2lf = %.2lf*y Points with numbers: ", i + 1, lines[i].A, lines[i].C, lines[i].B);
				for (int c = 0; c < lines[i].size; c++)
					fprintf(out, "[%.2lf, %.2lf] (%d) ", lines[i].points[c].x, lines[i].points[c].y, lines[i].points[c].order);
				fprintf(out, "\n");

				fprintf(out, "Line%d: %.2lf*x + %.2lf = %.2lf*y Points with numbers: ", j + 1, lines[j].A, lines[j].C, lines[j].B);
				for (int c = 0; c < lines[j].size; c++)
					fprintf(out, "[%.2lf, %.2lf] (%d) ", lines[j].points[c].x, lines[j].points[c].y, lines[j].points[c].order);
				fprintf(out, "\n");
			}
		}
	}

	if (flag < 1)
		fprintf(out, "No perpendicular lines");

	fclose(in);
	fclose(out);
	return 0;
}
