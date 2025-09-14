// Rozwiązanie do zadania 'Kolorowy wąż' z I etapu XXX OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(p + n)
// Złożoność pamięciowa: O(m^2)
// Punkty: 100 (upsolve)
#include <bits/stdc++.h>
using namespace std;
constexpr int MAXM = 2005;
int t[MAXM][MAXM], kolor[MAXM][MAXM];

pair<int,int> ruch(char c) {
	if (c == 'D') return {1, 0};
	if (c == 'G') return {-1, 0};
	if (c == 'L') return {0, -1};
	if (c == 'P') return {0, 1};

	// Jak wywali to znaczy, że test jest niepoprawny.
	assert(false);
}

// Trzyma kolory kolejnych pól węża, w kolejności od ogona do głowy węża.
vector<int> waz = {0};

int32_t main() {
	ios_base::sync_with_stdio(0);
	int m, p, n;
	cin >> m >> p >> n;
	while (p--) {
		int w, k, c;
		cin >> w >> k >> c;

		// Indeksuję kolory od [1 do m^2], żeby nie musieć inicjować tabeli.
		kolor[w][k] = c + 1;
	}

	int x = 1, y = 1, T = 1;
	t[x][y] = T;
	while (n--) {
		char typ;
		cin >> typ;

		if (typ == 'Z') {
			int w, k;
			cin >> w >> k;
			
			// Wystarczy sprawdzić kiedy wszedłem na pole i jak to się ma względem głowy węża.
			int pozycja = t[w][k] - (T - (int)waz.size()) - 1;
			cout << (pozycja < 0 ? -1 : waz[pozycja]) << "\n";
		} else {
			auto [dx, dy] = ruch(typ);
			x += dx;
			y += dy;

			// Zapisuję kiedy wszedłem na pole.
			t[x][y] = ++T;

			if (kolor[x][y]) {
				waz.push_back(kolor[x][y] - 1);
				kolor[x][y] = 0;
			}
		}
	}

}
