// Rozwiązanie zadania 'Bajtokomputer' z III etapu XX OI.
// Autor: Paweł Putra
// Złożoność czasowa: O(n)
// Złożoność pamięciowa: O(n).


#include <iostream>
#include <algorithm>
using namespace std;
constexpr int MAXN = 1'000'005, INF = 1'000'000'000;
// dp[i][x] = koszt uzyskania posortowanego ciągu kończącego się na x - 1.
int dp[MAXN][3];
int x[MAXN];
int32_t main() {
	ios_base::sync_with_stdio(0);
	int n;
	cin >> n;

	if (n == 1) {
		cout << "0\n";
		return 0;
	}

	// Nie opłaca się wykraczać jakąkolwiek wartością ciągu poza zbiór {-1, 0, 1}.
	for (int i = 1; i <= n; i++) {
		cin >> x[i];
		for (int j = 0; j < 3; j++)
			dp[i][j] = INF;
	}
	dp[1][x[1] + 1] = 0;
	for (int i = 2; i <= n; i++) {
		for (int ostatni = -1; ostatni <= 1; ostatni++) {
			for (int teraz = ostatni; teraz <= 1; teraz++) {
				// Dodając zero nic nie zmienimy.
				if (ostatni == 0 && x[i] != teraz) continue;
				dp[i][teraz+1] = min(dp[i][teraz+1], dp[i-1][ostatni + 1] + abs(teraz - x[i]));
			}
		}
	}

	int wynik = min({dp[n][0], dp[n][1], dp[n][2]});
	if (wynik >= INF) cout << "BRAK\n";
	else cout << wynik << "\n";
}
