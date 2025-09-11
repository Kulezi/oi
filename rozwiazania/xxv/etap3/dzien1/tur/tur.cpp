// Rozwiązanie do zadania 'Turniej trójinformatyczny' z III etapu XXV OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * log(n))
// Złożoność pamięciowa: O(n)
// Punkty: 100 (upsolve)
// Moja implementacja omówienia https://oi.edu.pl/l/oi25_3_tur/.

#include <bits/stdc++.h>
using namespace std;
constexpr int MAX_N = 500'005, CIAGI = 3, INF = 19999999;
int n;
int hamilton[MAX_N], bufor[MAX_N], t[CIAGI][MAX_N], spojna[MAX_N], lewo[MAX_N], kolejnosc[MAX_N];

bool wygrywa(int i, int j) {
	int res = 0;
	for (int c = 0; c < CIAGI; c++) {
		if (t[c][i] < t[c][j]) res++;
	}

	return res >= 2;
}

void merge_sort(int l, int r) {
	if (l == r) return;
	int m = (l + r) / 2;
	merge_sort(l, m);
	merge_sort(m + 1, r);

	int pos = l;
	int j = m + 1;
	for (int i = l; i <= m; i++) {
		while (j <= r && wygrywa(hamilton[j], hamilton[i])) {
			bufor[pos++] = hamilton[j++];
		}
		bufor[pos++] = hamilton[i];
	}

	// Nieprzepisywani do bufora byli od samego początku na dobrym miejscu.
	for (int i = l; i < pos; i++) {
		hamilton[i] = bufor[i];
	}
}

struct Fenwick {
	int n;
	vector<int> fw;
	Fenwick(int n) : n(n), fw(n, INF) {}
	void insert(int x, int val) {
		for (; x < n; x |= (x+1))
			fw[x] = min(fw[x], val);
	}
	int query(int r) {
		int res = INF;
		for (; r >= 0; r = (r & (r + 1)) - 1)
			res = min(fw[r], res);
		return res;
	}
}; 

void minuj_lewo(int c1, int c2) {
	Fenwick tree(n+1);

	vector<int> ord(n);
	iota(ord.begin(), ord.end(), 1);
	sort(ord.begin(), ord.end(), [&](auto &lhs, auto &rhs) {
		if (t[c1][lhs] == t[c1][rhs])
			return t[c2][lhs] > t[c2][rhs];
		return t[c1][lhs] > t[c1][rhs];
	});

	for (auto i : ord) {
		// Odwracam porządek na y, bo fenwick liczy tylko prefiksy.
		int x = t[c1][i], y = n - t[c2][i] + 1;

		lewo[i] = min(lewo[i], tree.query(y));
		tree.insert(y, kolejnosc[i]);
	}
}

int32_t main() {
	ios_base::sync_with_stdio(0);
	cin >> n; 
	for (int c = 0; c < CIAGI; ++c) {
		for (int i = 1; i <= n; i++) {
			cin >> t[c][i]; 
		}
	}
	
	for (int i = 1; i <= n; i++) {
		hamilton[i] = i;
	}

	// Znajdź ścieżkę hamiltona mergesortem.
	merge_sort(1, n);

	for (int i = 1; i <= n; i++) {
		kolejnosc[hamilton[i]] = lewo[hamilton[i]] = i;
	}

	for (int c1 = 0; c1 < CIAGI; c1++)
		for (int c2 = c1 + 1; c2 < CIAGI; c2++)
			minuj_lewo(c1, c2);


	int min_lewo = INF;
	for (int i = n; i >= 1; i--) {
		spojna[hamilton[i]] = i;
		if (min_lewo <= i) spojna[hamilton[i]] = spojna[hamilton[i+1]];
		min_lewo = min(min_lewo, lewo[hamilton[i]]);
	}

	int m;
	cin >> m;
	while (m--) {
		int a, b;
		cin >> a >> b;
		if (kolejnosc[a] < kolejnosc[b] || spojna[a] == spojna[b]) cout << "TAK\n";
		else cout << "NIE\n";
	}
}
