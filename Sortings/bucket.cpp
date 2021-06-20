#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
#include <vector>
#define SIZE 100


void bucketSort(double v[], int n) {
	vector <double> b[SIZE];
	double max = v[0];
	for (int i = 0; i < n; i++) {
		if (v[i] > max) {
			max = v[i];
		}
	}

	double min = v[0];
	for (int i = 0; i < n; i++) {
		if (v[i] < min) {
			min = v[i];
		}
	}
	double step = (max - min) / (n * 2);

	cout << "\n\n";

	if (step != 0)
	{

		for (int i = 0; i < n; i++) {
			int index = (int)floor((v[i] - min) / step);
			if (index == n * 2)
				index--;
			b[index].push_back(v[i]);
		}

	}
	else
	{
		for (int i = 0; i < n; i++) {
			b[0].push_back(v[i]);
		}
	}

	for (int i = 0; i < n * 2; i++)
	{
		if (b[i].size() > 0)
		{
			cout << "Bucket:\n";
			for (int j = 0; j < b[i].size(); j++) {
				printf("%.2f ", b[i][j]);
			}
			cout << "\n";
		}

		sort(b[i].begin(), b[i].end());

		if (b[i].size() > 0)
		{
			cout << "Sorted bucket:\n";
			for (int j = 0; j < b[i].size(); j++) {
				printf("%.2f ", b[i][j]);

			}
			cout << "\n\n";
		}
	}

	int k = 0;

	for (int i = 0; i < n * 2; i++)
		for (int j = 0; j < b[i].size(); j++)
		{
			v[k] = b[i][j];
			k++;
		}

}


int main() {
	int n;
	cin >> n;
	double v[SIZE];
	for (int i = 0; i < n; i++)
		cin >> v[i];
	cout << "Initial array:\n";
	for (int i = 0; i < n; i++)
	{
		printf("%.2f ", v[i]);
	}
	bucketSort(v, n);

	cout << "Final array:\n";
	for (int i = 0; i < n; i++)
	{
		printf("%.2f ", v[i]);
	}

	return 0;
}
