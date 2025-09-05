// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(liczba liczb kompletnych <= 10^9).
// Złożoność pamięciowa: O(1).
// Punkty: 100 (upsolve)
// Faktyczna pamięć: 452MB, nie chciało mi się tego żyłować. 

#include <bits/stdc++.h>

#define dbg(x) #x << " = " << x << " "
#define pot3(x) x*x*x
#define pot6(x) 1LL*x*x*x*x*x*x
#define pot7(x) pot6(x) * x
#define pot8(x) pot7(x) * x
using namespace std;
constexpr int P1 = 10, P2 = 100, P3 = 1000, P4 = 1'000'0, P5 = 1'000'00, P6 = 1'000'000, P7 = 1'000'000'0, P8 = 1'000'000'00, P9 = 1'000'000'000;
constexpr int SQRT_1e9 = 31623;
constexpr int SQRT_SQRT_1e9 = 178;
constexpr int MAX_T = 1005, SIEVE_SIZE = P8 / 6 + 69;

int f_div[SIEVE_SIZE + 5];
int N = 0;
int primes[SIEVE_SIZE + 5];

int complete[P8 + 5], pary[SQRT_1e9+5];

int d(int n) {
	int res = 1;
	while (n > 1) {
		int alpha = f_div[n];
		int beta = 0;
		while (f_div[n] == alpha) {
			beta++;
			n /= alpha;
		}
		res *= beta + 1;
	}

	return res;
}

int digits(int n) {
	int res = 1;
	while (n > 9) {
		res++;
		n /= 10;
	}
	return res;
}

bool is_complete(int n) {
	return d(n) == digits(n);

}

void preprocess() {
	for (int i = 1; i < SIEVE_SIZE; ++i)
		f_div[i] = i;
	for (int i = 2; i * i < SIEVE_SIZE; ++i)
		if (f_div[i] == i)
			for (int j = i; j < SIEVE_SIZE; j += i)
				f_div[j] = i;
  
	for (int i = 2; i < SIEVE_SIZE; ++i)
		if (f_div[i] == i)
			primes[++N] = i;

	// Zaznaczamy które liczby mniejsze od 10^6 są kompletne po prostu je sprawdzając.
	for (int i = 1; i < P6; i++) {
		complete[i] = is_complete(i);
	}

	// Liczby kompletne 7 cyfrowe są zawsze postaci p^6, gdzie p jest liczbą pierwszą.
	// Jest ich bardzo mało więc po prostu zaznaczamy je wszystkie.
	// Musi mieć dokładnie 7 cyfr.
	for (int i = 1, p6 = pot6(primes[i]); p6 < P7; i++, p6 = pot6(primes[i])) {
		if (p6 >= P6) {
			complete[p6] = 1;
		}
	}

	// Liczby kompletne 8 cyfrowe są jednej z 4 postaci, każdą zaznaczamy.
	// 1. Liczby postaci p^7 - liczymy analogicznie do 7 cyfrowych.
	for (int i = 1, p7 = pot7(primes[i]); p7 < P8; i++, p7 = pot7(primes[i])) {
		// Musi mieć dokładnie 8 cyfr.
		if (p7 >= P7) complete[p7] = 1;
	}

	// 2. Liczby postaci p*q^3, gdzie p < q i p, q pierwsze:
	// q^3 <= 10^8 więc q <= 10^(8/3) <= 1000, więc takich par p i q jest mniej niż 10^6.
	for (int i = 1, p = primes[i]; p <= 1000; i++, p = primes[i]) {
		for (int j = i+1, q3 = pot3(primes[j]); 1LL * p * q3 < P8; j++, q3 = pot3(primes[j])) {
			if (p * q3 >= P7) complete[p * q3] = 1;
		}
	}

	// 3. Liczby postaci p^3 * q, gdzie p < q i p, q pierwsze:
	// Tym razem p^4 <= p^3 * q <= 10^8, więc p <= 10^(8/4) = 100.
	// W sumie takich liczb też wyjdzie koło miliona.
	for (int i = 1, p3 = pot3(primes[i]); primes[i] < 100; i++, p3 = pot3(primes[i])) {
		for (int j = i+1, q = primes[j]; 1LL * p3 * q < P8; j++, q = primes[j]) {
			if (p3 * q >= P7) complete[p3 * q] = 1;
		}
	}

	// 4. Liczby postaci p * q * r, gdzie p < q < r i p, q, r pierwsze.
	// n <= r^3, więc r >= 10^(7/3), więc p * q <= n / r <= 10^(17/3) <= 464159.
	// p^2 <= p * q <= 464159 czyli p <= sqrt(464159) <= 682.
	// Okazuje się, że samych kandydatów na taką trójkę jest około 20 * 10^8.
	for (int i = 1; primes[i] <= 682; i++) {
		for (int j = i+1; primes[i] * primes[j] <= 464159; j++) {
			for (int k = j+1; 1LL * primes[i] * primes[j] * primes[k] < P8; k++) {
				if (primes[i] * primes[j] * primes[k] >= P7) complete[primes[i] * primes[j] * primes[k]] = 1;
			}
		}
	}

	// Spreprocesujemy sobie też ilość par p < q dla każdego n takich, że sqrt(10^8) <= p * q <= n < sqrt(10^9),
	// żeby potem sprawdzać szybko ile jest takich par, że p^2 * q^2 < n dla liczb 9 cyfrowych.
	// Takie p <= 10^(9 / 4) <= 178, bo p^4 <= p^2*q^2 <= 10^9.
	// Takich jest ~5 milionów.
	for (int i = 1; primes[i] <= SQRT_SQRT_1e9; i++) {
		for (int j = i+1; 1LL * primes[i] * primes[j] <= SQRT_1e9; j++) {
			// Takie co nie będą miały 9 cyfr to mnie średnio interesują.
			int pq = primes[i] * primes[j];
			if (digits(pq * pq) == 9) pary[primes[i] * primes[j]] = 1;
		}
	}

	// Na koniec trzeba jeszcze zrobić na tym wszystkim sumy prefiksowe.
	for (int i = 1; i <= P8; i++) {
		complete[i] += complete[i-1];
	}

	for (int i = 1; i <= SQRT_1e9; i++) {
		pary[i] += pary[i - 1];
	}
}

