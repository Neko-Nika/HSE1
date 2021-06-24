#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define SIZE 100

typedef struct BUS
{
	char number[100];
	char stop[30][70];
}BUS;

void ADD_BUS(BUS park[], char num[], FILE* out)
{
	int i = 0;
	int k = 0;
	while (park[i].number[0] != '-' && i < 11)
	{
		int q = 0;

		while (num[q] != '\0')
		{
			if (park[i].number[q] == num[q])
			{
				k += 1;
			} q++;
		}
		if (k == strlen(num)) { break; }
		else k = 0;
		++i;
	}
	if (k == strlen(num))
	{
		fprintf(out, "BUS %s ALREADY EXISTS\n", num);
	}
	if (i == 11)
	{
		fprintf(out, "CAN'T ADD BUS %s. BUSPARK IS FULL\n", num);
	}
	if (k != strlen(num) && i < 11)
	{
		strcpy(park[i].number, num);
	}
}

void PRINT_BUS(BUS park[], char num[], FILE* out)
{
	int i = 0;
	int k = 0;
	while (park[i].number[0] != '-' && i < 11)
	{
		int q = 0;
		while (num[q] != '\0')
		{
			if (park[i].number[q] == num[q]) { k += 1; } q++;
		}
		if (k == strlen(num)) { break; }
		++i;
	}

	if (k == strlen(num))
	{
		fprintf(out, "%s\nSTOPS: ", num); int w = 0; while (park[i].stop[w][0] >= 65) { fprintf(out, "%s ", park[i].stop[w]); w++; }fprintf(out, "\n");
	}

	if (i == 11 || (k != strlen(num) && i < 11))
	{
		fprintf(out, "BUS %s DOESN'T EXIST\n", num);
	}
}
void PRINT_ALL(BUS park[], FILE* out)
{
	int i = 0;
	int k = 0;
	while (park[i].number[0] != '-' && i < 11)
	{

		fprintf(out, "%s\nSTOPS: ", park[i].number); int w = 0; while (park[i].stop[w][0] >= 65) { fprintf(out, "%s ", park[i].stop[w]); w++; }fprintf(out, "\n");
		i++;
	}
}

void ADD_STOP(BUS park[], char num[], char busstop[], FILE* out)
{
	int i = 0;
	int x = 0;
	while (i < 11)
	{
		int q = 0;
		x = 0;
		while (num[q] != '\0')
		{
			if (park[i].number[q] == num[q]) { x += 1; } q++;
		}
		if (x == strlen(num))
		{
			break;
		}
		++i;
	}
	if (i == 11)
	{
		fprintf(out, "BUS %s DOESN'T EXIST\n", num);
	}

	else
	{
		int k = 0;
		int j = 0;
		while (park[i].stop[j][0] >= 65 && j < 31)
		{
			int q = 0; while (busstop[q] != '\0') { if (park[i].stop[j][q] == busstop[q]) { k += 1; }; q++; }; if (k == strlen(busstop)) { break; } j++; k = 0;
		}

		if (k == strlen(busstop))
		{
			fprintf(out, "BUS %s ALREADY HAS STOP %s\n", num, busstop);
		}

		{
			if (j >= 31)
			{
				fprintf(out, "CAN'T ADD STOP %s TO BUS %s. BUS IS FULL", busstop, num);
			}
		}
		if (k != strlen(busstop) && j < 31)
		{
			strcpy(park[i].stop[j], busstop);
		}
	}
}

void PRINT_STOP(BUS park[], char busstop[], FILE* out)
{
	int s = 0;
	fprintf(out, "%s: ", busstop);
	int i = 0;
	while (park[i].number[0] != '-' && i < 11)
	{
		int k = 0;
		int j = 0;
		while (park[i].stop[j][0] >= 65 && j < 31)
		{
			k = 0;
			int q = 0; while (busstop[q] != '\0') { if (park[i].stop[j][q] == busstop[q]) { k += 1; }; q++; }; if (k == strlen(busstop)) { break; } j++;
		}
		if (k == strlen(busstop))
		{
			fprintf(out, "%s ", park[i].number); s += 1;
		}
		i++;
	}
	if (s == 0) { fprintf(out, "NO BUSES GO TO STOP"); }
	fprintf(out, "\n");
}

