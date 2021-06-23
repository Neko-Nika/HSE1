#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct address
{
	int a, b, c, d;
} ADDRESS;

typedef struct router
{
	ADDRESS* web;
	ADDRESS* mask;
	ADDRESS* inter;
	int size;
} ROUTER;

void create_address(char* buf, int* x, int* y, int* z, int* w)
{
	int i = 0, k = 0, c = 0;
	int values[4];
	while (i < strlen(buf))
	{
		char* tmp = (char*)calloc(10, sizeof(char));
		k = 0;
		while (i < strlen(buf) && buf[i] != '.')
			tmp[k++] = buf[i++];
		values[c++] = atoi(tmp);
		i++;
		free(tmp);
	}
	*x = values[0];
	*y = values[1];
	*z = values[2];
	*w = values[3];
}

void fill_router(ROUTER* router, char* buf)
{
	char add[100];
	int step = 0, k = 0, size = router->size;
	while (buf[k] == ' ')
		k++;

	while (buf[k] != ' ')
		add[step++] = buf[k++];
	add[step] = '\0';
	create_address(add, &(router->web[size].a), &(router->web[size].b), &(router->web[size].c), &(router->web[size].d));

	step = 0;
	while (buf[k] == ' ')
		k++;
	while (buf[k] != ' ')
		add[step++] = buf[k++];
	add[step] = '\0';
	create_address(add, &(router->mask[size].a), &(router->mask[size].b), &(router->mask[size].c), &(router->mask[size].d));

	step = 0;
	while (buf[k] == ' ')
		k++;
	while (buf[k] != ' ')
		k++;
	while (buf[k] == ' ')
		k++;
	while (buf[k] != ' ')
		add[step++] = buf[k++];
	add[step] = '\0';
	create_address(add, &(router->inter[size].a), &(router->inter[size].b), &(router->inter[size].c), &(router->inter[size].d));

	(router->size)++;
}

ADDRESS* create_web(ADDRESS one, ADDRESS two)
{
	ADDRESS* res = (ADDRESS*)calloc(1, sizeof(ADDRESS));
	res->a = one.a & two.a;
	res->b = one.b & two.b;
	res->c = one.c & two.c;
	res->d = one.d & two.d;
	return res;
}

int find_inter(ROUTER router, ADDRESS web, ADDRESS mask)
{
	for (int i = 0; i < router.size; i++)
	{
		if (router.web[i].a == web.a && router.web[i].b == web.b && router.web[i].c == web.c && router.web[i].d == web.d)
			if (router.mask[i].a == mask.a && router.mask[i].b == mask.b && router.mask[i].c == mask.c && router.mask[i].d == mask.d)
				return i;
	}
	return 0;
}

int main()
{
	char name1[] = "input.txt";
	char name2[] = "output.txt";

	FILE* in = fopen(name1, "rt");
	FILE* out = fopen(name2, "rt+");

	int n, k = 0;
	fscanf(in, "%d \n", &n);
	ROUTER router;
	router.size = 0;
	router.web = (ADDRESS*)calloc(n - 1, sizeof(ADDRESS));
	router.mask = (ADDRESS*)calloc(n - 1, sizeof(ADDRESS));
	router.inter = (ADDRESS*)calloc(n - 1, sizeof(ADDRESS));
	for (int i = 0; i < n; i++)
	{
		if (i == 0)
		{
			char skip[1000];
			fgets(skip, 1000, in);
			continue;
		}
		char* buf = (char*)calloc(1000, sizeof(char));
		fgets(buf, 1000, in);
		fill_router(&router, buf);

		free(buf);
	}

	fscanf(in, "%d", &n);
	for (int i = 0; i < n; i++)
	{
		char* ip = (char*)calloc(100, sizeof(char));
		char* m = (char*)calloc(100, sizeof(char));
		fscanf(in, "%s %s", ip, m);
		ADDRESS one, two;
		create_address(ip, &one.a, &one.b, &one.c, &one.d);
		create_address(m, &two.a, &two.b, &two.c, &two.d);

		ADDRESS* tmp = create_web(one, two);
		int index = find_inter(router, *tmp, two);

		fprintf(out, "%d.%d.%d.%d %d.%d.%d.%d\n", tmp->a, tmp->b, tmp->c, tmp->d,
			router.inter[index].a, router.inter[index].b, router.inter[index].c, router.inter[index].d);

		free(ip);
		free(m);
	}

	fclose(in);
	fclose(out);
	return 0;
}
