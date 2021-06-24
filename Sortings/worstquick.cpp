#include <iostream>
#include <vector>
#define N 100
using namespace std;

void worst(int n, int l, int r)
{
	vector <int> v(n);
	int pivot = (l + r) / 2;
	v[pivot] = n;
	int s = 0;
	int f = 0;
	for (int i = 1; i < n; i++)
		if (i % 2 == 0)
			v[s++] = i;
		else
		{
			v[n - 1 - f] = i;
			f++;
		}
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";
}

int main()
{
	int n;
	cin >> n;
	worst(n, 0, n - 1);


	return 0;
}
