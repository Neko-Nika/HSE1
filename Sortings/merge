#include <iostream>
#include <vector>
#define N 100
using namespace std;

void merge(int mas[], int l, int r, int pivot)
{
	int size1 = pivot - l;
	int size2 = r - pivot + 1;

	vector <int> v1(size1);
	vector <int> v2(size2);

	for (int i = 0; i < size1; i++)
		v1[i] = mas[l + i];
	for (int i = 0; i < size2; i++)
		v2[i] = mas[pivot + i];

	cout << "Left part: ";
	for (int i = 0; i < v1.size(); i++)
		cout << v1[i] << " ";
	cout << endl;
	cout << "Right part: ";
	for (int i = 0; i < v2.size(); i++)
		cout << v2[i] << " ";

	int i = 0, j = 0;
	int k = l;
	while (i < size1 && j < size2)
	{
		if (v1[i] < v2[j])
		{
			mas[k++] = v1[i];
			i++;
		}
		else
		{
			mas[k++] = v2[j];
			j++;
		}
	}

	while (i < size1)
	{
		mas[k++] = v1[i];
		i++;
	}

	while (j < size2)
	{
		mas[k++] = v2[j];
		j++;
	}

	cout << endl;
	cout << "Merged parts: ";
	for (int c = l; c < k; c++)
		cout << mas[c] << " ";

	cout << endl;
	cout << endl;
}

void merge_sort(int mas[], int l, int r)
{
	if (l < r)
	{
		int pivot;
		if ((l + r) % 2 == 0)
			pivot = (l + r) / 2;
		else
			pivot = ((l + r) / 2) + 1;

		merge_sort(mas, l, pivot - 1);
		merge_sort(mas, pivot, r);

		merge(mas, l, r, pivot);
	}

}

int main()
{
	int arr[N];
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	cout << "Initial array:" << endl;
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl << endl;

	merge_sort(arr, 0, n - 1);

	return 0;
}
