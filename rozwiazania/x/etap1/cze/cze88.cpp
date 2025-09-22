// Rozwiązanie powolne zadania 'Czekolada' z I Etapu X OI.
// Autor: Paweł Putra
// Złożoność czasowa: O((n + m) * log(n + m))
// Złożoność pamięciowa: O(n + m)
// Punkty: 88 (upsolve)
// Rozwiązanie bez obserwacji, że można zawsze łamać przez całość czekolady bez zmiany wyniku.

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
constexpr int MAXN = 1005, INF = 1'000'000'000;
int x[MAXN], y[MAXN];

struct MinTree {
	int t[4 * MAXN], n, *tab;

	int ql, qr;

	int idx_of_max(int l, int r) {
		ql = l, qr = r;
		return query(1, 1, n);
	}

	int query(int pos, int l, int r) {
		if (l > qr || r < ql) return 0;
		if (l >= ql && r <= qr) return t[pos];
		int m = (l + r) / 2;
		int idx_l = query(pos * 2, l, m);
		int idx_r = query(pos * 2 + 1, m+1, r);
		if (tab[idx_l] > tab[idx_r]) return idx_l;
		return idx_r;
	}

	void build(int size, int* tab_ptr) {
		n = size;
		tab = tab_ptr;
		_build(1, 1, n);
	}

	void _build(int pos, int l, int r) {
		if (l == r) {
			t[pos] = l;
			return; 
		}
		
		int m = (l + r) / 2;
		_build(pos * 2, l, m);
		_build(pos * 2 + 1, m + 1, r);
		if (tab[t[pos*2]] > tab[t[pos*2+1]]) t[pos] = t[pos*2];
		else t[pos] = t[pos*2+1];
	}
} best_x, best_y;

// Koszt podzielenia podprostokąta czekolady o współrzędnych łamań [l, r] x [d, u].
// Krawędzi jest (n-1)*m + m * (n-1) <= 2 * n*m <= 2 * 10^6.
// Czyli max wynik <= 2 * 10^9.
int solve(int l, int r, int d, int u) {
	int bx = best_x.idx_of_max(l, r);
	int by = best_y.idx_of_max(d, u);
	if (bx == 0 && by == 0) return 0;
	//	cerr << dbg(l) << dbg(r) << dbg(d) << dbg(u) << dbg(bx) << dbg(x[bx]) << dbg(by) << dbg(y[by]) << endl;
	if (x[bx] > y[by]) {
	//	cerr << "PO X" << endl;
		return x[bx] + solve(l, bx - 1, d, u) + solve(bx + 1, r, d, u);
	} else {
	//	cerr << "PO Y" << endl;
		return y[by] + solve(l, r, d, by-1) + solve(l, r, by+1, u);
	}
}


int32_t main() {
	ios_base::sync_with_stdio(0);

	int m, n;

	cin >> m >> n;

	for (int i = 1; i <= m-1; i++) cin >> x[i];
	for (int i = 1; i <= n-1; i++) cin >> y[i];


	best_x.build(m, x);
	best_y.build(n, y);
	cout << solve(1, m-1, 1, n-1) << "\n";
}
