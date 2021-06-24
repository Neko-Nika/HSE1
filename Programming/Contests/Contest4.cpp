#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main()
{
	char a[10000];
	char name1[1000];
	char name2[1000];
	int n1, n2, g1, g2;
	gets(a);

	int j = 0;
	while (a[j] != ' ')
		name1[j++] = a[j];
	name1[j] = '\0';

	j += 3;
	int k = 0;
	while (a[j] != ' ')
		name2[k++] = a[j++];
	name2[k] = '\0';

	j++;
	char num[1000];
	k = 0;
	while (a[j] != ':')
		num[k++] = a[j++];
	num[k] = '\0';
	g1 = atoi(num);

	j++;
	k = 0;
	while (a[j] != ' ')
		num[k++] = a[j++];
	num[k] = '\0';
	g2 = atoi(num);

	j += 2;
	k = 0;
	while (a[j] != ':')
		num[k++] = a[j++];
	num[k] = '\0';
	n1 = atoi(num);

	j++;
	k = 0;
	while (a[j] != ')')
		num[k++] = a[j++];
	num[k] = '\0';
	n2 = atoi(num);

	char f[1000];
	char s[1000];
	char t[1000];

	if (n1 > n2)
		strcpy(f, name1);
	else if (n1 < n2)
		strcpy(f, name2);
	else
		strcpy(f, "draw\0");

	if (g1 - n1 > g2 - n2)
		strcpy(s, name1);
	else if (g1 - n1 < g2 - n2)
		strcpy(s, name2);
	else
		strcpy(s, "draw\0");

	if (g1 > g2)
		strcpy(t, name1);
	else if (g1 < g2)
		strcpy(t, name2);
	else
		strcpy(t, "draw\0");

	if (strcmp(f, s) == 0 && strcmp(s, t) == 0)
	{
		printf("%s\n", f);
	}
	else
	{
		printf("%s\n%s\n%s\n", f, s, t);
	}

	return 0;
}