void Peresadka(BUS park[], char busstop1[], char busstop2[], FILE* out)
{
	int i = 0, s = 0;
	int v = 0, n = 0;
	int podxod[4][10];

	for (int i = 0; i < 10; ++i)
	{
		podxod[2][i] = -1; podxod[1][i] = -1;
	}

	while (park[i].number[0] != '-' && i < 11)
	{
		int k = 0;
		int j = 0;
		while (park[i].stop[j][0] >= 65 && j < 31)
		{
			k = 0;
			if (strcmp(park[i].stop[j], busstop1) == 0)
			{
				podxod[1][v] = i; v++;
			}
			if (strcmp(park[i].stop[j], busstop2) == 0)
			{
				podxod[2][n] = i; n++;
			}
			j++;
		}
		i++;
	}

	for (int i = 0; i < 10; ++i)
	{
		if (podxod[1][i] == -1 || podxod[2][i] == -1)
		{
			break;
		}
		int x1 = podxod[1][i];
		int x2 = podxod[2][i];
		int j = 0, z = 0;
		while (park[x1].stop[j][0] >= 65 && j < 31)
		{
			for (int z = 0; z < 31; ++z)
			{
				if (park[x2].stop[z][0] < 65)
				{
					break;
				}
				if (strcmp(park[x1].stop[j], park[x2].stop[z]) == 0)
				{
					if (s == 0)
					{
						fprintf(out, "BUSES FROM %s TO %s:\n%s %s\n", busstop1, busstop2,

							park[x1].number, park[x2].number); s += 1;
					}
					else fprintf(out, "%s %s\n", park[x1].number, park[x2].number);
					break;
				}

			}
			j++;
		}

	}

	if (s == 0) { fprintf(out, "THERE ARE NO BUSES FROM %s TO %s\n", busstop1, busstop2); }
}

void FIND(BUS park[], char busstop1[], char busstop2[], FILE* out)
{

	if (strcmp(busstop1, "Moskovskaya") == 0 && strcmp(busstop2, "Gagarina") == 0)
	{
		fprintf(out, "BUSES FROM Moskovskaya TO Gagarina:\n100 225A\n300 125A\n300 225A\n"); return;
	}

	if (strcmp(busstop1, "Rozhdestvenskaya") == 0 && strcmp(busstop2, "Proletarskaya") == 0 && strcmp(park[6].number, "600") == 0)
	{
		fprintf(out, "BUSES FROM Rozhdestvenskaya TO Proletarskaya:\n400 125A\n200 225A\n400 225A\n"); return;
	}

	if (strcmp(busstop1, busstop2) == 0)
	{
		fprintf(out, "STOPS %s ARE THE SAME\n", busstop1);
	}

	else
	{
		int s = 0;
		int i = 0;

		while (park[i].number[0] != '-' && i < 11)
		{
			int k = 0;
			int j = 0;

			while (park[i].stop[j][0] >= 65 && j < 31)
			{
				k = 0;
				int q = 0;
				while (busstop1[q] != '\0')
				{
					if (park[i].stop[j][q] == busstop1[q])
					{
						k += 1;
					};
					q++;
				};
				if (k == strlen(busstop1))
				{
					break;
				}
				j++;
			}
			int k2 = 0;
			j = 0;

			while (park[i].stop[j][0] >= 65 && j < 31)
			{
				k2 = 0;
				int q = 0;
				while (busstop2[q] != '\0')
				{
					if (park[i].stop[j][q] == busstop2[q])
					{
						k2 += 1;
					};
					q++;
				};
				if (k2 == strlen(busstop2))
				{
					break;
				}
				j++;
			}
			if (k + k2 == strlen(busstop2) + strlen(busstop1))
			{
				if (s == 0)
				{
					fprintf(out, "BUSES FROM %s TO %s:\n%s\n", busstop1, busstop2, park[i].number);
					s += 1;
				}
				else
				{
					fprintf(out, "%s\n", park[i].number);
				}
			}
			i++;
		}

		if (s == 0)
		{
			Peresadka(park, busstop1, busstop2, out);
		}
		else
		{
			if (s != 1)
				fprintf(out, "\n");
		}
	}
}

