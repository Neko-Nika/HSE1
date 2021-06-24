#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <cctype>
#include <string>
#define SIZE 100
using namespace std;

template<typename T>
struct _stack
{
	T* values;
	T top;
	int size = 0;

};

template<typename T>
void _push(_stack<T>* st, T val)
{
	st->values = (T*)realloc(st->values, (st->size + 1) * sizeof(T));
	st->values[st->size] = val;
	st->size = st->size + 1;
	st->top = val;
}

template<typename T>
void _pop(_stack<T>* st)
{
	if (st->size < 1)
		return;
	st->values = (T*)realloc(st->values, (st->size - 1) * sizeof(T));
	st->size = st->size - 1;
	if (st->size > 0)
		st->top = st->values[st->size - 1];
	else
		st->top = NULL;
}

int priority(char c)
{
	switch (c)
	{
	case '*': case '/': return 3;
	case '+': case '-': return 2;
	case '(': return 1;
	case ')': return -1;
	default: return 0;
	}
	cout << "Error!" << endl;
}

int count(char out[SIZE][SIZE], int k)
{
	_stack <int> st;
	st.values = (int*)calloc(0, sizeof(int));

	int res = 0, p;
	char str[SIZE];
	for (int i = 0; i < k; i++)
	{
		if (priority(out[i][0]) != 0)
		{
			int b = st.top;
			_pop(&st);
			int a = st.top;
			_pop(&st);

			switch (out[i][0])
			{
			case '+': res = a + b; break;
			case '-': res = a - b; break;
			case '*': res = a * b; break;
			case '/': res = a / b; break;
			}

			_push(&st, res);
		}
		else
		{
			int j = 0;
			for (j = 0; j < strlen(out[i]); j++)
				str[j] = out[i][j];
			str[j] = '\0';
			_push(&st, stoi(str));
		}
	}

	return st.top;

}

int main()
{
	_stack <char> st;
	st.values = (char*)calloc(0, sizeof(char));

	char in[SIZE], out[SIZE][SIZE];
	int k = 0, j = 0, p;
	cin >> in;

	for (int i = 0; i < strlen(in); i++)
	{
		p = priority(in[i]);
		switch (p)
		{
		case 2: case 3:
			j = 0;
			while (priority(st.top) >= p)
			{
				out[k][j] = st.top;
				out[k][j + 1] = '\0';
				k++;
				_pop(&st);
			}
			if (st.size < 1 || priority(st.top) < p)
				_push(&st, in[i]);
			break;

		case 1:
			_push(&st, in[i]);
			break;

		case 0:
			j = 0;
			while (priority(in[i]) == 0 && i < strlen(in))
			{
				out[k][j++] = in[i];
				i++;
			}
			out[k][j] = '\0';
			k++;
			i--;
			break;

		case -1:
			j = 0;
			while (priority(st.top) != 1)
			{
				out[k][j] = st.top;
				out[k][j + 1] = '\0';
				k++;
				_pop(&st);
			}
			if (st.top = '(')
				_pop(&st);
			break;

		}

	}

	j = 0;
	while (st.size > 0)
	{
		out[k][j] = st.top;
		out[k][j + 1] = '\0';
		k++;
		_pop(&st);
	}

	cout << "Expression:\n" << in << endl;

	cout << "Reverse Polish Notation:\n";
	for (int i = 0; i < k; i++)
		cout << out[i] << " ";

	cout << "\nResult:" << endl;
	cout << count(out, k);

	return 0;
}
