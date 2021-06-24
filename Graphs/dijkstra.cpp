#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <string.h>
#define INT_MAX 2147483647
using namespace std;
struct city {
	int x;
	int y;
	string name;
	vector <string> neibs;
};
void dijkstra(vector <vector <double>>& g, vector <double>& dist, vector <int>& path, int start) {
	int n = g.size();
	vector <bool> visited(n, false);

	for (int i = 0; i < n; i++) {
		dist[i] = g[start][i];
		if (dist[i] < INT_MAX) {
			path[i] = start;
		}
	}

	dist[start] = 0;
	path[start] = start;
	int num;
	for (int i = 0; i < n; i++) {
		double min = INT_MAX;
		for (int j = 0; j < n; j++)
		{
			if (!visited[j] && dist[j] < min) {
				min = dist[j];
				num = j;
			}
		}


		for (int j = 0; j < n; j++) {
			if (!visited[j] && g[num][j] != INT_MAX && (dist[num] + g[num][j] < dist[j])) {
				dist[j] = dist[num] + g[num][j];
				path[j] = num;
			}
		}
		visited[num] = true;
	}
}


int main() {
	int k;
	cin >> k;
	vector <struct city> v(k);
	for (int i = 0; i < k; i++) {
		cin >> v[i].name;
		cin >> v[i].x;
		cin >> v[i].y;
		char c = getchar();
		if (c == '\n') {
			continue;
		}
		while (true) {
			string s;
			c = getchar();
			while (c != ' ' && c != '\n') {
				s.push_back(c);
				c = getchar();
			}
			if (s.size() > 0) {
				v[i].neibs.push_back(s);
			}
			if (c == '\n') {
				break;
			}
		}

	}

	int start, finish;
	string s;
	cin >> s;
	for (int i = 0; i < k; i++) {
		if (v[i].name == s) {
			start = i;
			break;
		}
	}
	cin >> s;
	for (int i = 0; i < k; i++) {
		if (v[i].name == s) {
			finish = i;
			break;
		}
	}

	vector <vector <double>> g(k, vector <double>(k, INT_MAX));
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < v[i].neibs.size(); j++) {
			for (int p = 0; p < v.size(); p++) {
				if (strstr(v[i].neibs[j].c_str(), v[p].name.c_str()) != NULL) {
					g[i][p] = sqrt(pow(v[i].x - v[p].x, 2) + pow(v[i].y - v[p].y, 2));
					break;
				}
			}
		}
	}

	vector <double> dist(k, INT_MAX);
	vector <int> path(k, -1);
	dijkstra(g, dist, path, start);


	if (path[finish] == -1) {
		cout << "Path:\nNo way";
	}
	else {
		vector <int> way;
		int l = finish;
		while (l != start) {
			way.push_back(l);
			l = path[l];
		}
		way.push_back(start);
		cout << "Path is not greater than " << ceil(dist[finish]) << endl;
		cout << "Path:\n";
		for (int i = way.size() - 1; i >= 0; i--) {
			cout << v[way[i]].name << ' ';
		}
	}
	return 0;
}
