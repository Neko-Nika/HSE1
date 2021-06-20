#include <iostream>
using namespace std;
#define SIZE 101
void insertion_sort(int mas[], int N)
{
	for (int i = 1; i < N; i++)
	{

		for (int j = i; mas[j - 1] > mas[j] && j > 0; j--)
			swap(mas[j - 1], mas[j]);
		cout << "Insertion - Element #" << i << endl;
		for (int j = 0; j < N; j++)
			cout << mas[j] << " ";
		cout << endl;
	}
}

int main()
{
	int n;
	cin >> n;
	int arr[SIZE];
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	cout << "Initial array:" << endl;
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;
	insertion_sort(arr, n);
	return 0;
}
