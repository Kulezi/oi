// Rozwiązanie zadania 'Suma ciągu jedynkowego' z I Etapu V OI.
// Autor: Paweł Putra
// Złożoność czasowa: O(n).
// Złożoność pamięciowa: O(1).
// Punkty: 100 (upsolve)

#include <iostream>
using namespace std;
constexpr int MAXN = 10'005;
int32_t main() {
	ios_base::sync_with_stdio(0);
	int n, S;
	cin >> n >> S;

	bool ujemny = false;
	if (S < 0) {
		ujemny = true;
		S = -S;
	}

	// Mamy ciąg decyzji czy następny element będzie ostatnim +1 czy -1.
	// Zmiana decyzji nie zmienia parzystości.
	int max_suma = (n - 1) * n / 2;
	if (max_suma < S || max_suma % 2 != S % 2) {
		cout << "NIE\n";
		return 0;
	}
	
	cout << "0\n";
	int obecny = 0;
	
	// Zaczynamy z ciągu z samymi +1.
	int zmniejszen = (max_suma - S) / 2;
	for (int i = 1; i < n; i++) {
		// Zmiana z +1 na -1 w tym miejscu zmniejszy sumę o (n-1) * 2.
		if (n - i <= zmniejszen) {
			obecny--;
			zmniejszen -= n-i;
		} else {
			obecny++;
		}
		cout << (ujemny ? -obecny : obecny) << "\n";
	}
}
