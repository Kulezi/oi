// Rozwiązanie brutalne do zadania 'Bitada' z I etapu XXXII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * 2^m * m)
// Złożoność pamięciowa: O(n)
// Punkty: 51 (upsolve)

#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define dbg(x) #x << " = " << x << " "
using namespace std;
constexpr int MAXN = 3005;
int n, m, k;
vector<vector<int>> mapy[4][4];
vector<int> bitada[MAXN], bajtogrod[MAXN], syny_bitadzkie[MAXN];
int zorientowany[MAXN], kolor[MAXN];
int wpasuj(int v, int u, int p) {
	vector<int> syny_bajtogrodzkie;
	for (auto w : bajtogrod[u]) 
		if (w != p) syny_bajtogrodzkie.push_back(w);

	int ile_synow_bitada = syny_bitadzkie[v].size();
	int ile_synow_bajtogrod = syny_bajtogrodzkie.size();
	if (ile_synow_bitada == 0) return 1;
	int wynik = 0;
	for (auto mapping : mapy[ile_synow_bitada][ile_synow_bajtogrod]) {
		int wynik_mappingu = 1;
		for (int i = 0; i < ile_synow_bitada; i++) {
			wynik_mappingu = 1LL * wynik_mappingu * wpasuj(syny_bitadzkie[v][i], syny_bajtogrodzkie[mapping[i]], u) % k;
		}

		wynik += wynik_mappingu;
		if (wynik >= k) wynik -= k;
	}

	return wynik;
}

void zorientuj_bitade(int v) {
	zorientowany[v] = 1;
	for (auto u : bitada[v]) {
		if (!zorientowany[u]) {
			syny_bitadzkie[v].push_back(u);
			zorientuj_bitade(u);
		}
	}
}

int32_t main() {
	ios_base::sync_with_stdio(0);
	mapy[1][1] = {{0}};
	mapy[1][2] = {{0}, {1}};
	mapy[2][2] = {{0, 1}, {1, 0}};

	// Te mapowania zostaną użyte tylko w korzeniu, dlatego potem rozgałęziamy się tylko w dwie opcje.
	// Stąd 2^m, a raczej 2^h gdzie h to wysokość Bitady.

	mapy[1][3] = {{0}, {1}, {2}};
	mapy[2][3] = {{0, 1}, {0, 2}, {1, 0}, {1, 2}, {2, 0}, {2, 1}};
	mapy[3][3] = {{0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}};
	cin >> n >> m >> k;
	
	for (int i = 1; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		bitada[x].push_back(y);
		bitada[y].push_back(x);
	}

	zorientuj_bitade(1);

	for (int i = 1; i < m; ++i) {
		int x, y;
		cin >> x >> y;
		bajtogrod[x].push_back(y);
		bajtogrod[y].push_back(x);
	}

	int wynik = 0;
	for (int i = 1; i <= m; ++i) {
		// Zmapuj korzeń bitady (wierzchołek nr. 1) na i-ty wierzchołek Bajtogrodu.
		wynik += wpasuj(1, i, -1);
		if (wynik >= k) wynik -= k;
	}

	cout << wynik << "\n";
}