int pi(int n) {
	int res = 1;
	for (int i = 2; i <= n; ++i) 
		if (f_div[i] == i) ++res;
	return res;
}

pair<int,int> zapytanie[MAX_T];

void generuj_wazne_liczby() {
		cout << "pi(10^8 / 6) = " << pi(1'000'000'00 / 6) << endl;

	int suma = 0;
	for (int p = 2; p <= 100; p++) {
		if (f_div[p] == p) {
			int wynik = pi(1'000'000'00 / (p*p*p));
			cerr << dbg(p) << "pi(10^8/p^3) = " << wynik << endl;
			suma += wynik;
		}
	}

	cerr << "kejsów p_1^3 * p_2: " << suma << endl;

	long long cnt = 0;
	for (int i = 1; primes[i] <= 682; i++) {
		for (int j = i+1; primes[i] * primes[j] <= 464159; j++) {
			for (int k = j+1; 1ll * primes[i] * primes[j] * primes[k] <= 1'000'000'00; k++) {
				cnt++;
			}
		}
	}

	cerr << "kejsów p_1 * p_2 * p_3: " << cnt << endl;

}

int solve(int n) {
	int res = complete[min(n, P8)] + pary[int32_t(sqrt(n))];
	
	// Jeszcze zostało tylko doliczyć liczby kompletne postaci p^8, za dużo ich nie ma,
	// bo to tylko 11^8 i 13^8.
	if (pot8(11) <= n) res++;
	if (pot8(13) <= n) res++;

	return res;
}

int32_t main() {
	ios_base::sync_with_stdio(0);
	int t = 0;
	cin >> t;
	for (int i = 1; i <= t; i++) {
		auto &[a, b] = zapytanie[i];
		cin >> a >> b;
	}

	preprocess();

//	generuj_wazne_liczby();

	for (int i = 1; i <= t; i++) {
		auto [a, b] = zapytanie[i];
		cout << solve(b) - solve(a-1) << "\n";
	}
}
