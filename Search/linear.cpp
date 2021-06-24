#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE 100

void linear_search(int a[], int n, int x)
{
	printf("Initial array:\n");
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\nTarget element: %d\n", x);
	int i = 0;
	int index[SIZE];
	for (int j = 0; j < n; j++)
		index[j] = -1;
	int j = 0;
	while (i < n)
	{
		if (a[i] == x)
		{
			index[j] = i;
			j++;
		}
		i++;
	}
	if (index[0] > -1)
	{
		printf("Target is found at: ");
		for (int k = 0; k < j; k++)
			printf("%d ", index[k]);
	}
	else
		printf("No targets");
}

int main()
{
	int a[SIZE];
	int n, target;
	scanf("%d", &n);
	scanf("%d", &target);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	linear_search(a, n, target);


	return 0;
}
