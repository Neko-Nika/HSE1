#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 101

typedef struct team
{
	char* name;
	char** oponents;
	int* goals;
	int* num;
	int* win;
	int size;

} TEAM;

int mentioned(char* name, TEAM* t, int tsize)
{
	for (int i = 0; i < tsize; i++)
		if (strcmp(t[i].name, name) == 0)
			return i;
	return -1;
}

int num_home(char* op, char* cur, TEAM* t, int k)
{
	for (int i = 0; i < k; i++)
	{
		if (strcmp(op, t[i].name) == 0)
		{
			for (int j = 0; j < t[i].size; j++)
				if (strcmp(cur, t[i].oponents[j]) == 0)
					return t[i].num[j];
		}
	}
	return 0;
}

int main()
{
	char filename1[] = "input.txt";
	char filename2[] = "output.txt";

	FILE* in = fopen(filename1, "rt");
	FILE* out = fopen(filename2, "rt+");

	TEAM* teams;
	teams = (TEAM*)calloc(11, sizeof(TEAM));
	for (int i = 0; i < 11; i++)
	{
		teams[i].oponents = (char**)calloc(11, sizeof(char*));
		for (int j = 0; j < 11; j++)
			teams[i].oponents[j] = (char*)calloc(20, sizeof(char));
		teams[i].goals = (int*)calloc(11, sizeof(int));
		teams[i].num = (int*)calloc(11, sizeof(int));
		teams[i].win = (int*)calloc(11, sizeof(int));
		teams[i].name = (char*)calloc(20, sizeof(char));
		teams[i].size = 0;
	}
	int k = 0;

	while (!feof(in))
	{
		char* n1;
		char* n2;
		int s1 = -1;
		int s2 = -1;
		n1 = (char*)calloc(20, sizeof(char));
		n2 = (char*)calloc(20, sizeof(char));
		fscanf(in, "%s - %s %d:%d", n1, n2, &s1, &s2);

		if (s1 == -1 || s2 == -1)
			break;
		int res;
		if ((res = mentioned(n1, teams, k)) < 0)
		{
			strcpy(teams[k].name, n1);
			strcpy(teams[k].oponents[teams[k].size], n2);
			teams[k].goals[teams[k].size] = s1;
			if (s1 > s2)
				teams[k].win[teams[k].size] = 1;
			teams[k].num[teams[k].size]++;
			teams[k].size++;
			k++;
		}
		else
		{
			int i = 0;
			for (i; i < teams[res].size; i++)
			{
				if (strcmp(teams[res].oponents[i], n2) == 0)
					break;
			}

			if (i == teams[res].size)
			{
				teams[res].size++;
				strcpy(teams[res].oponents[i], n2);
			}

			teams[res].goals[i] += s1;
			teams[res].num[i] += 1;
			if (s1 > s2)
				teams[res].win[i] += 1;
		}

		if ((res = mentioned(n2, teams, k)) < 0)
		{
			strcpy(teams[k].name, n2);
			strcpy(teams[k].oponents[teams[k].size], n1);
			teams[k].goals[teams[k].size] = s2;
			if (s2 > s1)
				teams[k].win[teams[k].size] = 1;
			//teams[k].num[teams[k].size]++;
			teams[k].size++;
			k++;
		}
		else
		{
			int i = 0;
			for (i; i < teams[res].size; i++)
			{
				if (strcmp(teams[res].oponents[i], n1) == 0)
					break;
			}

			if (i == teams[res].size)
			{
				teams[res].size++;
				strcpy(teams[res].oponents[i], n1);
			}

			teams[res].goals[i] += s2;
			//teams[res].num[i] += 1;
			if (s2 > s1)
				teams[res].win[i] += 1;
		}
		free(n1);
		free(n2);
	}


	for (int i = 0; i < k; i++)
	{
		fprintf(out, "%s\n", teams[i].name);
		for (int j = 0; j < teams[i].size; j++)
		{
			int num_games_home = num_home(teams[i].oponents[j], teams[i].name, teams, k);
			fprintf(out, "%s %d %d %d %d\n", teams[i].oponents[j], teams[i].num[j] + num_games_home, num_games_home, teams[i].win[j], teams[i].goals[j]);
		}
	}


	fclose(in);
	fclose(out);
	return 0;
}
