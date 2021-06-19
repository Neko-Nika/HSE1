#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE 1000

void binary_search1(int a[], int left, int right, int x, int n)
{
	if (left <= right)
		printf("\nSearch history: ");
	int pivot, flag = 0;
	while (left <= right)
	{
		pivot = left + (right - left) / 2;
		if (pivot % 4 != 0 && pivot > 2)
			printf("%d(%d) ", a[pivot], pivot);
		if (a[pivot] == x)
		{
			printf("\nTarget is found at: %d", pivot);
			flag = 1;
			break;
		}
		if (a[pivot] > x)
			right = pivot - 1;
		if (a[pivot] < x)
			left = pivot + 1;
	}
	if (flag < 1)
		printf("\nNo targets");
}

void doubling_search(int a[], int n, int x)
{
	printf("Initial array:\n");
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\nTarget element: %d\n", x);
	printf("Bounds history: ");
	printf("%d(%d) ", a[0], 0);
	if (a[0] == x)
	{
		printf("\nTarget is found at: %d", 0);
		return;
	}
	if (x < a[0])
	{
		printf("\nNo targets");
		return;
	}
	int i = 1;
	while (i < n)
	{
		printf("%d(%d) ", a[i], i);
		if (a[i] == x)
		{
			printf("\nTarget is found at: %d", i);
			return;
		}
		if (a[i] < x)
			i *= 2;
		else
			break;

	}

	if (i < 4)
	{
		printf("\nNo targets");
		return;
	}

	int half = i / 2;

	if (i > n)
		i = n - 1;
	if (half < n && a[n - 1] < x)
	{
		binary_search1(a, half + 1, i, x, n);
	}
	else
		binary_search1(a, half, i, x, n);
}

int main()
{
	int a[SIZE];
	int n, target;
	scanf("%d", &n);
	scanf("%d", &target);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	doubling_search(a, n, target);

	return 0;
}
