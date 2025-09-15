// Rozwiązanie zadania 'Osiedla' z II etapu XXV OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n)
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
constexpr int MAXN = 1'000'005;

int spojne;
string kierunki;
vector<pair<int,int>> g[MAXN];

int vis[MAXN];
int d[MAXN];	// d[v] = odległość v od korzenia (głębokość).
int low[MAXN];	// low[v] = najniższa głębokość na jaką idzie krawędź powrotna z poddrzewa.

void dfs(int v, int p /* numer krawędzi którą przyszedłem */) {
	low[v] = d[v];
	vis[v] = 1;
	for (auto [w, i] : g[v]) {
		if (!vis[w]) {
			d[w] = d[v] + 1;
			kierunki[abs(i) - 1] = (i < 0 ? '>' : '<');
			dfs(w, abs(i));

			low[v] = min(low[w], low[v]);
		}
		else if (abs(i) != p) {
			kierunki[abs(i) - 1] = (i < 0 ? '<' : '>');
			low[v] = min(low[v], d[w]);
		}
	}
}


int32_t main() {
	ios_base::sync_with_stdio(0);
	int n, m;
	cin >> n >> m;

	kierunki = string(m, '<');
	for (int i = 1; i <= m; i++) {
		int a, b;
		cin >> a >> b;
		g[a].emplace_back(b, i);
		g[b].emplace_back(a, -i);
	}

	for (int i = 1; i <= n; i++) {
		if (!vis[i]) 
			dfs(i, 0);
		
		if (low[i] == d[i]) spojne++;
	}

	cout << spojne << "\n";
	cout << kierunki << "\n";
}
