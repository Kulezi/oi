// Rozwiązanie zadania 'Czekolada' z I Etapu X OI.
// Autor: Paweł Putra
// Złożoność czasowa: O((n + m) * log(n + m))
// Złożoność pamięciowa: O(n + m)
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>
#define dbg(x) #x << " = " << x << " "
using namespace std;
constexpr int MAXN = 1005, INF = 1'000'000'000;
int x[MAXN], y[MAXN];

int32_t main() {
	ios_base::sync_with_stdio(0);

	int m, n;

	cin >> m >> n;

	for (int i = 1; i <= m-1; i++) cin >> x[i];
	for (int i = 1; i <= n-1; i++) cin >> y[i];
	
	sort(x + 1, x + m, [](int a, int b) {return a > b;});
	sort(y + 1, y + n, [](int a, int b) {return a > b;});

	int i = 1, j = 1;
	int wynik = 0;
	while (i < m && j < n) {
		if (x[i] >= y[j]) {
			wynik += j * x[i];
			i++;
		} else {
			wynik += i * y[j];
			j++;
		}
	}

	while (i < m) wynik += j * x[i], i++;
	while (j < n) wynik += i * y[j], j++;

	cout << wynik << "\n";
}
