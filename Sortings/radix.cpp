#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
vector <string> radix(vector<string> v);
vector <string> makearray(vector <vector <string>> v);

vector <string> radix(vector<string> v)
{
	bool bl = true;
	int k = 0;
	while (bl)
	{
		bl = false;
		int max = 0;
		vector <vector <string>> v1(17, vector <string>());
		for (int i = 0; i < v.size(); i++)
		{
			int p = 0;

			if (v[i].size() > k)
			{

				int l = v[i].size() - 1 - k;
				if (l > max)
				{
					max = l;
				}
				if (v[i][l] < 58)
				{
					p = v[i][l] - 47;
				}
				else
				{
					p = v[i][l] - 54;
				}
			}
			else {
				p = 0;
			}
			v1[p].push_back(v[i]);
		}
		if (max != 0)
		{
			bl = true;
		}
		v = makearray(v1);
		k++;
		cout << "Sorting by " << max << " digit:\n";
		for (int i = 0; i < v.size(); i++)
		{
			cout << v[i] << endl;
		}
		cout << endl;
	}

	return v;
}
vector <string> makearray(vector <vector <string>> v)
{
	vector <string> vk;
	for (int i = 0; i < v.size(); i++)
	{
		for (int j = 0; j < v[i].size(); j++)
		{
			vk.push_back(v[i][j]);
		}
	}
	return vk;
}
int main()
{
	int n;
	cin >> n;
	vector <string> v(n);
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
	}
	v = radix(v);
	return 0;
}