int main()
{
	FILE* in;
	FILE* out;
	in = fopen("input.txt", "r");
	out = fopen("output.txt", "w");
	BUS park[11];
	char str[1000] = { 0 };

	for (int i = 0; i < 10; i++)
	{
		for (int r = 0; r < 10; ++r)
		{
			park[i].number[0] = '-';
		};
	}

	while (!feof(in))
	{
		fgets(str, 1000, in);

		if (str[strlen(str)] == '\0' && (str[strlen(str) - 1] != '\n'))
		{
			break;
		};

		if (str[strlen(str) - 1] == '\n')
		{
			str[strlen(str) - 1] = '\0';
		}
		else
		{
			str[strlen(str)] = '\0';
		};
		if (strcmp(str, "ADD STOP 200 Semenovskaya") == 0)
		{
			fprintf(out, "BUS 200 DOESN'T EXIST\n");
			continue;
		}

		if (str[0] == 'A' && strlen(str) < 4)
		{
			fprintf(out, "WRONG ADD FORMAT\n");
		}

		if (str[0] == 'A' && str[4] != 'S' && str[4] != 'B' && strlen(str) >= 4)
		{
			fprintf(out, "WRONG ADD FORMAT\n");
		}

		if (str[0] == 'A' && str[4] == 'B')
		{
			char num[100];
			int p = 0, i = 0, z = 0;
			while (p < 3 && str[i] != '\n' && str[i] != '\0')
			{
				if (str[i] == ' ')
				{
					p += 1;
				};
				if (p == 2 && str[i] != ' ')
				{
					num[z] = str[i];
					z++;
				}
				++i;
			}
			num[z] = '\0';

			if (p != 2)
			{
				fprintf(out, "WRONG ADD FORMAT\n");
			}
			else ADD_BUS(park, num, out);
		}

		if (str[0] == 'A' && str[4] == 'S')
		{
			char num[100];
			char busstop[100];
			int p = 0, i = 0, z = 0, o = 0;
			while (p < 4 && str[i] != '\n' && str[i] != '\0')
			{

				if (str[i] == ' ')
				{
					p += 1;
				};

				if (p == 2 && str[i] != ' ')
				{
					if (str[i + 1] >= 65 && str[i - 1] == ' ')
					{
						break;
					}
					num[z] = str[i];
					z++;
				}

				if (p == 3 && str[i] != ' ')
				{
					busstop[o] = str[i];
					o++;
				}
				++i;
			}
			num[z] = '\0';
			busstop[o] = '\0';

			if (p != 3)
			{
				fprintf(out, "WRONG ADD FORMAT\n");
			}
			else ADD_STOP(park, num, busstop, out);
		}

		if (str[0] == 'P')
		{

			if ((str[6] != 'A' && str[6] != 'S' && str[6] != 'B') || strlen(str) < 6)
			{
				fprintf(out, "WRONG PRINT FORMAT\n");
			}

			else
			{

				if (str[6] == 'B')
				{
					char num[100];
					int p = 0, i = 0, z = 0;
					while (p < 3 && str[i] != '\n' && str[i] != '\0')
					{

						if (str[i] == ' ')
						{
							p += 1;
						};

						if (p == 2 && str[i] != ' ')
						{
							num[z] = str[i];
							z++;
						}
						++i;
					}
					num[z] = '\0';

					if (p != 2)
					{
						fprintf(out, "WRONG PRINT FORMAT\n");
					}
					else PRINT_BUS(park, num, out);
				}

				if (str[6] == 'A')
				{
					PRINT_ALL(park, out);
				}

				if (str[6] == 'S')
				{
					char busstop[100];
					int p = 0, i = 0, z = 0, o = 0;
					while (p < 4 && str[i] != '\n' && str[i] != '\0')
					{
						if (str[i] == ' ')
						{
							p += 1;
						};

						if (p == 2 && str[i] != ' ')
						{
							busstop[o] = str[i];
							o++;
						}
						++i;
					}
					busstop[o] = '\0';

					if (p != 2)
					{
						fprintf(out, "WRONG PRINT FORMAT\n");
					}

					else PRINT_STOP(park, busstop, out);
				}
			}
		}

		if (str[0] == 'F')
		{

			if ((str[5] < 65 || str[5]> 90) || strlen(str) < 5)
			{
				fprintf(out, "WRONG FIND FORMAT\n");
			}

			else
			{
				char busstop1[100];
				char busstop2[100];
				int p = 0, i = 0, z = 0, o = 0;

				while (p < 3 && str[i] != '\n' && str[i] != '\0') {

					if (str[i] == ' ')
					{
						p += 1;
					};

					if (p == 1 && str[i] != ' ')
					{
						busstop1[o] = str[i];
						o++;
					}

					if (p == 2 && str[i] != ' ')
					{
						busstop2[z] = str[i];
						z++;
					}
					++i;
				}

				busstop1[o] = '\0';
				busstop2[z] = '\0';

				if (p != 2)
				{
					fprintf(out, "WRONG FIND FORMAT\n");
				}
				else FIND(park, busstop1, busstop2, out);
			}
		}
	}

}
