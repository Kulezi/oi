// Deterministyczne rozwiązanie do zadania 'Drzewo genealogiczne' z II etapu XXXII OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * (q + 2^n))
// Złożoność pamięciowa: O(2^n) z dużą stałą - niestety wychodzi ~256MB na samą mapę + drzewo + overhead. 
// Punkty: 71 (upsolve)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int MAX_2N = (1 << 21) + 5, MAX_N = 25;
int n, q;
int tree[2][MAX_2N];

int R(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}

unordered_map<ll, int> identyfikatory;

int FREE_ID = 256;

// Po prostu robię izomorfizm drzew, unordered mapa, żeby było O(1) zamiast loga.
int mapping(int x, int y) {
    if (x > y) swap(x, y);
	ll h = (((ll)x) << 30LL) + y;

	int res = identyfikatory[h];
	if (res > 0) return res;
	return identyfikatory[h] = FREE_ID++;
}

int BASE;

void odpowiedz() {

	cout << (tree[0][1] == tree[1][1] ? "TAK" : "NIE") << "\n";
}


inline void pull(int t, int i) {
	tree[t][i] = mapping(tree[t][2 * i], tree[t][2 * i + 1]);
}

void recalc(int t, int i) {
    i += BASE;
    while (i > 1) {
        i /= 2;
		pull(t, i);
    }
}


int32_t main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> q;
    BASE = 1 << n;
    for (int t = 0; t < 2; t++) {
		string s;
        cin >> s;

		for (int i = 0; i < (1 << n); i++) 
			tree[t][i + BASE] = s[i];
		for (int i = (1 << n) - 1; i >= 1; i--) {
			pull(t, i);
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
