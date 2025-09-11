// Rozwiązanie do zadania 'Drzewo genealogiczne' z II etapu XXXII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * (q + 2^n))
// Złożoność pamięciowa: O(2^n)
// Punkty: 100 (upsolve)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int MAX_2N = (1 << 21) + 5, MAX_N = 25, MOD = 100031419, P = 31;
int n, q;
int tree[2][MAX_2N];
ll pot[MAX_N];

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

int mapping(int x, int y, int level) {
	if (x > y) swap(x, y);
	return (pot[level] * x + y) % MOD;
}

int BASE;

void odpowiedz() {
	cout << (tree[0][1] == tree[1][1] ? "TAK" : "NIE") << "\n";
}

inline void pull(int t, int i, int level) {
	tree[t][i] = mapping(tree[t][2 * i], tree[t][2 * i + 1], level);
}



void recalc(int t, int i) {
    i += BASE;
	int level = 0;
    while (i > 1) {
        i /= 2;
		pull(t, i, level);
		level++;
    }
}


int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> q;
	pot[0] = P;
	for (int i = 1; i <= n; i++) pot[i] = pot[i-1] * pot[i-1] % MOD;

    BASE = 1 << n;
    for (int t = 0; t < 2; t++) {
		string s;
        cin >> s;

		for (int i = 0; i < (1 << n); i++) 
			tree[t][i + BASE] = s[i];
		int level = 0;
		for (int i = (1 << n) - 1; i >= 1; i--) {
			pull(t, i, level);
			if (i == 1 << (n-level-1)) level++;
		}
    }

    odpowiedz();
    while (q--) {
        int t, k;
		char c;
        cin >> t >> k >> c;
		tree[t-1][k-1 + BASE] = c;
        recalc(t-1, k-1);
        odpowiedz();
    }
}
