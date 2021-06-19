#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE 1000

void binary_search(int a[], int left, int right, int x, int n)
{
	printf("Initial array:\n");
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\nTarget element: %d\n", x);

	int index[SIZE];
	for (int j = 0; j < n; j++)
		index[j] = -1;

	int pivot, j = 0;
	printf("Search history: ");
	while (left <= right)
	{
		pivot = left + (right - left) / 2;
		printf("%d(%d) ", a[pivot], pivot);
		if (a[pivot] == x)
		{
			index[j] = pivot;
			j++;
			break;
		}
		if (a[pivot] >= x)
			right = pivot - 1;
		if (a[pivot] < x)
			left = pivot + 1;
	}
	if (index[0] > -1)
	{
		printf("\nTarget is found at: ");
		for (int k = 0; k < j; k++)
			printf("%d ", index[k]);
	}
	else
		printf("\nNo targets");
}
int main()
{
	int a[SIZE];
	int n, target;
	scanf("%d", &n);
	scanf("%d", &target);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	binary_search(a, 0, n - 1, target, n);


	return 0;
}
