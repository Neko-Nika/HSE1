#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <cctype>
#include <string>
#include <cmath>
#define SIZE 1000
using namespace std;

struct _hash
{
	int value;
	string key;
};

int hash_function(string key, int q, int p)
{
	int sum = 0, power = 1;
	for (int i = 0; i < key.size(); i++)
	{
		sum = (sum + (key[i] - 'a' + 1) * power) % q;
		power = (power * p) % q;
	}

	return sum;
}

void put_hash(_hash* t, int* status, string key, int value, int hash, int q)
{
	cout << "PUT result=";

	if (status[hash] < 1)
	{
		status[hash] = 1;
		_hash tmp;
		tmp.key = key;
		tmp.value = value;
		t[hash] = tmp;
		cout << "inserted value=" << value;
		return;
	}

	if (status[hash] > 0)
	{
		int nhash = hash;
		int k = 0;

		while (status[nhash] != 0 && k < q)
		{
			k++;
			nhash++;
			nhash %= q;
		}

		if (k < q)
		{
			status[nhash] = 1;
			_hash tmp;
			tmp.key = key;
			tmp.value = value;
			t[nhash] = tmp;
			cout << "collision linear_probing=" << nhash << " value=" << value;
			return;
		}
		else
		{
			cout << "overflow";
			return;
		}

	}

}

void get_hash(_hash* t, int* status, string key, int hash, int q)
{
	cout << "GET result=";

	if (status[hash] == 0)
	{
		cout << "no_key";
		return;
	}

	if (status[hash] > 0 && t[hash].key == key)
	{
		cout << "found value=" << t[hash].value;
		return;
	}

	int k = 0;
	int nhash = hash;
	while (status[nhash] != 0 && k < q)
	{
		if (status[nhash] > 0 && t[nhash].key == key)
		{
			cout << "collision linear_probing=" << nhash << " value=" << t[nhash].value;
			return;
		}

		k++;
		nhash++;
		nhash %= q;
	}

	cout << "collision linear_probing=" << nhash << " value=no_key";
	return;
}

void del_hash(_hash* t, int* status, string key, int hash, int q)
{
	cout << "DEL result=";

	if (status[hash] > 0 && t[hash].key == key)
	{
		cout << "removed";
		status[hash] = -1;
		return;
	}

	if (status[hash] == 0)
	{
		cout << "no_key";
		return;
	}

	int k = 0;
	int nhash = hash;
	while (status[nhash] != 0 && k < q)
	{
		if (status[nhash] > 0 && t[nhash].key == key)
		{
			cout << "collision linear_probing=" << nhash << " value=removed";
			status[nhash] = -1;
			return;
		}

		k++;
		nhash++;
		nhash %= q;
	}

	cout << "collision linear_probing=" << nhash << " value=no_key";
	return;
}

int main()
{
	int q, p, n;
	cin >> q >> p >> n;

	int status[SIZE]{ 0 };    //1 - value, 0 - None, -1 - deleted value
	_hash* table = new _hash[q];

	int value;
	string op, key, val;
	for (int i = 0; i < n; i++)
	{
		cin >> op >> key;

		int res = hash_function(key, q, p);

		cout << "key=" << key << " hash=" << res << " operation=";

		if (op == "PUT")
		{
			cin >> val;
			value = stoi(val);
			put_hash(table, status, key, value, res, q);
		}

		if (op == "GET")
			get_hash(table, status, key, res, q);

		if (op == "DEL")
			del_hash(table, status, key, res, q);

		cout << endl;
	}

	return 0;
}
