// Rozwiązanie do zadania 'Gra w wielokąty' z I etapu VI OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(1).
// Złożoność pamięciowa: O(1)
// Punkty: 100 (upsolve)

#include <algorithm>
#include <iostream>
using namespace std;
int n, a, b, c;

bool jest_bokiem_wielokata(int a, int b) {
	if (a > b) swap(a, b);
	if (b - a == 1) return true;
	if (a == 0 && b == n-1) return true;
	return false;
}

int32_t main() {
	ios_base::sync_with_stdio(0);
	cin >> n >> a >> b >> c;

	int boki = jest_bokiem_wielokata(a, b) 
			 + jest_bokiem_wielokata(b, c) 
			 + jest_bokiem_wielokata(a, c);
	if (boki == 2 || (n - 3) % 2 == 1) {
		cout << "TAK\n";
	} else {
		cout << "NIE\n";
	}

}
