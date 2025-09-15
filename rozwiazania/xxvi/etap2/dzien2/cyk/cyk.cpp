// Rozwiązanie zadania 'Przesunięcie cykliczne' z II etapu XXV OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(log(n)))
// Złożoność pamięciowa: O(1)
// Ilość zapytań: 2 * log_2(n) + 2
// Punkty: 100 (upsolve)

#include <stdlib.h>
#include "cyklib.hpp"
#define dbg(x) #x << " = " << x << " "
using namespace std;
using ll = long long;

ll teraz;

ll pytaj(int k) {
	teraz = circular_shift(k);
	return teraz;
}


void odpowiadaj(int n) {
	ll przed = teraz;
	ll po = pytaj(n);
	if (przed == po) {
		give_answer(n);
		exit(0);
	}
}

bool mniej_niz_pol(int k) {
	ll a = teraz;
	ll b = pytaj(k);
	if (b == a) odpowiadaj(k);
	ll c = pytaj(k);
	if (c == a) odpowiadaj(2 * k);
	
	int inwersje = (a > b) + (a > c) + (b > c);
	return inwersje % 2 == 0;
}

int32_t main() {
	// Dobrze jest wiedzieć z czego zaczynamy.
	ll start = pytaj(0);
	pytaj(1);
	if (teraz == start) odpowiadaj(1);

	int lo = 1;
	while (mniej_niz_pol(lo * 2)) lo *= 2;

	int hi = 2 * lo;
	while (lo < hi) {
		int mid = (lo + hi + 1) / 2;
		if (mniej_niz_pol(mid)) lo = mid;
		else hi = mid - 1;
	}

	// Zostały tylko dwie opcje na odpowiedź.
	odpowiadaj(2 * lo);
	odpowiadaj(2 * lo + 1);
}

