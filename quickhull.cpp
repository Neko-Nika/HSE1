#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

struct point
{
	int x;
	int y;
};

bool compare1(const point& a, const point& b)
{
	return a.x < b.x;
}

bool compare2(const point& a, const point& b)
{
	return a.x > b.x;
}

bool comparey(const point& a, const point& b)
{
	return a.y < b.y;
}

bool isinhull(const vector <point>& v, vector <point>& res, int x)
{
	for (int i = 0; i < res.size(); i++)
		if (v[x].x == res[i].x && v[x].y == res[i].y)
			return true;
	return false;
}

double distance(point p1, point p2, point p)
{
	double res = (double)fabs(((p2.x - p1.x) * (p.y - p1.y) - (p2.y - p1.y) * (p.x - p1.x)) / (sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y))));
	return res;
}

int up_or_down(point p1, point p2, point p)
{
	int res = (p2.x - p1.x) * (p.y - p1.y) - (p.x - p1.x) * (p2.y - p1.y);
	if (res > 0) return 1;
	if (res == 0) return 0;
	if (res < 0) return -1;
}

void findhull(vector <point>& s, vector <point>& res, point first, point second)
{
	if (s.size() < 1)
		return;
	double dist = 0;
	point max;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i].x == first.x && s[i].y == first.y || s[i].x == second.x && s[i].y == second.y)
			continue;
		if (distance(first, second, s[i]) > dist)
		{
			dist = distance(first, second, s[i]);
			max = s[i];
		}

	}

	if (dist > 0)
		res.push_back(max);

	vector <point> s1, s2;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i].x == max.x && s[i].y == max.y || s[i].x == first.x && s[i].y == first.y)
			continue;
		if (up_or_down(first, max, s[i]) > 0)
			s1.push_back(s[i]);
		if (up_or_down(max, second, s[i]) > 0)
			s2.push_back(s[i]);
		if (up_or_down(first, max, s[i]) == 0 && s[i].x == 0)
			res.push_back(s[i]);
	}

	findhull(s1, res, first, max);
	findhull(s2, res, max, second);

}

void quickhull(vector <point>& v, vector <point>& res)
{
	sort(v.begin(), v.end(), compare2);

	int min = v[0].x, max = v[0].x, mini = 0, maxi = 0;
	for (int i = 1; i < v.size(); i++)
	{
		if (v[i].x < min)
		{
			min = v[i].x;
			mini = i;
		}
		if (v[i].x > max)
		{
			max = v[i].x;
			maxi = i;
		}
	}

	for (int i = 0; i < v.size(); i++)
	{
		if (i == maxi || i == mini)
			continue;
		if (v[i].x == min && v[i].y < v[mini].y)
			mini = i;
		if (v[i].x == max && v[i].y > v[maxi].y)
			maxi = i;
	}

	vector <point> s1, s2;
	for (int i = 0; i < v.size(); i++)
	{
		if (i == mini || i == maxi)
			continue;
		if (up_or_down(v[mini], v[maxi], v[i]) > 0)
			s1.push_back(v[i]);
		else
			s2.push_back(v[i]);
	}

	res.push_back(v[mini]);
	res.push_back(v[maxi]);

	findhull(s1, res, v[mini], v[maxi]);
	findhull(s2, res, v[maxi], v[mini]);

}

int main()
{
	int x, y;
	vector <point> v;
	char name1[] = "input.txt";
	char name2[] = "output.txt";
	FILE* in = fopen(name1, "rt");
	while (!feof(in))
	{
		point tmp;
		int n = fscanf(in, "%d %d", &(tmp.x), &(tmp.y));
		if (n < 2)
			break;
		v.push_back(tmp);
	}

	vector <point> res;

	quickhull(v, res);

	sort(res.begin(), res.end(), comparey);
	sort(res.begin(), res.end(), compare1);
	cout << "Convex Hull is:\n";
	for (int i = 0; i < res.size(); i++)
	{
		cout << res[i].x << " " << res[i].y << endl;
	}
	fclose(in);
	return 0;
}
