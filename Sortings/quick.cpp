#include <iostream>
#include <vector>
#define N 100
using namespace std;

void quick_sort(vector <int>& mas, int l, int r, int n)
{
	if (l < r)
	{
		int pivot = (l + r) / 2;
		int c = mas[pivot];
		cout << "Pivot index: " << pivot << " , pivot element: " << c << endl;

		int k = l;
		int pi = pivot;
		for (int i = l; i <= r; i++)
		{
			if (i == pivot)
				continue;
			if (mas[i] <= c)
			{
				for (int x = i; x > k; x--)
				{
					if (x - 1 == pi)
						pi = x;
					swap(mas[x], mas[x - 1]);
				}
				k++;
			}

		}
		for (int x = pi; x > k; x--)
			swap(mas[x], mas[x - 1]);

		cout << "Array after partition: ";
		for (int i = 0; i < n; i++)
			cout << mas[i] << " ";

		cout << endl;
		cout << endl;
		quick_sort(mas, l, k - 1, n);
		quick_sort(mas, k + 1, r, n);

	}
}

int main()
{
	int n;
	cin >> n;

	vector <int> arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	cout << "Initial array:" << endl;
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl << endl;

	quick_sort(arr, 0, n - 1, n);

	return 0;
}
