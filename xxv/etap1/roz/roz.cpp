// Rozwiązanie do zadania 'Różnorodność' z I etapu XXV OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(n * m * log(n*m))
// Punkty: 100 (upsolve)

#include <bits/stdc++.h>

#include <bits/stdc++.h>
using namespace std;
constexpr int MAX_N = 3005, MAX_C = 100005;
int m, n, k;
int A[MAX_N][MAX_N];

// dp[i][j] = różnorodność kwadratu o prawym dolnym rogu w wierszu i i kolumnie j.
// Sumy prefiksowe 2D.
int dp[MAX_N][MAX_N];

// Reprezentuje aktywne kwadraty danego koloru. 
multiset<int> s[MAX_C];

// Znajduje przedział który zostałby pokryty, gdyby wrzucić aktywować kwadrat na kolumnach [j, j+k).
pair<int, int> pusty_przedzial(int kolor, int j) {
	int l = max(j, *(--s[kolor].upper_bound(j)) + k);
	int r = min(j + k - 1, *s[kolor].lower_bound(j) - 1);
	return {l, r};
}

void dodaj(int i, int l, int r, int delta) {
	if (l > r) return;
	dp[i][l] += delta;
	dp[i][r + 1] -= delta;
}

int32_t main() {
	ios_base::sync_with_stdio(0);
	cin >> m >> n >> k;
	
	// Wrzucam wartowników, żeby zawsze mieć poprawne iteratory z lower_bound.
	for (int i = 1; i < MAX_C; i++) {
		s[i].insert(-k);
		s[i].insert(n+1);
	}


	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> A[i][j];

			// Trzeba odjąć 1 od różnorodności, dla wszystkich kolumn,
			// które widzą tylko A[i-k][j].
			// Przez to że wszystkie przedziały są szerokości k, zbiór tych kolumn jest przedziałem.
			if (i > k) {
				int kolor = A[i-k][j];
				s[kolor].erase(s[kolor].find(j));
				auto [l, r] = pusty_przedzial(kolor, j);
				dodaj(i, l, r, -1);
			}

			// Dodaję 1 do różnorodności na przedziale kolumn [l, r],
			// ale tylko tam, gdzie jeszcze nie dodałem.
			int kolor = A[i][j];
			auto [l, r] = pusty_przedzial(kolor, j);
			dodaj(i, l, r, 1);
			s[kolor].insert(j);
		}
	}
	
	int max_roznorodnosc = 0;
	long long suma_roznorodnosci = 0;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			dp[i][j] += dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1];
			if (i >= k && j >= k) {
				max_roznorodnosc = max(max_roznorodnosc, dp[i][j]);
				suma_roznorodnosci += dp[i][j];
			} 
		}

	}

	cout << max_roznorodnosc << " " << suma_roznorodnosci << "\n";
}
